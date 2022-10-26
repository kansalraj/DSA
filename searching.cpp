#include <iostream>
#include <queue>

using namespace std;

int binarySearch(int *input, int n, int val)
{
    int s = 0, e=n-1;
    int mid=(s+e)/2;
    while(s<=e) {
        if (input[mid]==val) return mid;
        if (input[mid] > val) e=mid-1; else s=mid+1;
        mid=(s+e)/2;
    }
    return -1;
}

int main() {}