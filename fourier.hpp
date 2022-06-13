#pragma once

#include <vector>
#include <cmath>
#include "complex.hpp"

#define PI 3.14159265

//функция реализует быстрое преобразование Фурье для многочленов
std::vector<Complex> fourierTransform(std::vector<Complex> coefs);
