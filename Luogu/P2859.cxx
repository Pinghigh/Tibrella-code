/*
    Licensed under GPL v3
*/

#pragma GCC target("avx2,sse4a,bmi,bmi2,lzcnt,popcnt,fma")

#ifndef PDQSORT_H
#define PDQSORT_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

#if __cplusplus >= 201103L
#include <cstdint>
#include <type_traits>
#define PDQSORT_PREFER_MOVE(x) std::move(x)
#else
#define PDQSORT_PREFER_MOVE(x) (x)
#endif

namespace pdqsort_detail {
    enum {
        // Partitions below this size are sorted using insertion sort.
        insertion_sort_threshold = 24,

        // Partitions above this size use Tukey's ninther to select the pivot.
        ninther_threshold = 128,

        // When we detect an already sorted partition, attempt an insertion sort that allows this
        // amount of element moves before giving up.
        partial_insertion_sort_limit = 8,

        // Must be multiple of 8 due to loop unrolling, and < 256 to fit in unsigned char.
        block_size = 64,

        // Cacheline size, assumes power of two.
        cacheline_size = 64

    };

#if __cplusplus >= 201103L
    template <class T>
    struct is_default_compare : std::false_type {};
    template <class T>
    struct is_default_compare<std::less<T>> : std::true_type {};
    template <class T>
    struct is_default_compare<std::greater<T>> : std::true_type {};
#endif

    // Returns floor(log2(n)), assumes n > 0.
    template <class T>
    inline int log2(T n) {
        return std::__lg(n);
    }

    // Sorts [begin, end) using insertion sort with the given comparison function.
    template <class Iter, class Compare>
    inline void insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return;

        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = PDQSORT_PREFER_MOVE(*sift);

                do {
                    *sift-- = PDQSORT_PREFER_MOVE(*sift_1);
                } while (sift != begin && comp(tmp, *--sift_1));

