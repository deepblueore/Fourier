#include "complex.hpp"

void Complex::correctComplex()
{
	if(_real < LOWER && _real > -LOWER)
	{
		_real = 0;
	}
	if(_imaginary < LOWER && _imaginary > -LOWER)
	{
		_imaginary = 0;
	}
}

Complex::Complex()
{
	_imaginary = 0;
	_real = 0;
}

Complex::Complex(const double re, const double im)
{
	_imaginary = im;
	_real = re;
	correctComplex();
}

double Complex::getRe() const{return _real;}
double Complex::getIm() const{return _imaginary;}

Complex Complex::conjugate()
{
	return Complex(_real, -_imaginary);
}
Complex Complex::pow(unsigned int power)
{
	Complex result = *this;
	if(power == 0)
	{
		result = Complex(1, 0);
	}
	else
	{
		for(unsigned int iter = 0; iter < power - 1; ++iter)
		{
			result = *this * result;
		}
	}
	result.correctComplex();
	return result;
}

void Complex::print() const
{
	std::cout << _real << " + " << _imaginary << "*i ";
}
