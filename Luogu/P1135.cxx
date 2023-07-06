#include <cstdio>
#include <queue>
#include <cstdlib>
#define maxn 210

using namespace std;

int dataa[maxn];
bool st[maxn];
int n,a,b;
queue<int> x;
int nexta[maxn];
int nex;

int read() {
    int f1 = 0,f2 = 1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f2 = -1;
    } while (ch > '9' || ch < '0');
    do {
        f1 = f1*10 + ch -'0';
        ch = getchar();
    } while (ch <= '9' && ch >= '0');
    return f1*f2;
}


/*
该题最后几次提交问题出在标记上
90pts的原因就是当时的标记是在遍历到该点才打的，这就会导致一个很大的问题
也就是说如果我 7 步和 114514 步 扩展到同一个点， 但是这个点还没有被遍历到（苦命排队人
就会出现重复。
*/

void bfs() {
    int da = x.front();
    int step = dataa[da] + 1;

    if (da == b) {
		printf("%d",dataa[da]);
		exit(0);
	}
    x.pop();        
    
    if (da + nexta[da] <= nex && !st[da + nexta[da]] ) {
    	x.push(da + nexta[da]);
    	dataa[da+nexta[da]] = step;
        st[da+nexta[da]] = 1;
	}
	if (da - nexta[da] > 0 && !st[da - nexta[da]]) {
    	x.push(da - nexta[da]);
    	dataa[da-nexta[da]] = step;
        st[da-nexta[da]] = 1;
	}
	
}

int main() {
    n = read(); a = read(); b = read();
    for (int i = 1; i <= n; i ++) {
    	nexta[++ nex] = read();
	}
    
    x.push(a);

    while (!x.empty()) bfs();
	printf("-1");
    return 0;
}