                *sift = PDQSORT_PREFER_MOVE(tmp);
            }
        }
    }

    // Sorts [begin, end) using insertion sort with the given comparison function. Assumes
    // *(begin - 1) is an element smaller than or equal to any element in [begin, end).
    template <class Iter, class Compare>
    inline void unguarded_insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return;

        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = PDQSORT_PREFER_MOVE(*sift);

                do {
                    *sift-- = PDQSORT_PREFER_MOVE(*sift_1);
                } while (comp(tmp, *--sift_1));

                *sift = PDQSORT_PREFER_MOVE(tmp);
            }
        }
    }

    // Attempts to use insertion sort on [begin, end). Will return false if more than
    // partial_insertion_sort_limit elements were moved, and abort sorting. Otherwise it will
    // successfully sort and return true.
    template <class Iter, class Compare>
    inline bool partial_insertion_sort(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (begin == end) return true;

        std::size_t limit = 0;
        for (Iter cur = begin + 1; cur != end; ++cur) {
            Iter sift = cur;
            Iter sift_1 = cur - 1;

            // Compare first so we can avoid 2 moves for an element already positioned correctly.
            if (comp(*sift, *sift_1)) {
                T tmp = PDQSORT_PREFER_MOVE(*sift);

                do {
                    *sift-- = PDQSORT_PREFER_MOVE(*sift_1);
                } while (sift != begin && comp(tmp, *--sift_1));

                *sift = PDQSORT_PREFER_MOVE(tmp);
                limit += cur - sift;
            }

            if (limit > partial_insertion_sort_limit) return false;
        }

        return true;
    }

    template <class Iter, class Compare>
    inline void sort2(Iter a, Iter b, Compare comp) {
        if (comp(*b, *a)) std::iter_swap(a, b);
    }

    // Sorts the elements *a, *b and *c using comparison function comp.
    template <class Iter, class Compare>
    inline void sort3(Iter a, Iter b, Iter c, Compare comp) {
        sort2(a, b, comp);
        sort2(b, c, comp);
        sort2(a, b, comp);
    }

    template <class T>
    inline T* align_cacheline(T* p) {
#if defined(UINTPTR_MAX) && __cplusplus >= 201103L
        std::uintptr_t ip = reinterpret_cast<std::uintptr_t>(p);
#else
        std::size_t ip = reinterpret_cast<std::size_t>(p);
#endif
        ip = (ip + cacheline_size - 1) & -cacheline_size;
        return reinterpret_cast<T*>(ip);
    }

    template <class Iter>
    inline void swap_offsets(Iter first, Iter last, unsigned char* offsets_l, unsigned char* offsets_r, size_t num, bool use_swaps) {
        typedef typename std::iterator_traits<Iter>::value_type T;
        if (use_swaps) {
            // This case is needed for the descending distribution, where we need
            // to have proper swapping for pdqsort to remain O(n).
            for (size_t i = 0; i < num; ++i) {
                std::iter_swap(first + offsets_l[i], last - offsets_r[i]);
            }
        } else if (num > 0) {
            Iter l = first + offsets_l[0];
            Iter r = last - offsets_r[0];
            T tmp(PDQSORT_PREFER_MOVE(*l));
            *l = PDQSORT_PREFER_MOVE(*r);
            for (size_t i = 1; i < num; ++i) {
                l = first + offsets_l[i];
                *r = PDQSORT_PREFER_MOVE(*l);
                r = last - offsets_r[i];
                *l = PDQSORT_PREFER_MOVE(*r);
            }
            *r = PDQSORT_PREFER_MOVE(tmp);
        }
    }

    // Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
    // to the pivot are put in the right-hand partition. Returns the position of the pivot after
    // partitioning and whether the passed sequence already was correctly partitioned. Assumes the
    // pivot is a median of at least 3 elements and that [begin, end) is at least
    // insertion_sort_threshold long. Uses branchless partitioning.
    template <class Iter, class Compare>
    inline std::pair<Iter, bool> partition_right_branchless(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;

        // Move pivot into local for speed.
        T pivot(PDQSORT_PREFER_MOVE(*begin));
        Iter first = begin;
        Iter last = end;

        // Find the first element greater than or equal than the pivot (the median of 3 guarantees
        // this exists).
        while (comp(*++first, pivot))
            ;

        // Find the first element strictly smaller than the pivot. We have to guard this search if
        // there was no element before *first.
        if (first - 1 == begin)
            while (first < last && !comp(*--last, pivot))
                ;
        else
            while (!comp(*--last, pivot))
                ;

        // If the first pair of elements that should be swapped to partition are the same element,
        // the passed in sequence already was correctly partitioned.
        bool already_partitioned = first >= last;
        if (!already_partitioned) {
            std::iter_swap(first, last);
            ++first;

            // The following branchless partitioning is derived from "BlockQuicksort: How Branch
            // Mispredictions don’t affect Quicksort" by Stefan Edelkamp and Armin Weiss, but
            // heavily micro-optimized.
            unsigned char offsets_l_storage[block_size + cacheline_size];
            unsigned char offsets_r_storage[block_size + cacheline_size];
            unsigned char* offsets_l = align_cacheline(offsets_l_storage);
            unsigned char* offsets_r = align_cacheline(offsets_r_storage);

            Iter offsets_l_base = first;
            Iter offsets_r_base = last;
            size_t num_l, num_r, start_l, start_r;
            num_l = num_r = start_l = start_r = 0;

            while (first < last) {
                // Fill up offset blocks with elements that are on the wrong side.
                // First we determine how much elements are considered for each offset block.
                size_t num_unknown = last - first;
                size_t left_split = num_l == 0 ? (num_r == 0 ? num_unknown / 2 : num_unknown) : 0;
                size_t right_split = num_r == 0 ? (num_unknown - left_split) : 0;

                // Fill the offset blocks.
                if (left_split >= block_size) {
                    for (size_t i = 0; i < block_size;) {
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                    }
                } else {
                    for (size_t i = 0; i < left_split;) {
                        offsets_l[num_l] = i++;
                        num_l += !comp(*first, pivot);
                        ++first;
                    }
                }

                if (right_split >= block_size) {
                    for (size_t i = 0; i < block_size;) {
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                    }
                } else {
                    for (size_t i = 0; i < right_split;) {
                        offsets_r[num_r] = ++i;
                        num_r += comp(*--last, pivot);
                    }
                }

                // Swap elements and update block sizes and first/last boundaries.
                size_t num = std::min(num_l, num_r);
                swap_offsets(offsets_l_base, offsets_r_base, offsets_l + start_l, offsets_r + start_r, num, num_l == num_r);
                num_l -= num;
                num_r -= num;
                start_l += num;
                start_r += num;

                if (num_l == 0) {
                    start_l = 0;
                    offsets_l_base = first;
                }

                if (num_r == 0) {
                    start_r = 0;
                    offsets_r_base = last;
                }
            }

            // We have now fully identified [first, last)'s proper position. Swap the last elements.
            if (num_l) {
                offsets_l += start_l;
                while (num_l--)
                    std::iter_swap(offsets_l_base + offsets_l[num_l], --last);
                first = last;
            }
            if (num_r) {
                offsets_r += start_r;
                while (num_r--)
                    std::iter_swap(offsets_r_base - offsets_r[num_r], first), ++first;
                last = first;
            }
        }

        // Put the pivot in the right place.
        Iter pivot_pos = first - 1;
        *begin = PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = PDQSORT_PREFER_MOVE(pivot);

        return std::make_pair(pivot_pos, already_partitioned);
    }

    // Partitions [begin, end) around pivot *begin using comparison function comp. Elements equal
    // to the pivot are put in the right-hand partition. Returns the position of the pivot after
    // partitioning and whether the passed sequence already was correctly partitioned. Assumes the
    // pivot is a median of at least 3 elements and that [begin, end) is at least
    // insertion_sort_threshold long.
    template <class Iter, class Compare>
    inline std::pair<Iter, bool> partition_right(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;

        // Move pivot into local for speed.
        T pivot(PDQSORT_PREFER_MOVE(*begin));

        Iter first = begin;
        Iter last = end;

        // Find the first element greater than or equal than the pivot (the median of 3 guarantees
        // this exists).
        while (comp(*++first, pivot))
            ;

        // Find the first element strictly smaller than the pivot. We have to guard this search if
        // there was no element before *first.
        if (first - 1 == begin)
            while (first < last && !comp(*--last, pivot))
                ;
        else
            while (!comp(*--last, pivot))
                ;

        // If the first pair of elements that should be swapped to partition are the same element,
        // the passed in sequence already was correctly partitioned.
        bool already_partitioned = first >= last;

        // Keep swapping pairs of elements that are on the wrong side of the pivot. Previously
        // swapped pairs guard the searches, which is why the first iteration is special-cased
        // above.
        while (first < last) {
            std::iter_swap(first, last);
            while (comp(*++first, pivot))
                ;
            while (!comp(*--last, pivot))
                ;
        }

        // Put the pivot in the right place.
        Iter pivot_pos = first - 1;
        *begin = PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = PDQSORT_PREFER_MOVE(pivot);

        return std::make_pair(pivot_pos, already_partitioned);
    }

    // Similar function to the one above, except elements equal to the pivot are put to the left of
    // the pivot and it doesn't check or return if the passed sequence already was partitioned.
    // Since this is rarely used (the many equal case), and in that case pdqsort already has O(n)
    // performance, no block quicksort is applied here for simplicity.
    template <class Iter, class Compare>
    inline Iter partition_left(Iter begin, Iter end, Compare comp) {
        typedef typename std::iterator_traits<Iter>::value_type T;

        T pivot(PDQSORT_PREFER_MOVE(*begin));
        Iter first = begin;
        Iter last = end;

        while (comp(pivot, *--last))
            ;

        if (last + 1 == end)
            while (first < last && !comp(pivot, *++first))
                ;
        else
            while (!comp(pivot, *++first))
                ;

        while (first < last) {
            std::iter_swap(first, last);
            while (comp(pivot, *--last))
                ;
            while (!comp(pivot, *++first))
                ;
        }

        Iter pivot_pos = last;
        *begin = PDQSORT_PREFER_MOVE(*pivot_pos);
        *pivot_pos = PDQSORT_PREFER_MOVE(pivot);

        return pivot_pos;
    }

    template <class Iter, class Compare, bool Branchless>
    inline void pdqsort_loop(Iter begin, Iter end, Compare comp, int bad_allowed, bool leftmost = true) {
        typedef typename std::iterator_traits<Iter>::difference_type diff_t;

        // Use a while loop for tail recursion elimination.
        while (true) {
            diff_t size = end - begin;

            // Insertion sort is faster for small arrays.
            if (size < insertion_sort_threshold) {
                if (leftmost)
                    insertion_sort(begin, end, comp);
                else
                    unguarded_insertion_sort(begin, end, comp);
                return;
            }

            // Choose pivot as median of 3 or pseudomedian of 9.
            diff_t s2 = size / 2;
            if (size > ninther_threshold) {
                sort3(begin, begin + s2, end - 1, comp);
                sort3(begin + 1, begin + (s2 - 1), end - 2, comp);
                sort3(begin + 2, begin + (s2 + 1), end - 3, comp);
                sort3(begin + (s2 - 1), begin + s2, begin + (s2 + 1), comp);
                std::iter_swap(begin, begin + s2);
            } else
                sort3(begin + s2, begin, end - 1, comp);

            // If *(begin - 1) is the end of the right partition of a previous partition operation
            // there is no element in [begin, end) that is smaller than *(begin - 1). Then if our
            // pivot compares equal to *(begin - 1) we change strategy, putting equal elements in
            // the left partition, greater elements in the right partition. We do not have to
            // recurse on the left partition, since it's sorted (all equal).
            if (!leftmost && !comp(*(begin - 1), *begin)) {
                begin = partition_left(begin, end, comp) + 1;
                continue;
            }

            // Partition and get results.
            std::pair<Iter, bool> part_result = Branchless ? partition_right_branchless(begin, end, comp) : partition_right(begin, end, comp);
            Iter pivot_pos = part_result.first;
            bool already_partitioned = part_result.second;

            // Check for a highly unbalanced partition.
            diff_t l_size = pivot_pos - begin;
            diff_t r_size = end - (pivot_pos + 1);
            bool highly_unbalanced = l_size < size / 8 || r_size < size / 8;

            // If we got a highly unbalanced partition we shuffle elements to break many patterns.
            if (highly_unbalanced) {
                // If we had too many bad partitions, switch to heapsort to guarantee O(n log n).
                if (--bad_allowed == 0) {
                    std::make_heap(begin, end, comp);
                    std::sort_heap(begin, end, comp);
                    return;
                }

                if (l_size >= insertion_sort_threshold) {
                    std::iter_swap(begin, begin + l_size / 4);
                    std::iter_swap(pivot_pos - 1, pivot_pos - l_size / 4);

                    if (l_size > ninther_threshold) {
                        std::iter_swap(begin + 1, begin + (l_size / 4 + 1));
                        std::iter_swap(begin + 2, begin + (l_size / 4 + 2));
                        std::iter_swap(pivot_pos - 2, pivot_pos - (l_size / 4 + 1));
                        std::iter_swap(pivot_pos - 3, pivot_pos - (l_size / 4 + 2));
                    }
                }

                if (r_size >= insertion_sort_threshold) {
                    std::iter_swap(pivot_pos + 1, pivot_pos + (1 + r_size / 4));
                    std::iter_swap(end - 1, end - r_size / 4);

                    if (r_size > ninther_threshold) {
                        std::iter_swap(pivot_pos + 2, pivot_pos + (2 + r_size / 4));
                        std::iter_swap(pivot_pos + 3, pivot_pos + (3 + r_size / 4));
                        std::iter_swap(end - 2, end - (1 + r_size / 4));
                        std::iter_swap(end - 3, end - (2 + r_size / 4));
                    }
                }
            } else {
                // If we were decently balanced and we tried to sort an already partitioned
                // sequence try to use insertion sort.
                if (already_partitioned && partial_insertion_sort(begin, pivot_pos, comp) && partial_insertion_sort(pivot_pos + 1, end, comp)) return;
            }

            // Sort the left partition first using recursion and do tail recursion elimination for
            // the right-hand partition.
            pdqsort_loop<Iter, Compare, Branchless>(begin, pivot_pos, comp, bad_allowed, leftmost);
            begin = pivot_pos + 1;
            leftmost = false;
        }
    }
}  // namespace pdqsort_detail

