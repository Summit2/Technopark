

#include <iostream>
#include <cassert>
#include <string>
class Stack {

	char* buffer;
	int size;



public:
	Stack(int capacity) {

		this->size = -1;

		buffer = new char[size];
	}
	~Stack() {
		delete[] buffer;
	}
	void push(char value) {
		size++;
		buffer[size] = value;
		
	}
	char top() {
		return buffer[size];
	}
	char pop() {
		assert(size != -1);
		size--;
		return buffer[size + 1];
	}
	bool is_empty() {
		return size == -1;
	}


};
int main()
{
	

	std::string str;
	
	
	std::cin >> str;
	
	

	Stack stack(str.length());
	
	for (char elem : str) {
		if (elem == '(') {
			stack.push(elem);
		}
		else  if (!stack.is_empty() && stack.top()=='(') {
			stack.pop();
		}
		else {
			std::cout << "NO";
			return 0;
		}
	}
	if (stack.is_empty()) {
		std::cout << "YES";

	}
	else {
		std::cout << "NO";
	}


	return 0;
}
;