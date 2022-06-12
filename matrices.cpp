#include "matrices.hpp"

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
	return tmp
}

void Matrix::setCoef(unsigned int columnPos, unsigned int rowPos, Complex newCoef)
{
	if(columnPos >= _columnIndex || rowPos >= _rowIndex)
	{
		throw std::runtime_error("Error: position doesn't exist");
	}
	_coefs[columnPos][rowPos] = newCoef;
}

void setType(int newType)
{
	_type = newType;
}

Complex Matrix::getCoef(unsigned int columnPos, unsigned int rowPos) const
{
	return _coefs[columnPos][rowPos];
}