template <class Iter, class Compare>
inline void pdqsort(Iter begin, Iter end, Compare comp) {
    if (begin == end) return;

#if __cplusplus >= 201103L
    pdqsort_detail::pdqsort_loop<Iter, Compare,
                                 pdqsort_detail::is_default_compare<typename std::decay<Compare>::type>::value && std::is_arithmetic<typename std::iterator_traits<Iter>::value_type>::value>(
        begin, end, comp, pdqsort_detail::log2(end - begin));
#else
    pdqsort_detail::pdqsort_loop<Iter, Compare, false>(begin, end, comp, pdqsort_detail::log2(end - begin));
#endif
}

template <class Iter>
inline void pdqsort(Iter begin, Iter end) {
    typedef typename std::iterator_traits<Iter>::value_type T;
    pdqsort(begin, end, std::less<T>());
}

template <class Iter, class Compare>
inline void pdqsort_branchless(Iter begin, Iter end, Compare comp) {
    if (begin == end) return;
    pdqsort_detail::pdqsort_loop<Iter, Compare, true>(begin, end, comp, pdqsort_detail::log2(end - begin));
}

template <class Iter>
inline void pdqsort_branchless(Iter begin, Iter end) {
    typedef typename std::iterator_traits<Iter>::value_type T;
    pdqsort_branchless(begin, end, std::less<T>());
}

