#pragma once

#include <vector>
#include "complex.hpp"
#include <utility>
#include <stdexcept>

class Matrix
{
	private:
		//порядок и тип матрицы:
		//0 - общий вид, 1 - теплицева,
		//2 - циркулянтная, 3 - Фурье
		unsigned int _columnIndex;
		unsigned int _rowIndex;
		int _type;
		std::vector<std::vector<Complex>> _coefs;
	public:
		Matrix(int type, unsigned int columnIndex, unsigned int rowIndex);

		//возвращает пару: число столбцов, число строк
		std::pair<unsigned int, unsigned int> getOrder() const;

		//возвращает коэффициент с произвольной позиции
		Complex getCoef(unsigned int columnPos, unsigned int rowPos) const;

		//устанавливает коэффициент в произвольную позицию
		void setCoef(unsigned int columnPos, unsigned int rowPos, Complex newCoef);

		//устанавливает тип матрицы
		void setType(int newType);

		//изменяет размер до ближайшей степени двойки
		void setCorrectSize();

		//распечатывает матрицу
		void print() const;
		
		Matrix operator*(Matrix matrix)
		{
			//подготовка к перемножению, инициализация произведения
			auto matrixParams = matrix.getOrder();
			Matrix result(0, std::get<0>(matrixParams), _rowIndex);

			for(unsigned int lRowIter = 0; lRowIter < _rowIndex; ++lRowIter)
			{
				for(unsigned int rColumnIter = 0; rColumnIter < std::get<0>(matrixParams); ++rColumnIter)
				{
					Complex sum;
					for(unsigned int multIter = 0; multIter < _columnIndex; ++multIter)
					{
						sum = sum + _coefs[multIter][lRowIter] * matrix.getCoef(rColumnIter, multIter);
					}
					result.setCoef(rColumnIter, lRowIter, sum);
				}
			}
			return result;
		}
};
