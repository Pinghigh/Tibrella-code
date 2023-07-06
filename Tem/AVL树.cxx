#include <iostream>

auto max = [](auto a, auto b) { return a > b ? a : b; };
auto min = [](auto a, auto b) { return a < b ? a : b; };

template <class Type, int Size>
class AVLTree {
    struct Node {
        Node *lc, *rc;
        int height, siz, freq;
        Type val;
    } tree[Size], *root, *null, *tot, *rubbish_bin[Size];
    int bintop;

    using nodePointer = Node*;

    int get_height(nodePointer nod) {
        if (nod == null) return -1;
        return nod->height;
        // return max(get_height(nod->lc), get_height(nod->rc)) + 1;
    }
    int get_siz(nodePointer nod) {
        if (nod == null) return 0;
        return get_siz(nod->lc) + get_siz(nod->rc) + 1;
    }

    void update(nodePointer nod) {  // 此处高度只和下面有关，所以直接获取儿子高度进行更新即可。
        nod->height = max(get_height(nod->lc), get_height(nod->rc)) + 1;
        // nod->siz = get_siz(nod->lc) + get_siz(nod->rc) + 1;
        return;
    }

    int balance_fact(nodePointer nod) {
        if (nod == null) return 0;
        return get_height(nod->lc) - get_height(nod->rc);
    }

    nodePointer left_rotate(nodePointer nod) {
        nodePointer newRoot = nod->rc;
        nod->rc = newRoot->lc;
        newRoot->lc = nod;

        update(nod);
        update(newRoot);

        return newRoot;  // 返回新根
    }

    nodePointer right_rotate(nodePointer nod) {
        nodePointer newRoot = nod->lc;
        nod->lc = newRoot->rc;
        newRoot->rc = nod;

        update(nod);
        update(newRoot);

        return newRoot;
    }

    // nodePointer r_l_rotate(nodePointer nod) {  // 右子树上插入左儿子，先（向）右旋右儿子，再左旋自己
    //     nod->rc = right_rotate(nod->rc);
    //     return left_rotate(nod);
    // }

    // nodePointer l_r_rotate(nodePointer nod) {  // 左子树插入右儿子
    //     nod->lc = left_rotate(nod->lc);
    //     return right_rotate(nod);
    // }

    nodePointer rotate(nodePointer nod) {
        int factor = balance_fact(nod);
        if (factor > 1) {  // lc-rc 大于 1，左偏，需要右旋
            if (balance_fact(nod->lc) > -1)
                return right_rotate(nod);
            else {
                nod->lc = left_rotate(nod->lc);
                return right_rotate(nod);
            }
        } else if (factor < -1) {
            if (balance_fact(nod->rc) < 1)
                return left_rotate(nod);
            else {
                nod->rc = right_rotate(nod->rc);
                return left_rotate(nod);
            }
        }
        return nod;
    }

    nodePointer get_new() {
        if (bintop) {
            return rubbish_bin[bintop--];
        } else {
            ++tot;
            return tot;
        }
    }

    nodePointer get_max_nod(nodePointer nod) {
        while (nod->rc != null)
            nod = nod->rc;
        return nod;
    }
    nodePointer get_min_nod(nodePointer nod) {
        while (nod->lc != null)
            nod = nod->lc;
        return nod;
    }

    nodePointer ins(nodePointer& nod, Type val) {
        if (nod == null) {
            // std::cout << "[INS] " << val << '\n';
            nod = get_new();
            nod->val = val;
            nod->siz = 1;
            nod->freq = 1;
            nod->lc = nod->rc = null;
        } else if (val > nod->val)
            nod->rc = ins(nod->rc, val);
        else if (val < nod->val)
            nod->lc = ins(nod->lc, val);
        else {
            ++nod->freq;
            return nod;
        }
        update(nod);
        nod = rotate(nod);
        return nod;
    }

    nodePointer& del(nodePointer& nod, Type val) {
        if (nod == null) {
            return null;
        } else {
            if (val == nod->val) {
                if (nod->lc != null && nod->rc != null) {
                    if (get_height(nod->lc) > get_height(nod->rc)) {
                        nodePointer pre = nod->lc;  // 如果左子树比右子树大，则从左子树找最大值替换当前节点
                        while (pre->rc != null)
                            pre = pre->rc;
                        nod->val = pre->val;
                        nod->lc = del(nod->lc, pre->val);  // 递归删除刚才找到的最大值
                    } else {
                        nodePointer pre = nod->rc;
                        while (pre->lc != null)
                            pre = pre->lc;
                        nod->val = pre->val;
                        nod->rc = del(nod->rc, pre->val);
                    }
                } else {
                    // std::cout << "[DEL] " << nod->val << '\n';
                    rubbish_bin[++bintop] = nod;
                    if (nod->lc != null)
                        nod = nod->lc;
                    else if (nod->rc != null)
                        nod = nod->rc;
                    else
                        return null;
                }
            } else if (val > nod->val) {
                nod->rc = del(nod->rc, val);
            } else {
                nod->lc = del(nod->lc, val);
            }
            update(nod);
            nod = rotate(nod);
            return nod;
        }
    }