#undef PDQSORT_PREFER_MOVE

#endif

#include <cstdio>

namespace Fastio {
    namespace Fread {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S, *T;
        inline char getchar() {
            if (S == T) {
                T = (S = buf) + fread(buf, 1, SIZE, stdin);
                if (S == T) return '\n';
            }
            return *S++;
        }
    }  // namespace Fread
    namespace Fwrite {
        const int SIZE = (1 << 20);
        char buf[SIZE], *S = buf, *T = buf + SIZE;
        inline void flush() {
            fwrite(buf, 1, S - buf, stdout);
            S = buf;
        }
        inline void putchar(char c) {
            *S++ = c;
            if (S == T) flush();
        }
        struct NTR {
            ~NTR() {
                flush();
            }
        } ztr;
    }  // namespace Fwrite
#ifdef ONLINE_JUDGE
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#endif
    struct Reader {
        template <typename T>
        Reader& operator>>(T& x) {
            char c = getchar();
            T dp = 1;
            while (c < '0' || c > '9') {
                c = getchar();
            }
            x = 0;
            while (c > 47 && c < 58)
                x = x * 10 + (c ^ '0'), c = getchar();
            return *this;
        }
        Reader& operator>>(char& c) {
            c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            return *this;
        }
        Reader& operator>>(char* str) {
            int len = 0;
            char c = getchar();
            while (c == ' ' || c == '\n')
                c = getchar();
            while (c != ' ' && c != '\n' && c != '\r')
                str[len++] = c, c = getchar();
            str[len] = '\0';
            return *this;
        }
        inline Reader() {}
    } cin;
    const char endl = '\n';
    char sta[40];
    struct Writer {
        template <typename T>
        Writer& operator<<(T x) {
            int top = 0;
            do {
                sta[++top] = x % 10 ^ 48, x /= 10;
            } while (x);
            do {
                putchar(sta[top--]);
            } while (top);
            return *this;
        }
        Writer& operator<<(char c) {
            putchar(c);
            return *this;
        }
        Writer& operator<<(char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        Writer& operator<<(const char* str) {
            int cur = 0;
            while (str[cur])
                putchar(str[cur++]);
            return *this;
        }
        inline Writer() {}
    } cout;
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
}  // namespace Fastio
using namespace Fastio;

using i32 = int;
using i64 = long long;

struct p {
    i32 id;
    i32 end;

