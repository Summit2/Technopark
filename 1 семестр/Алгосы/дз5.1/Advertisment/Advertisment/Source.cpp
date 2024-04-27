/*
* 
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.

*/

#include <iostream>
#include <cstring>

struct Segment {
public:
	int Start;
	int End;

	bool operator<(const Segment& r) const {
		if (End == r.End) {
			return Start < r.Start; //при равенстве концов отрезков сортируем по началу отрезков
		}
		return End < r.End; //если концы отрезков разные, сортируем по концам
	}
};

template<typename T>
struct DefaultComparator { //наш функтор

	bool operator()(const T& l, const T& r) const {
		return l < r;
	};
};




template <typename T, typename Comparator = DefaultComparator<T>>
void Merge(T* FirstArr, const int FirstLen, T* SecondArr, const int SecondLen, T* ResultArr, Comparator comp = Comparator()) //Функция для слияния двух массивов
{
	for (int firstIter = 0, secondIter = 0, ResIter = 0; ; ResIter++) 
	{
		//если 1 массив опустел, докопируем из второго
		if (firstIter == FirstLen) {
			for (int i = secondIter, j = ResIter; i < SecondLen; i++, j++)
			{
				ResultArr[j] = SecondArr[i];
			}
			return;
		};
		//если 2 массив опустел, докопируем из первого
		if (secondIter == SecondLen) {
			for (int i = firstIter, j = ResIter; i < FirstLen; i++, j++)
			{
				ResultArr[j] = FirstArr[i];
			}
			return;
		};
		if (comp(FirstArr[firstIter], SecondArr[secondIter])) {
			ResultArr[ResIter] = FirstArr[firstIter];
			firstIter++;
		}
		else {
			ResultArr[ResIter] = SecondArr[secondIter];
			secondIter++;
		}
	};
};

template <typename T, typename Comparator = DefaultComparator<T>>
void MergeSort(T* arr, const int size, Comparator comp = Comparator()) //Сортировка слиянием
{
	if (size <= 1) {
		return;
	}
	int FirstLen = size / 2;
	int SecondLen = size - FirstLen;

	MergeSort(arr, FirstLen, comp);
	MergeSort(arr + FirstLen, SecondLen, comp); 
	
	T* temp = new T[size];
	Merge(arr, FirstLen, arr + FirstLen, SecondLen, temp);
	memcpy(arr, temp, sizeof(T) * size);

	delete[] temp;


};


int CountMinAdvertisments(Segment* arr, const int size) {

	if (size == 0) return 0;
	int count = 2; //начинаем с 2, т.к. если хотя бы 1 есть, то 2 рекламы мы ему покажем


	//итераторы, чтобы проверять, показали мы уже рекламу или нет
	int second_ad_iter = arr[0].End; 
	int first_ad_iter = second_ad_iter - 1;
	

	for (size_t i = 1; i < size; i++)
	{
		
		if (arr[i].Start > second_ad_iter) {

			//случай, когда мы не пересекаемся с предыдущими посетителями
			second_ad_iter = arr[i].End;
			first_ad_iter = second_ad_iter - 1;
			count += 2;
		}
		else {
			//случай, когда мы цепляем предыдущую рекламу

			if (arr[i].Start == second_ad_iter) {

				first_ad_iter = second_ad_iter;
				second_ad_iter = arr[i].End;
				count++;
			}
			else {
				if (arr[i].Start > first_ad_iter) {
					first_ad_iter = second_ad_iter;
					second_ad_iter = arr[i].End;
					count++;
				}
			}
		}
	}
	

	return count;
};

int main() {


	int n;
	std::cin >> n;
	
	Segment* schedule = new Segment [n];

	for (size_t i = 0; i < n; i++)
	{
		std::cin >> schedule[i].Start >> schedule[i].End;
	};


	MergeSort(schedule, n); 

	std::cout << CountMinAdvertisments(schedule, n);

	delete[] schedule;
	
	return 0;
}