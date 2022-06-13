#include "matrices.hpp"

//возвращает ближайшую справа степень двойки
unsigned int getClosestOrder(unsigned int number)
{
	while(true)
	{
		unsigned int tmp = number;
		while(true)
		{
			if(tmp == 1 && number >= 2)
			{
				return number;
			}
			if(tmp % 2 != 0)
			{
				++number;
				break;
			}
			tmp /= 2;
		}
	}
}

Matrix::Matrix(int type, unsigned int columnIndex, unsigned int rowIndex)
{
	_type = type;
	_columnIndex = columnIndex;
	_rowIndex = rowIndex;
	std::vector<Complex> column;
	column.resize(_rowIndex);

	//первый коэф - столбец, второй - строка
	for(unsigned int iter = 0; iter < _columnIndex; ++iter)
	{
		_coefs.push_back(column);
	}
}

std::pair<unsigned int, unsigned int> Matrix::getOrder() const
{
	auto tmp = std::make_pair(_columnIndex, _rowIndex);
	return tmp;
}

void Matrix::setCoef(unsigned int columnPos, unsigned int rowPos, Complex newCoef)
{
	if(columnPos >= _columnIndex || rowPos >= _rowIndex)
	{
		throw std::runtime_error("Error: position doesn't exist");
	}
	_coefs[columnPos][rowPos] = newCoef;
}

void Matrix::setType(int newType)
{
	_type = newType;
}

void Matrix::setCorrectSize()
{
	//вычисление скорректированных размеров
	unsigned int correctColumn, correctRow;
	correctColumn = getClosestOrder(_columnIndex);
	correctRow = getClosestOrder(_rowIndex);

	//внесение правок в матрицу
	_columnIndex = correctColumn;
	_rowIndex = correctRow;
	_coefs.resize(_columnIndex);
	for(unsigned int columnIter = 0; columnIter < _columnIndex; ++columnIter)
	{
		_coefs[columnIter].resize(_rowIndex);
	}
}

Complex Matrix::getCoef(unsigned int columnPos, unsigned int rowPos) const
{
	return _coefs[columnPos][rowPos];
}

void Matrix::print() const
{
	for(unsigned int rowIter = 0; rowIter < _rowIndex; ++rowIter)
	{
		for(unsigned int columnIter = 0; columnIter < _columnIndex; ++columnIter)
		{
			_coefs[columnIter][rowIter].print();
		}
		std::cout << std::endl;
	}
}