    bool operator<(const p& exa) {
        return end < exa.end;
    }
};

#define __SIZ 50005

struct Node {
    p val;
    Node *child, *nex;
} tree[__SIZ], *rubbish_bin[__SIZ];
Node *null = tree, *tot = tree;
int bintop;
class pairing_heap {
    inline __attribute__((always_inline)) Node* new_node() {
        Node* nod;
        if (bintop)
            nod = rubbish_bin[bintop--];
        else
            nod = ++tot;
        nod->child = null;
        nod->nex = null;
        return nod;
    }

    inline __attribute__((always_inline)) void remove(Node* x) {
        rubbish_bin[++bintop] = x;
    }

    inline __attribute__((always_inline)) Node* meld(Node* x, Node* y) {  // 合并两个堆
        if (x == null)
            return y;
        else if (y == null)
            return x;
        if (x->val < y->val) {
            y->nex = x->child;
            x->child = y;
            return x;
        } else {
            x->nex = y->child;
            y->child = x;
            return y;
        }
    }

    Node* merges(Node* x) {
        if (x == null || x->nex == null) return x;  // x 为空或者 x 没有下一个兄弟节点
        Node* y = x->nex;                           // y 是 x 的下一个兄弟
        Node* c = y->nex;                           // c 是下一个兄弟
        x->nex = y->nex = null;                     // 拆散
        return meld(merges(c), meld(x, y));         // x 与 y 配对在一起，剩下的继续配对
    }

