#include <stdio.h>
#include <algorithm>

using namespace std;

int fb[50]={0,1};

int main() {
    int n;
    scanf("%d",&n);

    for(int i = 2; i <= n; i ++) {
        fb[i] = fb[i-1] + fb[i-2];
    }
    printf("%.2f",1.0*fb[n]);

    return 0;
}