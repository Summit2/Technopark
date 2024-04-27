/*
* 
� ������������ ������ �������������� ����� �������. �������� ���������� ������� � ����� ����������� (��� ����� �����). ������� ���������� ���������� �������� ������� 2 �������.  ������� ����� ������������� ������ � ������������� ������� �������. ���������� ����� ������ ������� �� ������� ������� �� ������� ����� �� ��������.
� ������ ������ ������� ����� ������������ ������ ���� �������. ���������, ��� ������� ������������ ���������. ���� ������� ������������ � ������ ����� ��� �������, �� ���������, ��� ���������� ����� � ����������. ��������� ���������� ����������� ����� ������� �������.

*/

#include <iostream>
#include <cstring>

struct Segment {
public:
	int Start;
	int End;

	bool operator<(const Segment& r) const {
		if (End == r.End) {
			return Start < r.Start; //��� ��������� ������ �������� ��������� �� ������ ��������
		}
		return End < r.End; //���� ����� �������� ������, ��������� �� ������
	}
};

template<typename T>
struct DefaultComparator { //��� �������

	bool operator()(const T& l, const T& r) const {
		return l < r;
	};
};




template <typename T, typename Comparator = DefaultComparator<T>>
void Merge(T* FirstArr, const int FirstLen, T* SecondArr, const int SecondLen, T* ResultArr, Comparator comp = Comparator()) //������� ��� ������� ���� ��������
{
	for (int firstIter = 0, secondIter = 0, ResIter = 0; ; ResIter++) 
	{
		//���� 1 ������ �������, ���������� �� �������
		if (firstIter == FirstLen) {
			for (int i = secondIter, j = ResIter; i < SecondLen; i++, j++)
			{
				ResultArr[j] = SecondArr[i];
			}
			return;
		};
		//���� 2 ������ �������, ���������� �� �������
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
void MergeSort(T* arr, const int size, Comparator comp = Comparator()) //���������� ��������
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
	int count = 2; //�������� � 2, �.�. ���� ���� �� 1 ����, �� 2 ������� �� ��� �������


	//���������, ����� ���������, �������� �� ��� ������� ��� ���
	int second_ad_iter = arr[0].End; 
	int first_ad_iter = second_ad_iter - 1;
	

	for (size_t i = 1; i < size; i++)
	{
		
		if (arr[i].Start > second_ad_iter) {

			//������, ����� �� �� ������������ � ����������� ������������
			second_ad_iter = arr[i].End;
			first_ad_iter = second_ad_iter - 1;
			count += 2;
		}
		else {
			//������, ����� �� ������� ���������� �������

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