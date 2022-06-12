#pragma once

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
		void conjugate();
		void pow(unsigned int power);

		//вывод числа
		void print() const;

		Complex operator+(Complex value)
		{
		        Complex result(this->getRe() + value.getRe(), this->getIm() + value.getIm());
		        return result;
		}

		Complex operator*(Complex value)
		{
		        int ReResult, ImResult;
		        ReResult = this->getRe() * value.getRe() - this->getIm() * value.getIm();
		        ImResult = this->getRe() * value.getIm() + this->getIm() * value.getRe();
		        Complex result(ReResult, ImResult);
		        return result;
		}

		Complex operator=(Complex value)
		{
        		_imaginary = value.getIm();
        		_real = value.getRe();
        		return *this;
		}

};
