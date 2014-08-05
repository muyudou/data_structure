#include <vector>
class BinomialQueue
{
public:
    BinomialQueue();
    BinomialQueue(const Comparable &item);
    BinomialQueue(const BinomialQueue &rhs);
    ~BinomialQueue();

    bool isEmpty() const;
    const Comparable &findMin() const;

    void insert(const Comparable &x) const;
    void deleteMin();
    void deleteMin(BinomialQueue &rhs);

    void makeEmpty();
    void merge(BinomialQueue & rhs)
    {
        if (this == &rhs)
            return;

        currentSize += rhs.currentSize;

        if (currentSize > capacity())
        {
            int oldNumTrees = theTrees.size();
            int newNumTrees = max(oldNumTrees, rhs.theTrees.size())+1;
            theTrees.resize(newNumTrees);
            for (int i = oldNumTrees; i < newNumTrees; i++)
                theTrees[i] = NULL;
        }

        BinomialNode *carry = NULL;
        for (int i = 0, j = 1; j <= currentSize; i++, j *= 2)
        {
            BinomialNode *t1 = theTrees[i];
            BinomialNode *t2 = (i < rhs.theTrees[i].size()) ? 
                rhs.theTrees[i] : NULL;

            BinomiakNode *carry = NULL;
            int whichCase = t1 == NULL ? 0 : 1;
            whichCase += t2 == NULL ? 0 : 2;
            whichCase += carry == NULL ? 0 : 4;
            
            switch (whichCase)
            {
                case 0:
                case 1:
                    break;
                case 2:
                    theTrees[i] = t2;
                    rhs.theTrees[i] = NULL;
                    break;
                case 3:
                    carry = combineTrees(t1, t2);
                    theTrees[i] = NULL;
                    rhs.theTrees[i] = NULL;
                    break;
                case 4:
                    theTrees[i] = carry;
                    carry = NULL;
                    break;
                case 5:
                    carry = combine(t1, carry);
                    theTrees[i] = NULL;
                    break;
                case 6:
                    carry = combine(t2, carry);
                    rhs.theTrees[i] = NULL;
                    break;
                case 7:
                    theTrees[i] = carry;
                    carry = combine(t1, t2);
                    rhs.theTrees[i] = NULL;
                    break;
            }
        }
        for (int k = 0; k < rhs.theTrees.size(); k++)
            rhs.theTrees[k] = NULL;
        rhs.currentSize = 0;
    }

    const BinomialQueue & operator=(const BinomialQueue &rhs);

private:
    struct BinomialNode
    {
        Comparable element;
        BinomialNode *leftchild;
        BinomialNode *nextSibling;

        BinomialNode(const Comparable &theElement,
            BinomialNode *lt, BinomialNode *rt)
            : element(theElement), leftchild(lt), nextSibling(rt) {}
    };

    enum {DEFAULT_TREES = 1};

    int currentSize;
    vector<BinomialNode *> theTrees;

    int findMinIndex() const;
    int capacity() const;
    BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2)
    {
        if (t2->element < t1->element)
            return combineTrees(t2, t1);
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        currentSize--;
    }
    void makeEmpty(BinomialNode *&t);
    BinomialNode *clone(BinomialNode *t) const;
};