    inline __attribute__((always_inline)) Node* del(Node* x) {
        Node* t = merges(x->child);
        remove(x);
        return t;
    }

public:
    Node* root;
    pairing_heap() {
        root = null;
    }
    inline __attribute__((always_inline)) void push(p x) {
        Node* y = new_node();
        y->val = x;
        if (root == null)
            root = y;
        else
            root = meld(root, y);
    }
    inline __attribute__((always_inline)) p top() {
        return root->val;
    }
    inline __attribute__((always_inline)) void pop() {
        if (root == null) return;
        root = del(root);
    }

    inline __attribute__((always_inline)) void join(pairing_heap& x) {
        root = meld(root, x.root);
    }

    bool empty() {
        return (root == null);
    }
} q;

#include <algorithm>

struct c {
    i32 id;
    i32 s, e;
} cow[__SIZ];
i32 n;
i32 ans[__SIZ];
i32 cnt;

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> cow[i].s >> cow[i].e;
        cow[i].id = i;
    }

    pdqsort_branchless(cow + 1, cow + n + 1, [](c& a, c& b) { return a.s < b.s; });

    for (int i = 1; i <= n; ++i) {
        if (cow[i].s > q.top().end && !q.empty()) {
            ans[cow[i].id] = q.top().id;
            q.pop();
            q.push({ ans[cow[i].id], cow[i].e });
        } else {
            ans[cow[i].id] = ++cnt;
            q.push({ cnt, cow[i].e });
        }
    }

    cout << cnt << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }

    return 0;
}