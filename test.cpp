#include "functions.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	//инициализация СЛУ
	Matrix circulant = buildCirculant(4, 343);
	Matrix freeColumn = buildMatrix(1, 4, 547);

	//косметика
	circulant.print();
	std::cout << std::endl;
	freeColumn.print();
	std::cout << std::endl;

	//решение циркулянтной системы
	std::vector<Complex> solution = solveCirculant(circulant, freeColumn);
	std::cout << std::endl;
	std::cout << "Solution:" << std::endl;
	for(unsigned int iter = 0; iter < solution.size(); ++iter)
	{
		solution[iter].print();
		std::cout << std::endl;
	}
}
