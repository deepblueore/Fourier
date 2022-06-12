#include "matrices.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define GEN_LIM 10

void genMatrix(Matrix& matrix, int seed)
{
	unsigned int order = matrix.getOrder();
	srand(time(NULL)+seed);

	for(unsigned int iter = 0; iter < order; ++iter)
	{
		for(unsigned int jter = 0; jter < order; ++jter)
		{
			Complex tmp(rand()%GEN_LIM, rand()%GEN_LIM);
			matrix.setCoef(iter, jter, tmp);
		}
	}
}

int main()
{
	Complex a(1, 2);
	Complex b(3, 4);
	Complex num = a * b;
	num.print();

	num.conjugate();
	num.print();
}
