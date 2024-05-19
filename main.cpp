#include <iostream>
#include <string>
#include "List.h"

int main(void)
{
	List<int> list1 = { 1, 2, 3, 4, 5 };
	for (const int &i : list1)
		std::cout << i << std::endl;

	List<std::string> list2 = { "Teste1", "Teste2", "Teste3", "Teste4", "Teste5" };
	for (const std::string &j : list2)
		std::cout << j << std::endl;

	return 0;
}