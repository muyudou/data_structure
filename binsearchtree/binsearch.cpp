#include <iostream>
#include <vector>
using namespace std;

template <typename Comparable>
int binsearch(const vector<Comparable>& a, const Comparable& x)
{
	int low = 0;
	int high = a.size()-1;
    int mid;

	while (low <= high)
	{
		mid = (low+high)/2;
        if (x == a[mid])
			return mid;
		else if (x < a[mid])
			high = mid-1;
		else
			low = mid+1;
	}
	return -1;
}

int main()
{
	vector<int> arr;
	int i, pos, val;

    for (i = 0; i < 8; i++)
		arr.push_back(i);
	cin >> val;
	pos = binsearch(arr, val);
	if (pos == -1)
		cout << "不存在" << endl;
	else
		cout << "位置是: " << pos << endl;

}
