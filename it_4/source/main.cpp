#include <iostream>
#include <cstring>
#include <cassert>

template <class T>
class DefaultComparator {
public:
    bool operator() (const T& l, const T& r) {
        return l < r;
    }
};

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray();
    explicit DynamicArray(size_t initialSize);

    DynamicArray(const DynamicArray &array);
    DynamicArray(DynamicArray &&array);

    ~DynamicArray();

    size_t size() const;
    T operator[](size_t idx) const;
    T& operator[](size_t idx);

    DynamicArray& operator=(const DynamicArray &array);
    DynamicArray operator=(DynamicArray &&array);

    void add(T element);

    T pop();

    size_t getInitialSize() const;
    void display() const;
private:
    const size_t initialSize = 16;
    const size_t growCoeff = 2;

    T* buffer;
    size_t bufferSize;
    size_t realSize;

    void grow();
};

template <typename T, class Comporator = DefaultComparator<T> >
class Heap {
    template <typename U, class Comporator_U>
    friend int calculateTime(Heap<U, Comporator_U>);
public:
    Heap();
    Heap(const DynamicArray<T> &array);
    Heap(DynamicArray<T> &&array);

    ~Heap() = default;

    void insert(T element);

    T extractMount();

    T peekMount() const;
    T peekLast() const;
    size_t size() const;
    void display() const;

private:
    void siftUp(size_t idx);
    void siftDown(size_t idx);

    void heapify();

    DynamicArray<T> array;

    Comporator comp;
};

template<typename T, class Comporator>
int calculateTime(Heap<T, Comporator> heap) {
    int sumTime = 0;

    while (heap.size() > 1) {
        int time = heap.extractMount();
        time += heap.extractMount();
        heap.insert(time);
        sumTime += time;
    }

    return sumTime;
}

int main() {
    size_t num;
    std::cin >> num;

    DynamicArray<int> array(num);
    for (size_t i = 0; i < num; i++) {
        std::cin >> array[i];
    }

    Heap<int> heap(array);
    std::cout << calculateTime(heap) << std::endl;

    return 0;
}

template <typename T>
DynamicArray<T>::DynamicArray() : buffer(nullptr), bufferSize(0), realSize(0) {
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t initialSize)
    : buffer(nullptr), bufferSize(initialSize), realSize(initialSize) {
    buffer = new T[bufferSize];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &array)
    : bufferSize(array.bufferSize), realSize(array.realSize) {
    buffer = new T[bufferSize];

    for (size_t i = 0; i < realSize; i++) {
        buffer[i] = array.buffer[i];
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray &&array)
    :  buffer(array.buffer), bufferSize(array.bufferSize), realSize(array.realSize) {
    array.realSize = 0;
    array.bufferSize = 0;
    array.buffer = nullptr;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    if (buffer) {
        delete[] buffer;
    }
}

template <typename T>
T DynamicArray<T>::operator[] (size_t idx) const {
    assert(idx >= 0 && idx < realSize);
    return buffer[idx];
}

template <typename T>
T& DynamicArray<T>::operator[] (size_t idx) {
    assert(idx >= 0 && idx < realSize);
    return buffer[idx];
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray &array) {
    if (this != &array) {
        delete[] this->buffer;
        bufferSize = array.realSize;
        realSize = array.realSize;
        buffer = new T[bufferSize];
        for (size_t i = 0; i < realSize; i++) {
            buffer[i] = array.buffer[i];
        }
    }
    return *this;
}

template <typename T>
DynamicArray<T> DynamicArray<T>::operator=(DynamicArray &&array) {
    if (this != &array) {
        delete[] this->buffer;
        bufferSize = array.realSize;
        realSize = array.realSize;
        buffer = array.buffer;

        array.bufferSize = 0;
        array.realSize = 0;
        array.buffer = nullptr;
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::grow() {
    size_t newBufferSize = std::max(bufferSize * this->growCoeff, this->initialSize);
    T* newBuffer = new T[newBufferSize];

    std::copy(buffer, buffer + bufferSize, newBuffer);

    delete[] buffer;

    buffer = newBuffer;
    bufferSize = newBufferSize;
}

template <typename T>
void DynamicArray<T>::add(T element) {
    if (realSize == bufferSize) {
        grow();
    }

    assert(realSize < bufferSize && buffer != 0);

    buffer[realSize++] = element;
}

template <typename T>
T DynamicArray<T>::pop() {
    return buffer[--realSize];
}

template <typename T>
void DynamicArray<T>::display() const {
    for (size_t i = 0; i < realSize; i++) {
        std::cout << buffer[i] << "\t";
    }
    std::cout << std::endl;
}

template <typename T>
size_t DynamicArray<T>::size() const {
    return realSize;
}

template <typename T, class Comporator>
Heap<T, Comporator>::Heap(const DynamicArray<T> &array) {
    this->array = array;
    heapify();
}

template <typename T, class Comporator>
Heap<T, Comporator>::Heap(DynamicArray<T> &&array) {
    this->array = std::move(array);
    heapify();
}

template <typename T, class Comporator>
void Heap<T, Comporator>::display() const {
    this->array.display();
}

template <typename T, class Comporator>
size_t Heap<T, Comporator>::size() const {
    return array.size();
}

template <typename T, class Comporator>
void Heap<T, Comporator>::siftDown(size_t idx) {
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;
    size_t largest = idx;

    if (left < array.size() && comp(array[left], array[largest])) {
        largest = left;
    }
    if (right < array.size() && comp(array[right], array[largest])) {
        largest = right;
    }
    if (largest != idx) {
        std::swap(array[idx], array[largest]);

        siftDown(largest);
    }
}

template <typename T, class Comporator>
void Heap<T, Comporator>::siftUp(size_t idx) {
    size_t parent;

    while (idx > 0) {
        parent = (idx - 1) / 2;
        if (comp(array[idx], array[parent])) {
            std::swap(array[idx], array[parent]);
            idx = parent;
        }
        else{return;}
    }
}

template <typename T, class Comporator>
void Heap<T, Comporator>::heapify() {
    for (int i = array.size() / 2 - 1; i >= 0; i--) {
        siftDown((size_t)i);
    }
}

template <typename T, class Comporator>
void Heap<T, Comporator>::insert(T element) {
    array.add(element);
    siftUp(array.size() - 1);
}

template <typename T, class Comporator>
T Heap<T, Comporator>::peekLast() const {
    return array[array.size() - 1];
}
template <typename T, class Comporator>
T Heap<T, Comporator>::peekMount() const {
    return array[0];
}
template <typename T, class Comporator>
T Heap<T, Comporator>::extractMount() {
    T mount = array[0];
    array[0] = peekLast();
    array.pop();
    siftDown(0);

    return mount;
}
