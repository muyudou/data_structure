#include <vector>
#include <list>

template <typename HashedObj>
class HashTable
{
public:
    explicit HashTable(int size=101)
    {
        makeEmpty();
    }

    bool contains(const HashedObj &x) const
    {
        int index = myhash(x);
        xlist = theLists[index];
        list<HashedObj>::iterator it;
        for (it = xlist.begin(); it != xlist.end(); it++)
        {
            if (x == *it)
                return true;
        }
        return false;
    }

    void makeEmpty()
    {
        currentSize = 0;
        int i;
        for (i = 0; i < theLists.size(); i++)
        {
            theLists[i].clear();
        }
    }

    bool insert(const HashedObj & x)
    {
        list<HashedObj> &xlist = theLists[myhash(x)];
        if (find(xlist.begin(), xlist.end(), x) != xlist.end())
            return false;
        else
        {
            xlist.push_back(x);
            if (++currentSize > theLists.size())
                rehash();

            return true;
        }
    }

    bool remove(const HashedObj & x)
    {
        list<HashedObj> &xlist = theLists[myhash(x)];
        list<HashedObj>::iter;
        if ((iter = find(xlist.begin(), xlist.end(), x)) != xlist.end())
        {
            list.erase(iter);
            --currentSize;
            return true;
        }
        else
            return false;
        
    }

private:
    vector<list<HashedObj> > theLists;
    int currentSize;

    void rehash()
    {
        vector<list<HashedObj> > oldLists = theLists;

        theLists.resize(nextPrime(2*theLists.size()));
        for(int j = 0; j < theLists.size(); j++)
            theLists[j].clear();

        currentSize = 0;
        for (int i = 0; i < oldLists.size(); i++)
        {
            list<HashedObj>::iterator itr = oldLists[i].begin();
            while (itr != oldLists[i].end())
                insert(*itr++);
        }
    }

    int myhash(const HashedObj & x) const
    {
        int hashVal = hash(x);

        hashVal %= theList.size();
        if (hashVal < 0)
            hashVal += theLists.size();
        return hashVal;
    }
};

int hash(const string & key);
int hash(int key);
