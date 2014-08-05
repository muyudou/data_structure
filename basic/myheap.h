template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap(int capacity=100)
    {
        makeEmpty();
        array.reserve(capacity);
    }
    explicit BinaryHeap(const vector<Comparable> & items)
    {
        array = items;
        currentSize = items.size();    
    }

    bool isEmpty() const
    {
        return currentSize == 0;
    }

    const Comparable & findMin() const
    {
        return array[1];
    }

    void insert(const Comparable & x)
    {
        if (currentSize == array.size()-1)
            array.resize(array.size()*2);

        int hole = ++currentSize;
        while (array[hole/2] > x && hole > 1)
        {
            array[hole] = array[hole/2];
            hole /= 2;
        }
        if (array[hole] == x)
            return;
        else
            array[hole] == x;
    }

    void deleteMin()
    {
        
    }

    void deleteMin(Comparable & minItem);
    void makeEmpty()
    {
        currentSize = 0;
        array.clear();
    }

private:
    int currentSize;
    vector<Comparable> array;

    void buildHeap();
    void percolateDown(int hole);
};
