
/*
Дано множество целых чисел из [0..109] размера n.
Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
10% перцентиль
медиана
90% перцентиль

Требования:
К дополнительной памяти: O(n).
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition.
Рекурсия запрещена.
Решение должно поддерживать передачу функции сравнения снаружи.

6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>

template<typename T>
struct DefaultComparator { //наш функтор

	bool operator()(const T& l, const T& r) const {
		return l < r;
	};
};

template <typename T, typename Comparator = DefaultComparator<T>>
int median_of_three(T* arr, const int left, const int middle, const int right, Comparator comp = Comparator()) {
	const int first = arr[left];
	const int second = arr[middle];
	const int third = arr[right];
	if (comp(second, first)) {
		if (comp(first, third)) {
			return left;
		}
		else {
			return (comp(third, second)) ? (middle) : (right);
		};
	}
	else {
		if (comp(second, third)) {
			return middle;
		}
		else {
			return (comp(third, first)) ? (left) : (right);
		};}
};
template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T* arr, int left, int right , Comparator comp = Comparator()) {

	if (right-left<0) {
		return 0;
	}

	// Подготовка опорного элемента методом "медиана трех"
	int pivot_ind = median_of_three(arr, left, (right + left)/2, right, comp);
	
	std::swap(arr[pivot_ind], arr[right]);

	T pivot = arr[right];

	int i = left;

	for (int j = i; j < right; ++j) {

		if (comp(arr[j], pivot)) {
			std::swap(arr[j], arr[i]);
			++i;
		}


	}
	std::swap(arr[right], arr[i]);
	return i;


}


template <typename T, typename Comparator = DefaultComparator<T>>
int find_k_stat(T* arr, int left, int right, int k, Comparator comp = Comparator())
{

	int pivot_pos;
	while (left <= right) {
		pivot_pos = partition(arr, left ,right, comp);
		if (pivot_pos == k) {
			return arr[k];
		}
		else if (pivot_pos > k)
		{
			right = pivot_pos - 1;
		}
		else {
			left = pivot_pos + 1;
		}



	}
};


int main() {

	int n;
	std::cin >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	std::cout << find_k_stat(arr, 0, n - 1, n/10) << std::endl;
	std::cout << find_k_stat(arr, 0, n - 1, n/2) << std::endl;
	std::cout << find_k_stat(arr, 0, n - 1, 9*n/10) << std::endl;
	


	delete[] arr;
	return 0;
}