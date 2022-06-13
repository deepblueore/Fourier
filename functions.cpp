#include "functions.hpp"

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

std::vector<Complex> calculateFourierPolynom(Matrix& circulant)
{
	//выписываем первую строку циркулянта в вектор
	unsigned int size = std::get<0>(circulant.getOrder());
	std::vector<Complex> coefs;
	coefs.resize(size);
	for(unsigned int columnIter = 0; columnIter < size; ++columnIter)
	{
		coefs[columnIter] = circulant.getCoef(columnIter, 0);
	}

	//преобразуем вектор коэффициентов с помощью БПФ
	std::vector<Complex> newCoefs = fourierTransform(coefs);

	return newCoefs;
}

std::vector<Complex> getSolution(std::vector<Complex>& tmpVector)
{
	std::vector<Complex> newVector = fourierTransform(tmpVector);

	return newVector;
}

std::vector<Complex> solveCirculant(Matrix& circulant, Matrix& freeColumn)
{
	//небольшая обработка ошибок
	if(std::get<0>(freeColumn.getOrder()) != 1)
	{
		throw std::runtime_error("Error: free column can't be a matrix");
	}

	//корректируем размеры матрицы СЛУ
//	circulant.setCorrectSize();

	//вычисляем подходящий комплексный корень из единицы
	unsigned int order = std::get<0>(circulant.getOrder());
	Complex fourierRoot(cos(2 * PI / order), sin(2 * PI / order));

	//строим матрицу Фурье для СЛУ
	Matrix fourier = buildFourier(order, fourierRoot);

	std::cout << "Fourier matrix:" << std::endl;
	fourier.print();
	std::cout << std::endl;

	//вычисляем (F*)freeColumn
	Matrix transFourier = transposeFourier(fourier);
	Matrix multiplicatedTMP = transFourier * freeColumn;

	//уравнение сводится к x=Fy, для его решения вычислим y - промежуточное уравнение:
	//1) вычисляем вектор значений полинома ф(w)
	std::vector<Complex> polynomValues = calculateFourierPolynom(circulant);

	//2) вычисляем промежуточные координаты решения
	std::vector<Complex> tmpSolved;
	tmpSolved.resize(order);
	for(unsigned int tmpIter = 0; tmpIter < order; ++tmpIter)
	{
		//вычисляем координату y
		tmpSolved[tmpIter] = multiplicatedTMP.getCoef(0, tmpIter) / polynomValues[tmpIter];
	}

	//теперь отыщем координаты вектора x
	std::vector<Complex> solution;
	solution.resize(order);
	std::vector<Complex> solutionValues = getSolution(tmpSolved);
	for(unsigned int tmpIter = 0; tmpIter < order; ++tmpIter)
	{
		solution[tmpIter] = solutionValues[tmpIter] / order;
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
