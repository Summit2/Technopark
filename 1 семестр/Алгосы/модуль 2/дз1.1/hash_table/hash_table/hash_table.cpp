
/*
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. 
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

*/
#include <iostream>
#include <string>
#include <cassert>
#include <vector>




template<typename T, typename H>
class HashTable {
public:
	// Все ячейки в состоянии Empty
	HashTable(int initial_size, const H & _hasher) :
			hasher(_hasher),
			size(initial_size),
			/*table(initial_size, nullptr),*/
			keys_сount(0)
		{  };
	
	~HashTable() {
		assert(false);
	};


	// Empty: return false
	// Key: key == Key ? return true : пробируемся дальше
	// Deleted: пробируемся дальше
	bool has(const T& key) {

	};

	// Empty: firstDeleted == -1 ?
	//  (записываем ключ в текущую ячейку, помечаем ячейку Key и return true) :
	//  (записываем ключ в firstDeleted, помечаем ячейку Key и return true)
	// Key: key == Key ? return false : пробируемся дальше
	// Deleted: встречали ли Deleted раньше ? пробируемся дальше : запоминаем индекс в firstDeleted
	bool add(const T& key) {

	};

	// Empty: return false
	// Key: key == Key ? помечаем ячейку Deleted и return true : пробируемся дальше
	// Deleted: пробируемся дальше
	bool delete_cell(const T& key) {

	};

private:
	H hasher;


	enum cell_state { EMPTY, KEY, DELETED }; // состояния ячеек

	struct hash_table_cell {
			T key; 
			unsigned int hash;
			cell_state state;
			hash_table_cell() : hash( 0 ), state( EMPTY ) {};
		};
	std::vector<hash_table_cell> table;
	unsigned int size;


	unsigned int keys_сount; // надо ли при открытой адресации? 

	void grow_table();
};

//
//
//template<class T, class H>
//HashTable<T, H>::~HashTable()
//{
//	for (int i = 0; i < table.size(); ++i) {
//		HashTableNode* node = table[i];
//		while (node != nullptr) {
//			HashTableNode* nextNode = node->Next;
//			delete node;
//			node = nextNode;
//		}
//	};
//};
//
//template<class T, class H>
//bool HashTable<T, H>::has(const T& key)
//{
//	unsigned int hash = hasher(key) % table.size();
//	HashTableNode* node = table[hash];
//	while (node != nullptr && node->Key != key) {
//		node = node->Next;
//	}
//	return node != nullptr;
//}
//
//template<class T, class H>
//bool HashTable<T, H>::add(const T& key)
//{
//	if (keysCount > 3 * table.size()) {
//		growTable();
//	}
//
//	unsigned int hash = hasher(key);
//	unsigned int listIndex = hash % table.size();
//	HashTableNode* node = table[listIndex];
//	while (node != nullptr && node->Key != key) {
//		node = node->Next;
//	}
//
//	if (node != nullptr) {
//		return false;
//	}
//
//	table[listIndex] = new HashTableNode(key, hash, table[listIndex]);
//	++keysCount;
//
//	return true;
//}
//
//template<class T, class H>
//bool HashTable<T, H>::delete_cell(const T& key)
//{
//	unsigned int hash = hasher(key) % table.size();
//	HashTableNode* node = table[hash];
//	HashTableNode* prevNode = nullptr;
//	while (node != nullptr && node->Key != key) {
//		prevNode = node;
//		node = node->Next;
//	}
//
//	if (node == nullptr) {
//		return false;
//	}
//
//	if (prevNode == nullptr) {
//		table[hash] = node->Next;
//	}
//	else {
//		prevNode->Next = node->Next;
//	}
//
//	delete node;
//	--keysCount;
//	return true;
//}
//
//template<class T, class H>
//void HashTable<T, H>::growTable()
//{
//	std::vector<HashTableNode*> newTable(table.size() * 2, nullptr);
//	for (int i = 0; i < table.size(); ++i) {
//		HashTableNode* node = table[i];
//		while (node != nullptr) {
//			HashTableNode* nextNode = node->Next;
//
//			unsigned int listIndex = node->Hash % newTable.size();
//			node->Next = newTable[listIndex];
//			newTable[listIndex] = node;
//
//			node = nextNode;
//		}
//	}
//
//	table = std::move(newTable);
//}

struct StringHasher {
	
	unsigned int operator()(const std::string& key) const {
		unsigned int hash = 0;
		for (unsigned int i = 0; i < key.size(); ++i) {
			hash = hash * 137 + key[i];
		}
		return hash;
	}
};

int main()
{
	StringHasher hasher;
	HashTable<std::string, StringHasher> table(8, hasher);
	char operation = 0;
	std::string word;
	while (std::cin >> operation >> word) {
		switch (operation) {
		case '+':
			std::cout << (table.add(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.delete_cell(word) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.has(word) ? "OK" : "FAIL") << std::endl;
			break;
		}
	}

	return 0;
}