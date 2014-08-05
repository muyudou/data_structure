#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;

template <typename Comparable>
void insertSort(vector<Comparable> &a)
{
    cout << a.size() << endl;
    for (int i = 1; i < a.size(); i++)
    {
        Comparable tmp = a[i];
        int j;
        for (j = i-1; j >= 0 && a[j] > tmp; j--)
            a[j+1] = a[j];
        a[j+1] = tmp;
    }
}

template <typename Comparable>
void bubbleSort(vector<Comparable> &a)
{
    int i, j;
    for (i = 1; i < a.size(); i++)
        for (j = 0; j < a.size()-i; j++)
            if (a[j] > a[j+1])
                swap(a[j], a[j+1]);
}

//每次选择最小的元素，放在已排序序列的最后一个
template <typename Comparable>
void selectSort(vector<Comparable> &a)
{
    int i, j;
    for (i = 0; i < a.size()-1; i++)
    {
        int index = i;
        for (j = i+1; j < a.size(); j++)
            if (a[j] < a[index])
                index = j;
        swap(a[i], a[index]);
    }
}

template <typename Comparable>
void shellsort(vector<Comparable> &a)
{
    int d, i, j;

    for (d = a.size()/2; d > 0; d /= 2)
    {
        for (i = d; i < a.size(); i++)
        {
            Comparable tmp = a[i];
            for (j = i-d; j >= 0 && a[j] > tmp; j -= d)
                a[j+d] = a[j];
            a[j+d] = tmp;
        }
    }
}

template <typename Comparable>
void percolateDown(vector<Comparable> &a, int i, int n)
{
    Comparable tmp = a[i];
    int child;
    for (; i < n/2; i = child)
    {
        child = 2*i;
        if (child < n && a[child+1] > a[child])
            child++;
        if (a[child] > tmp)
            a[i] = a[child];
        else
            break;
    }
    a[i] = tmp;
}

template <typename Comparable>
void buildSort(vector<Comparable> &a)
{
    int i;
    for (i = a.size()/2-1; i>= 0; i--)
        percolateDown(a, i, a.size());
}

template <typename Comparable>
void deleteMin(vector<Comparable> &a, int i)
{
    swap(a[i], a[0]);
    percolateDown(a, 0, i);
}

template <typename Comparable>
void heapSort(vector<Comparable> &a)
{
    buildSort(a);
    int i;
    for (i = a.size()-1; i > 0; i--)
        deleteMin(a, i);
}

template <typename Comparable>
void mergeSort(vector<Comparable> &a)
{
    vector<Comparable> tmpArray(a.size());
    mergeSort(a, tmpArray, a.size()-1);
}

template <typename Comparable>
void mergeSort(vector<Comparable> &a, vector<Comparable> &b,
        int left, int right)
{
    if (left < right)
    {
        int center = (left+right)/2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center+1, right);
        merge(a, tmpArray, left, center+1, right);
    }
}

template <typename Comparable>
void merge(vector<Comparable> &a, vector<Comparable> &tmpArray,
        int left, int right, int len)
{
    int pos = left;
    while (left != right && right != len)
    {
        if (a[left] < a[right])
            tmpArray[pos++] = a[left++];
        else
            tmpArray[pos++] = a[right++];
    }

    while (left != right)
        tmpArray[pos++] = a[left++];
    while (right != len)
        tmpArray[pos++] = a[right++];

    for (int i = 0; i < right+1; i++, len--)
        a[len] = tmpArray[len];
}

int main()
{
    int arr[6] = {8, 34, 64, 51, 32, 21};
    int arr1[13] = {81, 94, 11, 96, 12, 35, 17, 95, 28, 58, 41, 75, 15};
    vector<int> a(arr, arr+6);
    vector<int> a1(arr1, arr1+13);
    //insertSort(a);
    //shellsort(a1);
    //bubbleSort(a);
    //bubbleSort(a1);
    //selectSort(a);
    //selectSort(a1);
    heapSort(a);
    heapSort(a1);

    ostream_iterator<int> out(cout, ",");
    copy(a.begin(), a.end(), out);
    cout << endl;
    copy(a1.begin(), a1.end(), out);
    cout << endl;
    return 0;
}
