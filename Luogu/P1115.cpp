#include <iostream>
#include <stack>
#include <string>
#include <cmath>
#define len 200

using namespace std;

string str;
stack<char> och;
char sta[len*2],tmp[len*2];
int tail,top;
int ch=0;
bool flag=0;
bool st[len*2];

struct numNode{
    numNode* next=NULL;
    int data;
    numNode(int a,numNode* nexta=NULL) {
        data = a;
        next = nexta;
    }
}
struct ocNode{
    ocNode* next=NULL;
    char data;
    numNode(char a,ocNode* nexta=NULL) {
        data = a;
        next = nexta;
    }
}

int o[10][10] = {
    { 1, 1,-1,-1,  -1,   1,   1,-1},
    { 1, 1,-1,-1,  -1,   1,   1,-1},
    { 1, 1, 1, 1,  -1,   1,   1,-1},
    { 1, 1, 1, 1,  -1,   1,   1,-1},
    {-1,-1,-1,-1,  -1,   0,0x3F,-1},
    { 1, 1, 1, 1,0x3F,   1,   1, 1},
    {-1,-1,-1,-1,  -1,0x3F,   0,-1},
    { 1, 1, 1, 1,  -1,   1,   1, 1}
};

inline int p(char a, char b) {
    int x,y;
    switch (a) {
        case('+'): x = 0;break;
        case('-'): x = 1;break;
        case('*'): x = 2;break;
        case('/'): x = 3;break;
        case('('): x = 4;break;
        case(')'): x = 5;break;
        case('#'): x = 6;break;
        case('^'): x = 7;break;
    }
    switch (b) {
        case('+'): y = 0;break;
        case('-'): y = 1;break;
        case('*'): y = 2;break;
        case('/'): y = 3;break;
        case('('): y = 4;break;
        case(')'): y = 5;break;
        case('#'): y = 6;break;
        case('^'): y = 7;break;
    }
    return o[x][y];
}
inline int previous(int now) {
    while (!st[now-1]) {
        now --;
    }
    return now-1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    och.push('#');
    cin >> str;
    str += '#';
    /*
    按照《数据结构》P79的思路写的
    由于书中的题目的表达式有#作为结尾，所以不再逐个输入字符，而是先输入整个串在末位添加#作为结尾。
    因此下面代码中的一个 ch++ 就相当于 getchar 一次，ch 相当于一个指针，用于遍历表达式 str
    */
    while (och.top() != '#' || str[ch] != '#') {
        if (str[ch] <= '9' && str[ch] >= '0') {
            tail++;
            sta[tail]=str[ch]; st[tail] = 1;
            ch++;
        }

        // 符号

        else {
            switch(p(och.top(),str[ch])) {
                case (-1):
                    och.push(str[ch]);ch++;break;
                case (0):
                    ch ++;
                    och.pop(); // '('
                    break;
                case (1):
                    tail++;
                    sta[tail] = och.top(); // 栈顶符号进队
                    st[tail] = 1; // 后缀表达式数组中的第 tail 个元素有效
                    och.pop();
                    
                    break;
            }
        }
    }
    
    for (int j = 0; j <= tail; j ++) {
        if (st[j]) cout << sta[j] << ' ';
    }
    cout << endl;
    int i = 0;
    for (;;) {
        flag = 0;
        // 输出操作的结果（如果不为空）
        for (int j = 0; j <= tail; j ++) {
            cout << sta[j] << ' ';
        }
        cout << endl;

        // 遍历后缀表达式数组，找到运算符号时运算并替换、
        for (i = 0; i <= tail; i ++) {
            int calcTmp;
            int prev,ppre;
            if (sta[i] == '+' || sta[i] == '-' || sta[i] == '/' || sta[i] == '*' || sta[i] == '^') {
                prev = previous(i);ppre = previous(prev);
                switch (sta[i]) {
                    case('+') :
                        calcTmp = sta[prev] + sta[ppre] - '0' - '0';flag=1;break;
                    case('-') :
                        calcTmp = sta[ppre] - sta[prev];flag=1;break;
                    case('*'):
                        calcTmp = (sta[ppre]-'0') * (sta[prev]-'0');flag=1;break;
                    case('/'):
                        calcTmp = (sta[ppre]-'0') / (sta[prev]-'0');flag=1;break;
                    case('^'):
                        calcTmp = pow(sta[ppre]-'0',sta[prev]-'0');flag=1;break;
                }
            }

            if (flag) {
                st[ppre] = 0; st[prev] = 0;
                st[ppre] = calcTmp;
                continue;
            } else {
                cout << st[ppre];
                return 0;
            }
        }
    }

    return 0;
}