#include "complex.hpp"
#include <iostream>

Complex::Complex()
{
	_imaginary = 0;
	_real = 0;
}

Complex::Complex(const double re, const double im)
{
	_imaginary = im;
	_real = re;
}

double Complex::getRe() const{return _real;}
double Complex::getIm() const{return _imaginary;}

void Complex::conjugate()
{
	_imaginary = -_imaginary;
}
void Complex::pow(unsigned int power)
{
	Complex result = *this;
	for(unsigned int iter = 0; iter < power; ++iter)
	{
		result *= *this;
	}
	*this = result;
}

void Complex::print() const
{
	std::cout << _real << " + " << _imaginary << "*i" << std::endl;
}
