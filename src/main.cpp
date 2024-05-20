#include <iostream>
#include <string>
#include "List.h"
#include "Set.h"

int main(void)
{
	std::cout << "Lista 1:" << std::endl;
	List<int> list1 = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
	list1.Insert(10, 4);
	for (const int &i : list1)
		std::cout << i << std::endl;

	std::cout << "\nConjunto 1:" << std::endl;
	Set<int> set1 = list1;
	set1.Insert(12, 1);
	set1.Insert(10, 1);
	for (const int& i : set1)
		std::cout << i << std::endl;

	std::cout << "\nLista 2:" << std::endl;
	List<std::string> list2 = { "Teste5", "Teste1", "Teste4", "Teste2", "Teste3" };
	list2.ForEach([](const std::string& i) {
		std::cout << i << std::endl;
	});

	return 0;
}