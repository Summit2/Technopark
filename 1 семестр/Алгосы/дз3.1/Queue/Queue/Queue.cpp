/*
Реализовать очередь с динамическим зацикленным буфером.
Обрабатывать команды push back и pop front.
*/
#include <iostream>
#include<cassert>


class Queue {

public:
	Queue();
	~Queue();

	Queue(Queue&) = delete;
	Queue& operator=(const Queue&) = delete; //не разрешаем использование оператора копирования и оператора присваивания  

	void PushBack(int data);
	int PopFront();
	int Size() const; // const показывает, метод Size не меняет значения полей класса

	
private:
	int* buffer;
	int bufferSize; //размер буфера
	int head; //индекс head
	int tail; //индекс tail
	int size; //количество заполненных элементов в буфере (его актуальный размер)


	//pivate методы
	void ReAllocate();

};

Queue::Queue() : head(0), tail(-1), bufferSize(4), size(0) //конструктор
{
	//как мы видим, значение tail у нас -1. После первого добавления элемента оно начнет указывать на первый элемент, т.е. станет = 0 
	buffer = new int[bufferSize];

}
Queue::~Queue() //деструктор
{
	delete[] buffer;
}
int Queue::Size() const { 
	return size;
}

void Queue::ReAllocate() {
	int newSize = bufferSize + bufferSize / 2;
	int* BiggerBuffer = new int[newSize]; //в полтора раза увеличиваем размер
	for (size_t j=0, i = head; j < size; j++, i++)
	{
		BiggerBuffer[j] =  buffer[i % bufferSize] ; 
	};

	head = 0; 
	tail = size - 1;
	delete[] buffer; //удаляем старый буфер
	buffer = BiggerBuffer; // теперь мы ссылаемся на новый буфер
	bufferSize = newSize;
}

void Queue::PushBack(int data) {

	tail =( tail + 1) % bufferSize; //здесь мы инкрементируем tail, но за границы буфера мы не выйдем
	buffer[tail] = data;

	++size;
	
	if (bufferSize == size) {
		ReAllocate();
	}

}
int Queue::PopFront() {

	assert(size > 0);

	int data_to_return = buffer[head];
	head = (head + 1) % bufferSize;
	--size;

	return data_to_return;

}


int main()
{
	Queue q;
	
	int n = 0;
	std::cin >> n;
	bool result = true;
	for (int i = 0; i < n; i++)
	{
		int command = 0;
		int data = 0;
		std::cin >> command >> data;

		switch (command) {
		case 2: //операция PopFront()
			if (q.Size()>0) {
				result = result && q.PopFront() == data;
			}
			else {
				
				result = result && data == -1;
			}
			

			break;
		case 3: //операция PushBack()
			q.PushBack(data);
			break;
		default:
			assert(false);
		};
	}

	std::cout << (result ? "YES" : "NO");

	return 0;
}

