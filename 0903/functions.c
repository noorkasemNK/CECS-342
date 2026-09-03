
//procedure 
int twice(int n) {
    return 2 * n;
}

//pure function
int average(int a, int b)
{
    return (a + b) / 2;
}


int signum2(int n) {
    return (n<0) ? -1 : ((n>0) ? 1 : 0);
}

//loops 
int factorial(int n) {
    int f =1;
    for (int k = 1; k <=n; ++k) {
        f *=k;
    }
    return f;
}
// varaible are always immutable in haskell
