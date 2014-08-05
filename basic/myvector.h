const int SPACE_CAPACITY = 8;

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize=0)
		: theSize(initSize), theCapacity(initSize+SPACE_CAPACITY)
	{
		objects = new Object[initSize];
	}

	Vector(const Vector& rhs)
		: theSize(initSize), theCapacity(initSize)
	{
		operator=(rhs);
	}
	~Vector()
	{
		delete [] objects;
	}

	const Vector& operator=(const Vector& rhs)
	{
		if (this == &rhs)
			return *this;
		else
		{
			delete [] objects;
			theSize = rhs.size();
			theCapacity = rhs.Capacity();

			objects = new Object[theCapacity];
			int i;
			for (i = 0; i < theSize; i++)
				objects[i] = (rhs.objects)[i];
			return *this;
		}
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
            reserve(newSize*2+1)
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity > theSize)
		{
            Object* oldobjects = objects;
            theCapacity = newCapacity;       
       
			int i;
			objects = new Object[newCapacity]();
            for (i = 0; i < theSize; i++)
				objects[i] = oldobjects[i];
			delete [] oldobjects;
		}
	}

	Object& operator[](int index)
	{
		return objects[index];
	}

	const Object& operator[](int index) const
	{
		return objects[index];
	}

	bool empty() const
	{
		return theSize == 0;
	}

	int size() const
	{
		return theSize;
	}
	
	int capacity() const
	{
		return theCapacity();
	}

	void push_back(const Object& x)
	{
		if (theSize == theCapacity)
			reserve(theSize * 2+1);
		objects[theSize++] = x;
	}

	void pop_back()
	{
		theSize--;
	}

	const Object& back() const
	{
		return objects[theSize-1];
	}

	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator begin()
	{
		return &objects[0];
	}

	const_iterator begin() const
	{
		return &objects[0];
	}

	iterator end()
	{
		return &objects[theSize];
	}

	const_iterator end() const
	{
		return &objects[theSize];
	}

	enum {SPACE_CAPACITY = 16};
private:
	int theSize;
	int theCapacity;
    Object *objects;
}
