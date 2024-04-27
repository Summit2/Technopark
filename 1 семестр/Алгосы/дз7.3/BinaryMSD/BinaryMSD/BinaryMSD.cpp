
/*
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 1000000. Отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

#include <iostream>

bool pivot(const long long elem, const int biggest_bit) {
	//возвращает только старший бит ( 0 или 1)
	return (elem >> biggest_bit) & 1;
}

void binary_msd(long long int* arr, int left, int right, int biggest_bit) {

	if (biggest_bit < 0 || right - left < 2) {
		return;
	}

	int i = left;
	int j = right;
	while (i < j) {
		for (; i < j && !pivot(arr[i], biggest_bit); ++i) {};
		for (; j > i && pivot(arr[j - 1], biggest_bit); --j) {};

		if (i < j) {
			std::swap(arr[i], arr[j - 1]);
			++i;
			--j;
		}
	};

	binary_msd(arr, left , j, biggest_bit - 1 );
	binary_msd(arr, i ,right , biggest_bit - 1);
}

int main() {

	int n;
	std::cin >> n;

	long long int* arr = new long long int[n];
	for (int i = 0; i < n; ++i)
	{
		std::cin >> arr[i];
	}

	binary_msd(arr, 0, n, 63);

	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}



	delete[] arr;
	return 0;
}