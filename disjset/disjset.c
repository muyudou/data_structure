#include "disjset.h"

DisjSets::DisjSets(int numElements)
    : s(numElements, -1)
{

}

//路径压缩求find操作
int DisjSets::find(int x) const
{
    if (s[x] < 0)
        return x;
    else
        return x = find(s[x]);
}

int DisjSets::find(int x)
{
    if (s[x] < 0)
        return x;
    else
        return x = find(s[x]);
}

//按大小求并
void DisjSets::unionSets(int root1, int root2)
{
    if (s[root1] < s[root2])
    {
        s[root1] += s[root2];
        s[root2] = root1;
    }
    else
    {
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

void DisjSets::display()
{
    for (int i = 0; i < s.size(); i++)
        cout << s[i] << " ";
    cout << endl;
}
