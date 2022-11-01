#include <iostream>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int countDistinctWays(int nStairs) {
    if (nStairs<0) return 0;
    if(nStairs==0) return 1;
    return countDistinctWays(nStairs-1)+ countDistinctWays(nStairs-2);
}

int main() {}