    nodePointer find(nodePointer nod, Type val) {
        // if (val == nod->val || nod == null)
        //     return nod;
        // else if (val > nod->val)
        //     return find(nod->lc, val);
        // else
        //     return find(nod->rc, val);
        while (nod->val != val) {
            if (nod->val > val)
                nod = nod->lc;
            else
                nod = nod->rc;
        }
        return nod;
    }

    // nodePointer find_rk(nodePointer nod, int k) {
    //     while (get_siz(nod->lc) != k - 1) {
    //         while (nod->lc == null)
    //             nod = nod->rc;
    //         if (get_siz(nod->lc) > k - 1)
    //             nod = nod->lc;
    //         else
    //             k -= get_siz(nod->lc) + 1, nod = nod->rc;
    //     }
    //     return nod;
    // }

    nodePointer find_rk(nodePointer nod, int k) {
        if (get_siz(nod->lc) >= k)
            return find_rk(nod->lc, k);
        else if (get_siz(nod->lc) + nod->freq >= k)
            return nod;
        else
            return find_rk(nod->rc, k - get_siz(nod->lc) - nod->freq);
    }

    void print(nodePointer nod) {
        if (nod == null) return;
        if (nod->lc != null) std::cout << nod->val << ' ' << nod->lc->val << std::endl;
        if (nod->rc != null) std::cout << nod->val << ' ' << nod->rc->val << std::endl;
        print(nod->lc);
        print(nod->rc);
    }

public:
    AVLTree() {
        tot = tree;
        null = root = tot;

        // init null node
        null->lc = null->rc = root->lc = root->rc = null;
        null->height = null->val = null->siz = 0;
    }

    void insert(Type val) {
        ins(root, val);
    }
    void remove(Type val) {
        del(root, val);
    }
    int get_rank(Type val) {
        nodePointer nod = root;
        Type ans = 0;
        while (nod != null) {
            if (nod->val == val)
                return get_siz(nod->lc) + ans + 1;
            else if (nod->val > val)
                nod = nod->lc;
            else {
                ans += get_siz(nod->lc) + 1;
                nod = nod->rc;
            }
        }
        return ans + 1;
    }
    Type find_by_rank(int rk) {
        return find_rk(root, rk)->val;
    }
    Type get_front(Type val) {
        nodePointer nod = root;
        Type ans;
        while (nod != null) {
            if (nod->val == val)
                return get_max_nod(nod->lc)->val;
            else if (nod->val > val)
                nod = nod->lc;
            else {
                ans = nod->val;
                nod = nod->rc;
            }
        }
        return ans;
    }
    Type get_next(Type val) {
        nodePointer nod = root;
        Type ans;
        while (nod != null) {
            if (nod->val == val) {
                if (nod->rc != null) {
                    nod = nod->rc;
                    while (nod->lc != null)
                        nod = nod->lc;
                    ans = nod->val;
                }
                break;
            } else if (nod->val < val)
                nod = nod->rc;
            else {
                ans = nod->val;
                nod = nod->lc;
            }
            if (nod->val > val && nod->val < ans) ans = nod->val;
            nod = nod->val < val ? nod->rc : nod->lc;
        }
        return ans;
    }

    void debug() {
        std::cout << get_siz(root) << '\n' << root->val << '\n';
        print(root);
    }
};

AVLTree<int, 100005> tree;
int n, m;
int opt, x;

using std::cin;
using std::cout;

#define endl '\n'

int main() {
    // std::ios::sync_with_stdio(0);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    cin >> n;
    while (n--) {
        cin >> opt >> x;
        // if (opt != 2 && opt != 1) cout << "DEBUG " << opt << ' ' << x << ' ';
        if (opt == 1) {
            tree.insert(x);
        } else if (opt == 2) {
            tree.remove(x);
        } else if (opt == 3) {
            cout << tree.get_rank(x) << endl;
        } else if (opt == 4) {
            cout << tree.find_by_rank(x) << endl;
        } else if (opt == 5) {
            cout << tree.get_front(x) << endl;
        } else if (opt == 6) {
            cout << tree.get_next(x) << endl;
        }
    }

    // tree.debug();

    return 0;
}
