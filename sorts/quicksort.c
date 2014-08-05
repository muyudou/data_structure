#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

template <typename Comparable>
const Comparable & median3(vector<Comparable> &a, int left, int right)
{
    int mid = (left+right)/2;
    if (a[left] > a[mid])
        swap(a[left], a[mid]);
    if (a[left] > a[right])
        swap(a[left], a[right]);
    if (a[mid] > a[right])
        swap(a[mid], a[right]);
    swap(a[mid], a[right-1]);
    return a[right-1];
}

template <typename Comparable>
void quickSort(vector<Comparable> &a, int left, int right)
{
    if(left >= right)
        return;

    Comparable pivot = median3(a, left, right);
    int i = left;
    int j = right-1;

    for (;;)
    {
        while (i < right-1 && a[++i] < pivot)
        {}
        while (j > left && a[--j] > pivot)
        {}
        if (i < j)
            swap(a[i], a[j]);
        else
            break;
    }
    swap(a[i], a[right-1]);
    quickSort(a, left, i-1);
    quickSort(a, i+1, right);
}


void quickSort2(int *arr, int left, int right)
{
    if (left >= right)
        return;
    int pivot = arr[left];
    int i = left+1;
    int j = right;

    while (i < j)
    {
        while (i <= right && arr[i] < pivot)
            ++i;
        while (j > left && pivot < arr[j])
            --j;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    if (arr[j] < arr[left])
        swap(arr[j], arr[left]);
    quickSort2(arr, left, j-1);
    quickSort2(arr, j+1, right); 
}

int main()
{
    int arr[10] = {8, 1, 4, 9, 0, 3, 5, 2, 7, 6};
    vector<int> a(arr, arr+10);
    //quickSort(a, 0, a.size()-1);
    quickSort2(arr, 0, 9);
    ostream_iterator<int> out(cout, " ");
    copy(a.begin(), a.end(), out);
    cout << endl;

    for (int i = 0; i < 10; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
