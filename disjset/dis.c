#include "disjset.h"
#include <iostream>
using namespace std;

int main()
{
    DisjSets d(8);
    d.unionSets(4, 5);
    d.unionSets(6, 7);
    d.unionSets(4, 6);
    int i, j;

    cin >> i >> j;
    i = d.find(i);
    j = d.find(j);
    if (i != j)
        d.unionSets(i, j);
    d.display();
    return 0;
}

