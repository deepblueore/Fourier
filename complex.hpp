#pragma once

#include <iostream>

#define LOWER 0.001

class Complex
{
	private:
		double _imaginary;
		double _real;
	public:
		Complex();
		Complex(const double re, const double im);
		double getRe() const;
		double getIm() const;

		//комплексное сопряжение
		Complex conjugate();

		//возведение в степень
		Complex pow(unsigned int power);

		//корректировка погрешностей вычислений
		void correctComplex();

		//вывод числа
		void print() const;

		Complex operator+(Complex value)
		{
		        Complex result(this->getRe() + value.getRe(), this->getIm() + value.getIm());
			result.correctComplex();
		        return result;
		}

		Complex operator+=(Complex value)
		{
			Complex result = *this + value;
			result.correctComplex();
			return result;
		}

		Complex operator*(Complex value)
		{
		        double ReResult, ImResult;
		        ReResult = this->getRe() * value.getRe() - this->getIm() * value.getIm();
		        ImResult = this->getRe() * value.getIm() + this->getIm() * value.getRe();
		        Complex result(ReResult, ImResult);
			result.correctComplex();
		        return result;
		}

		Complex operator/(Complex denom)
		{
			double ReResult, ImResult;

			Complex nom(this->getRe(), this->getIm());
			Complex denomConj(denom.getRe(), denom.getIm());
			denomConj.conjugate();

			Complex nomResult = nom * denomConj;
			double denomResult = (denom * denomConj).getRe();
			ReResult = nomResult.getRe() / denomResult;
			ImResult = nomResult.getIm() / denomResult;

			Complex result(ReResult, ImResult);
			result.correctComplex();
			return result;
		}

		Complex operator/(double denom)
		{
			double ReResult = this->getRe() / denom;
			double ImResult = this->getIm() / denom;

			Complex result(ReResult, ImResult);
			result.correctComplex();
			return Complex(ReResult, ImResult);
		}

		Complex operator=(Complex value)
		{
        		_imaginary = value.getIm();
        		_real = value.getRe();
        		return *this;
		}

};
