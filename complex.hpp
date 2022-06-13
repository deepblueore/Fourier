#pragma once

#include <iostream>

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

		Complex pow(unsigned int power);

		//вывод числа
		void print() const;

		Complex operator+(Complex value)
		{
		        Complex result(this->getRe() + value.getRe(), this->getIm() + value.getIm());
		        return result;
		}

		Complex operator+=(Complex value)
		{
			return (*this + value);
		}

		Complex operator*(Complex value)
		{
		        double ReResult, ImResult;
		        ReResult = this->getRe() * value.getRe() - this->getIm() * value.getIm();
		        ImResult = this->getRe() * value.getIm() + this->getIm() * value.getRe();
		        Complex result(ReResult, ImResult);
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

			return Complex(ReResult, ImResult);
		}

		Complex operator/(double denom)
		{
			double ReResult = this->getRe() / denom;
			double ImResult = this->getIm() / denom;
			return Complex(ReResult, ImResult);
		}

		Complex operator=(Complex value)
		{
        		_imaginary = value.getIm();
        		_real = value.getRe();
        		return *this;
		}

};
