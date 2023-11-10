def factorial(a):
    res = 1
    for i in range(1,a+1):
        res *= i
    return res;

def A(a,b):
    if a < b:
        return 0;
    else:
        return factorial(a)//factorial(a-b)


def C(a,b) :
    if a < b:
        return 0
    else:
        return factorial(a)//factorial(a-b)//factorial(b)

def output(x) :
    stk = []
    if x == 0:
        stk.append(0)
    else:
        while x:
            stk.append(x % 10)
            x //= 10
    while (len(stk)):
        print(stk.pop(), end='')


def main() :
    n, m = input().split()
    n, m = int(n), int(m)
   
    # sys.set_int_max_str_digits(10000000)
    output(A(m,m)*A(n+2,n+2)*C(n+3,m)-A(m,m)*A(n+1,n+1)*2*C(n+2,m))
    



if __name__ == "__main__":
    main()