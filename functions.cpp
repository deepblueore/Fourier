#include "functions.hpp"

//вспомогательное взятие модуля
int abs(int number)
{
	if(number >= 0)
	{
		return number;
	}
	return -number;
}

Matrix buildMatrix(unsigned int columnIndex, unsigned int rowIndex, int seed)
{
	srand(time(NULL)+seed);

	//генерация матрицы
	Matrix general(0, columnIndex, rowIndex);
	for(unsigned int columnIter = 0; columnIter < columnIndex; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < rowIndex; ++rowIter)
		{
			Complex tmp(rand()%GEN_LIM, 0);
			general.setCoef(columnIter, rowIter, tmp);
		}
	}

	return general;
}

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

Matrix transposeFourier(Matrix& matrix)
{
	auto orderPair = matrix.getOrder();
	unsigned int order = std::get<0>(orderPair);

	Matrix transposed(3, order, order);
	for(unsigned int columnIter = 0; columnIter < order; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < order; ++rowIter)
		{
			transposed.setCoef(rowIter, columnIter, matrix.getCoef(columnIter, rowIter).conjugate());
		}
	}

	return transposed;
}

Complex getFourierPolynom(Matrix& circulant, Complex fourierValue)
{
	Complex result;
	for(unsigned int columnIter = 0; columnIter < std::get<0>(circulant.getOrder()); ++columnIter)
	{
		result = result + circulant.getCoef(columnIter, 0) * fourierValue.pow(columnIter);
	}
	return result;
}

Complex getSolution(Matrix& tmpVector, Complex fourierValue)
{
        Complex result;
        for(unsigned int rowIter = 0; rowIter < std::get<1>(tmpVector.getOrder()); ++rowIter)
        {
                result = result + tmpVector.getCoef(0, rowIter) * fourierValue.pow(rowIter);
        }
        return result;
}

std::vector<Complex> solveCirculant(Matrix& circulant, Matrix& freeColumn)
{
	//небольшая обработка ошибок
	if(std::get<0>(freeColumn.getOrder()) != 1)
	{
		throw std::runtime_error("Error: free column can't be a matrix");
	}

	//корректируем размеры матрицы СЛУ
	circulant.setCorrectSize();

	//вычисляем подходящий комплексный корень из единицы
	unsigned int order = std::get<0>(circulant.getOrder());
	Complex fourierRoot(cos(2 * PI / order), sin(2 * PI / order));

	//строим матрицу Фурье для СЛУ
	Matrix fourier = buildFourier(order, fourierRoot);

	//вычисляем (F*)freeColumn
	Matrix transFourier = transposeFourier(fourier);
	Matrix multiplicatedTMP = transFourier * freeColumn;

	//уравнение сводится к x=Fy, для его решения вычислим y
	Matrix tmpSolved(0, 1, order);
	for(unsigned int tmpIter = 0; tmpIter < order; ++tmpIter)
	{
		//вычисляем ф(w^tmpIter)
		Complex polynomValue = getFourierPolynom(circulant, fourier.getCoef(1, tmpIter));

		//вычисляем координату y
		tmpSolved.setCoef(0, tmpIter, multiplicatedTMP.getCoef(0, tmpIter) / polynomValue);
	}

	//теперь отыщем координаты вектора x
	std::vector<Complex> solution;
	solution.resize(order);
	for(unsigned int tmpIter = 0; tmpIter < order; ++tmpIter)
	{
		Complex polynomValue = getSolution(tmpSolved, fourier.getCoef(1, tmpIter));
		solution[tmpIter] = polynomValue / order;
	}

	return solution;
}

Matrix buildCirculant(unsigned int order, int seed)
{
	srand(time(NULL)+seed);

	//генерацию элементов проводим заранее
	Complex* elems = new Complex[order];
	for(unsigned int iter = 0; iter < order; ++iter)
	{
		elems[iter] = Complex(rand()%GEN_LIM, 0);
	}

	//генерация матрицы
	Matrix circulant(2, order, order);
	for(unsigned int columnIter = 0; columnIter < order; ++columnIter)
	{
		for(unsigned int rowIter = 0; rowIter < order; ++rowIter)
		{
			if(columnIter >= rowIter)
			{
				circulant.setCoef(columnIter, rowIter, elems[columnIter-rowIter]);
			}
			else
			{
				circulant.setCoef(columnIter, rowIter, elems[order + columnIter - rowIter]);
			}
		}
	}

	delete[] elems;
	return circulant;
}
