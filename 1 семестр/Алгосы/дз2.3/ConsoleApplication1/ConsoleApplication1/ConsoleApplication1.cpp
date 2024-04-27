//Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
//A[0..n - 1] и B[0..m - 1].n » m.Найдите их пересечение.
//Требуемое время работы : O(m* log k), где k - позиция элементта B[m - 1] в массиве A..
//В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i - 1].n, k ≤ 10000.

#include <iostream>

int BinarySearch(const int* arr,int length, int elem, int& lower_bound) {

    int& first = lower_bound; //first - ссылка на нижнюю границу -> само значение lower_bound будет меняться от изменения first
    int last = length; 

    while (first < last) {
        int mid = (first + last) / 2;
        if (elem > arr[mid]) {
            first = mid + 1;
        }
        else {
            last = mid;
        }
    };
    if ( (arr[first] != elem) || (first == length) ) {
        return -1; // если элемента нет в массиве
    }
    else {
        return first; //по факту мы возвращаем ссылку на lower_bound (т.е. сам lower_bound)
                       
    }

   
};
void IntersectionTwoSets(const int* a, const int* b, int n, int m) //считаем, что b меньшей длины -> m<n
{
    int result;
    int lower_bound = 0; //для ускорения бинарного поиска (по заданию) не каждый раз будем идти с 0, а будем задавать нижнюю границу 

    for (size_t i = 0; i < m; i++) // идем по 2 массиву (меньшему)
    {
        result = BinarySearch(a, n, b[i], lower_bound); //
        // значение lower_bound возможно изменится после работы Binary_search
        if (result != -1) {
            std::cout << b[i] << ' ';
        }
        else {
            lower_bound = 0;
        };
    }
};

int main()
{
    int n, m;
    
    std::cin >> n >> m;

    int* a = new int[n];
    int* b = new int[m];


    for (size_t i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (size_t i = 0; i < m; i++)
    {
        std::cin >> b[i];
    }

    IntersectionTwoSets(a, b, n, m);


    delete[] a;
    delete[] b;


    return 0;
}