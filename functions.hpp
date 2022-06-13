#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "matrices.hpp"
#include "fourier.hpp"

#define GEN_LIM 10
#define PI 3.14159265

//генератор рандомных матриц
Matrix buildMatrix(unsigned int columnIndex, unsigned int rowIndex, int seed);

//генератор матрицы Фурье по некоторому основанию
Matrix buildFourier(unsigned int order, Complex base);

//эрмитово преобразование матрицы Фурье
Matrix transposeFourier(Matrix& matrix);

//возвращает значение ф(w) для дальнейшей работы с ним
std::vector<Complex> getFourierPolynom(Matrix& circulant, Complex fourierValue);

//возвращает значение полинома ф1(w)
std::vector<Complex> getSolution(std::vector<Complex>& tmpVector, Complex fourierValue);

//солвер циркулянтной системы
std::vector<Complex> solveCirculant(Matrix& circulant, Matrix& freeColumn);

//генератор рандомного циркулянта
Matrix buildCirculant(unsigned int order, int seed);



