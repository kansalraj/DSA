#include <iostream>
#include <queue>

using namespace std;

int binarySearch(int *input, int n, int val)
{
    int s = 0, e = n - 1;
    int mid = (s + e) / 2;
    while (s <= e)
    {
        if (input[mid] == val)
            return mid;
        if (input[mid] > val)
            e = mid - 1;
        else
            s = mid + 1;
        mid = (s + e) / 2;
    }
    return -1;
}

int binarySearchOptimised(int *input, int n, int val)
{
    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    while (s <= e)
    {
        if (input[mid] == val)
            return mid;
        if (input[mid] > val)
            e = mid - 1;
        else
            s = mid + 1;
        mid = s + (e - s) / 2;
    }
    return -1;
}

int firstOccInSortedArray(vector<int> &input, int n, int val)
{
    int s = 0, e = n - 1, ans = -1;
    int mid = s + (e - s) / 2;
    while (s <= e)
    {
        if (input[mid] == val)
        {
            ans = mid;
            e = mid - 1;
        }
        else if (input[mid] > val)
            e = mid - 1;
        else
            s = mid + 1;
        mid = s + (e - s) / 2;
    }
    return ans;
}

int lastOccInSortedArray(vector<int> &input, int n, int val)
{
    int s = 0, e = n - 1, ans = -1;
    int mid = s + (e - s) / 2;
    while (s <= e)
    {
        if (input[mid] == val)
        {
            ans = mid;
            s = mid + 1;
        }
        else if (input[mid] > val)
            e = mid - 1;
        else
            s = mid + 1;
        mid = s + (e - s) / 2;
    }
    return ans;
}

pair<int, int> firstAndLastPosition(vector<int> &arr, int n, int k)
{
    return {firstOccInSortedArray(arr, n, k), lastOccInSortedArray(arr, n, k)};
}

int peakIndexInMountainArray(vector<int> &arr)
{
    int s = 0;
    int e = arr.size() - 1;
    int mid = (s + e) / 2;
    while (s <= e)
    {
        if ((mid - 1) > -1 && (mid + 1) < arr.size() && arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
            return mid;
        else if (arr[mid] < arr[mid + 1])
            s = mid + 1;
        else
            e = mid - 1;
        mid = (s + e) / 2;
    }
    return -1;
}

int peakIndexInMountainArrayDifferentApproach(vector<int> &arr)
{
    int s = 0, e = arr.size() - 1;
    int mid = s + (e - s) / 2;
    while (s < e)
    {
        if (arr[mid] < arr[mid + 1])
            s = mid + 1;
        else
            e = mid;
        mid = s + (e - s) / 2;
    }
    return s;
}

int getPivot(int arr[], int n)
{
    int s = 0, e = n - 1;
    int mid = (s + e) / 2;
    while (s < e)
    {
        if (arr[mid] > arr[0])
        {
            s = mid + 1;
        }
        else
            e = mid;
        mid = (s + e) / 2;
    }
    return s;
}

int main()
{
    int arr[5] = {3, 8, 10, 17, 1};
    cout << getPivot(arr, 5);
}