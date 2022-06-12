#include <cstdlib>
#include <ctime>
#include "matrices.hpp"

#define GEN_LIM 10

//вспомогательное взятие модуля
int abs(int number)
{
	if(number >= 0)
	{
		return number;
	}
	return -number;
}

//генератор рандомных матриц
Matrix genMatrix(unsigned int columnIndex, unsigned int rowIndex, int seed)
{
	srand(time(NULL)+seed);

	//генерация матрицы
	Matrix general(0, columnIndex, rowIndex);
	for(unsigned int columnIter = 0; columnIter < columnIndex; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < rowIndex; ++rowIter)
		{
			Complex tmp(rand()%GEN_LIM, rand()%GEN_LIM);
			general(columnIter, rowIter, tmp);
		}
	}

	return general;
}

//генератор матрицы Фурье по некоторому основанию
Matrix buildFourier(unsigned int order, Complex base)
{
	//все умножения проводим заранее
	unsigned int maxDegree = (order-1)*(order-1) + 1;
	Complex* mults = new Complex[maxDegree + 1];
	for(unsigned int iter = 0; iter < maxDegree; ++iter)
	{
		mults[iter] = base.pow(iter);
	}

	//генерация матрицы
	Matrix fourier(3, order, order);
	for(unsigned int columnIter = 0; columnIter < order; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < order; ++rowIter)
		{
			fourier.setCoef(columnIter, rowIter, mults[columnIter * rowIter]);
		}
	}

	delete[] mults;
	return fourier;
}

//генератор рандомного циркулянта
Matrix buildCirculant(unsigned int order, int seed)
{
	srand(time(NULL)+seed);

	//генерацию элементов проводим заранее
	Complex* elems = new Complex[order];
	for(unsigned int iter = 0; iter < order; ++iter)
	{
		order[iter] = Complex(rand()%GEN_LIMIT, 0);
	}

	//генерация матрицы
	Matrix circulant(2, order, order);
	for(unsigned int columnIter = 0; columnIter < order; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < order; ++rowIter)
		{
			circulant.setCoef(columnIter, rowIter, elems[columnIter - rowIter]);
		}
	}

	delete[] elems;
	return circulant;
}
