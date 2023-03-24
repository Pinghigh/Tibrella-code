#include <cstdio>
#include <algorithm>

using namespace std;

int n,a[70],sum,maxn,len,hav,nown/*已经拼了多少木棍*/;
bool vis[70]; //记录各个木棍的状态

bool cmp(int a ,int b) {
	return a > b ;	
}

int read() {
    int x = 0,f=1;
    char ch;
    do {
        ch = getchar();
        if (ch == '-') f = -1;
    } while (ch > '9' || ch < '0');
    do {
        x = x*10 + ch -'0';
        ch = getchar();
    } while (ch <= '9' && ch >= '0');
    return f*x;
} // 快速读取// 快速读取

int dfs(
    int lon /*目前这根木棍已经拼了多长*/,
    int last /*上一根更长的木棍*/
    /*
    last 的意义：
    所有小木棍是排好序的，并且我们从大到小搜索
    因此目前这一根木棍之前的（更长的）一定是搜索过的
    所以这根木棍之前的所有木棍直接减掉
    */

    )
{
    if (hav > nown) return true; // 拼过的数量等于 总和/长度
    if (lon == len) 
    {   
        hav ++;
        int tmp = dfs(0,1);
        hav --;
        return tmp; // 直接把与原长相等的木棍扔里，然后搜索下一个
    }
    int fail = 0;
    for (int i = last; i <= n; i ++) {
        if (!vis[i] && lon + a[i] <= len && fail != a[i]) {
            /*
            1.跳过搜索过的木棍
            2.剪枝3：跳过之前搜索过同样长度（且失败）的长度
            3.如果当前木棍大于待拼长度就搜索下一个        
            */
            vis[i] = true;
            if (dfs(lon + a[i], i + 1)) return true;
            vis[i] = false;
            fail = a[i];
            if (lon == 0 || lon + a[i] == len) return false;
        }
    }
    return false;
}

int main() {
    n = read();
    for (int i = 1; i <= n; i ++) {
        a[i] = read();
        sum += a[i]; maxn = max(maxn,a[i]);
    }

    // 索引从 1 开始，而 a 指向第 0 个元素，因此 a+1
    sort(a + 1, a + n + 1, cmp); // 剪枝2：按照长度从大到小处理每根木棍

    for (len = maxn /*原长*/; len <= sum; len ++) {
        if (sum % len) continue; // 剪枝 1 : 只枚举总长度的因数
        hav = 1;
        nown = (sum/len);
        if (dfs(0,1)) {
            printf("%d\n",len);
            break;
        }
    }

    return 0;
}
