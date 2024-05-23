#include <iostream>
#include <string>

#include "UniqList.h"
#include "Stack.h"
#include "Tree.h"

int main(void)
{
	Tree<int> tree = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	tree.ForEach([](const int& i) {
		std::cout << i << std::endl;
	});

	/*std::cout << "Lista:" << std::endl;
	List<int> list1 = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	list1.Insert(10, 4);
	list1.Set(5, 6);
	for (const int& i : list1)
		std::cout << i << std::endl;
	std::cout << std::endl;
	list1.Remove(6);
	list1.Delete(4);

	std::cout << "Lista única:" << std::endl;
	UniqList<int> uniq = list1;
	uniq.Insert(12, 1);
	uniq.Insert(10, 1);
	uniq.Set(2, 3);
	uniq.Set(15, 5);
	for (const int& i : uniq)
		std::cout << i << std::endl;
	std::cout << std::endl;

	std::cout << "Pilha:" << std::endl;
	Stack<int> stack = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (const int& i : stack)
		std::cout << i << std::endl;
	std::cout << std::endl;
	stack.Insert(10, 4);
	stack.Set(5, 6);
	for (const int& i : stack)
		std::cout << i << std::endl;
	std::cout << std::endl;
	stack.Remove(6);
	stack.Delete(4);
	stack.ForEach([](const int& i) {
		std::cout << i << std::endl;
	});*/

	return 0;
}