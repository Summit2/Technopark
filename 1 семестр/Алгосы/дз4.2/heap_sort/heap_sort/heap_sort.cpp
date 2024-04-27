
#include <iostream>
#include <cassert>


//структура для реализации алгоритма

struct User {
    int Id = 0;
    int Value = 0 ;

    bool operator>(const User& r) const {
        return Value > r.Value;
    }
};



template<typename T>
struct DefaultComparator { //наш функтор

    bool operator()(const T& l, const T& r) const {
        return l > r;
    }


};

struct Our_Comparator {
    bool operator()(const User& l, const User& r) const {
        return l.Value < r.Value;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap {

public:
    Heap(Comparator comp = Comparator()) {
        size = 0;
        capacity = 3;
        buffer = new T[capacity];
        this->comp = comp;
    };
    explicit Heap(T* arr, int arrSize, Comparator comp = Comparator())
    {

        size = arrSize;
        capacity = size + size / 2;
        buffer = new T[capacity];
        this->comp = comp;
        //перекопируем наш буфер
        for (size_t i = 0; i < size; i++)
        {
            buffer[i] = arr[i];
        };
        //построим кучу
        buildHeap();
    };

    ~Heap()
    {
        delete[] buffer;
    };

    Heap(const Heap&) = delete;
    Heap(Heap&&) = delete;

    Heap& operator=(Heap&&) = delete;
    Heap& operator=(const Heap&&) = delete;

private:
    T* buffer; //буффер
    int size; //размер кучи
    int capacity; //вместительность буфера
    Comparator comp; //функция сравнения для кучи

public:
    const T& top()const {
        return buffer[0];
    };
    T pop()  //вытащить top элемент из кучи
    {

        T top_elem = buffer[0];

        buffer[0] = buffer[size - 1];
        size--;
        if (size > 0) {
            siftDown(0);
        }

        return top_elem;
    };

    void push(const T& elem) {

        buffer[size] = elem;
        ++size;
        siftUp(size - 1);
        if (size == capacity) {
            grow();
        }
    };
    const int Size() {
        return size;
    }

private:
    void grow() {
        int newCapacity = capacity + capacity / 2;
        T* newBuffer = new T[newCapacity];
        for (size_t i = 0; i < size; i++)
        {
            newBuffer[i] = buffer[i];
        };
        delete[] buffer;
        buffer = newBuffer;
        capacity = newCapacity;
    };
    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            siftDown(i);
        }

    }
    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (!comp(buffer[i], buffer[parent])) {
                return;
            }

            std::swap(buffer[i], buffer[parent]);
            i = parent;
        }
    };
    void siftDown(int i) //проталкивание элемента вниз
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        // Ищем большего сына, если такой есть.
        int largest = i;
        if (left < size && comp(buffer[left], buffer[i])) {
            largest = left;
        };

        if (right < size && comp(buffer[right], buffer[largest])) {
            largest = right;
        };
        // Если больший сын есть, то проталкиваем корень в него.
        if (largest != i) {
            std::swap(buffer[i], buffer[largest]);
            siftDown(largest);
        };

    };



};



template < typename Comparator = DefaultComparator<User>>
void sortKMax(User* log, User* result, int n, int k, Comparator comp = Comparator()) {

    assert(k <= n); // k не может быть больше n

    Heap<User, Comparator> h(log, k, comp); //сразу для первых k элементов строим кучу за О(n)
    for (size_t i = k; i < n; i++)
    {
            if (!comp(log[i], h.top())) {
                h.pop();
                h.push(log[i]);
            }
    }
    //наша куча теперь из k наибольших элементов, добавим их в результирующий массив
    for (size_t i = 0; i < k; i++)
    {
        result[i] = h.pop();
    }

};

int main()
{
    int n, k;
    std::cin >> n >> k; //длина массива и k пользователей


    User* log = new User[n];

    for (size_t i = 0; i < n; i++)
    {
        std::cin >> log[i].Id >> log[i].Value;
    }

    User* result = new User[k]; //создаем массив для хранения результатов


    Our_Comparator comp;

    sortKMax(log, result, n, k, comp);
    for (size_t i = 0; i < k; i++)
    {
        std::cout << result[i].Id << " ";
    }

    delete[] result;
    delete[] log;
    return 0;
}

