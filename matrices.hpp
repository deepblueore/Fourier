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
		
		Matrix operator*(Matrix matrix)
		{
			//подготовка к перемножению, инициализация произведения
			auto matrixParams = matrix.getOrder();
			Matrix result(0, std::get<0>(matrixParams), _rowIndex);

			//свитч-кейс немного странный, но на самом деле
			//перемножаются только:
			//> квадратные матрицы степени двойки (частный случай на n^2)
			//> матрица и вектор (очень частный случай)
			switch(std::get<0>(matrixParams))
			{
				case 1:
					for(rowIter = 0; rowIter < _rowIndex; ++rowIter)
					{
						Complex sum();
						for(multIter = 0; multIter < _columnIndex; ++multIter)
						{
							sum += _coefs[multIter][rowIter] * matrix.getCoef(1, multIter);
						}
						result.setCoef(1, rowIter, sum);
					}
					break;
				default:
			}
		}
};
