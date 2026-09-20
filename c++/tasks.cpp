#include <iostream>
#include "tasks.h"

class VectorIndexError : public std::exception {
    std::string msg;
public:
    VectorIndexError(std::string mess) : msg{ mess }
    {
    }
    virtual ~VectorIndexError() {}
    const char* what() const noexcept override { return msg.c_str(); }
};

template <typename T>
class Vector {
    T* data{ nullptr };
    size_t capacity1{ 8 };
    size_t length{ 0 };
    void new_size_data(int len)
    {
        if (len < capacity1) return;

        while (capacity1 <= len)
            capacity1 *= 2;

        T* ar = new T[capacity1];
        for (int i = 0; i < length; i++)
            ar[i] = data[i];

        delete[] data;
        data = ar;
    }

    class ItemIndex {
        int index;
        Vector<T>* dat{ nullptr };
    public:
        ItemIndex(Vector<T>* other, int ind) : dat{ other }, index{ ind }
        {
        }
        T operator =(T right)
        {
            dat->data[index] = right;
            return right;
        }
        operator T()
        {
            return dat->data[index];
        }
    };
public:
    Vector()
    {
        data = new T[capacity1];
    }
    Vector(const Vector<T>& other)
    {
        data = new T[other.capacity1];
        capacity1 = other.capacity1;
        length = other.length;

        for (int i = 0; i < length; i++)
            data[i] = other.data[i];
    }
    Vector(T* d, int size) : capacity1{ 8 }
    {
        data = new T[capacity1];
        new_size_data(size);
        for (int i = 0; i < size; i++)
            data[i] = d[i];

        length = size;
    }
    ~Vector() { delete[] data; }
    size_t size() const { return length; }
    size_t capacity() const { return capacity1; }
    void push_back(T elem)
    {
        new_size_data(length + 1);
        data[length] = elem;
        length++;
        return;
    }
    void push_front(T elem)
    {
        new_size_data(length + 1);

        for (int i = length; i > -1; i--)
            data[i] = data[i - 1];

        data[0] = elem;
        length++;
        return;

    }
    void pop_front()
    {
        for (int i = 0; i < length; i++)
            data[i] = data[i + 1];

        length--;
        return;
    }

    void pop_back()
    {
        data[length - 1] = data[length];
        length--;
        return;
    }
    ItemIndex operator[](int index)
    {
        if (index < 0 || index >= length)
            throw VectorIndexError("Invalid element index.");

        return ItemIndex(this, index);
    }
    void remove(int index)
    {
        if (index < 0 || index > length)
            throw VectorIndexError("Invalid element index.");

        if (index == 0) { pop_front(); return; }
        if (index == length) { pop_back(); return; }

        for (int i = index; i < length; i++)
            data[i] = data[i + 1];

        length--;
        return;
    }
    void insert(int index, T elem)
    {
        if (index < 0 || index > length)
            throw VectorIndexError("Invalid element index.");

        new_size_data(length + 1);

        if (index == 0) { push_front(elem); return; }
        if (index == length) { push_back(elem); return; }

        for (int i = length; i > index - 1; i--)
            data[i] = data[i - 1];

        data[index] = elem;
        length++;
        return;
    }
    bool empty() { return length; }
    void clear()
    {
        delete[] data;
        data = nullptr;
        length = 0;
        return;
    }
    Vector<T>* operator+= (const Vector<T>& right)
    {
        new_size_data(length + right.length);

        for (int i = length, j = 0; i < length + right.length; i++, j++)
            data[i] = right.data[j];

        length = length + right.length;
        return this;
    }
    Vector<T> operator + (const Vector<T> right)
    {
        T* dat = new T[right.length + length];
        for (int i = 0; i < length; i++)
            dat[i] = data[i];
        for (int i = length, j = 0; i < right.length + length; i++, j++)
            dat[i] = right.data[j];
        Vector<T> a(dat, right.length + length);
        delete[] dat;

        return a;
    }


};

int main()
{
    MemoryLeakDetector detector;
    Vector<short> ar_d;

    ar_d.push_back(1);
    ar_d.push_back(1);
    ar_d.push_front(2);
    ar_d.push_front(7);


    Vector<short> ar_d2 = ar_d;
    ar_d2 += ar_d;

    Vector<short> res = ar_d + ar_d2;

    size_t sz = res.size();
    for (size_t i = 0; i < sz; ++i)
        std::cout << res[i] << " ";
    return 0;
}
