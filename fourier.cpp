#include "fourier.hpp"

std::vector<Complex> fourierTransform(std::vector<Complex> coefs)
{
        //условие выхода из рекурсии
        unsigned int size = coefs.size();
        if(size == 1)
        {
                return coefs;
        }

        //операцию проведем повторно для мономов при четных и нечетных степенях
        std::vector<Complex> even, odd;
        even.resize(size/2);
        odd.resize(size/2);
        for(unsigned int iter = 0; iter < size/2; ++iter)
        {
                even[iter] = coefs[iter * 2];
                odd[iter] = coefs[iter * 2 + 1];
        }

        //рекурсивно запускаем БПФ
        std::vector<Complex> newOdd = fourierTransform(odd);
        std::vector<Complex> newEven = fourierTransform(even);
        Complex fourierBase(cos(2 * PI / size), sin(2 * PI / size));
	Complex base(1, 0);

	//восстанавливаем многочлен
	std::vector<Complex> newCoefs;
	newCoefs.resize(size);
	for(int iter = 0; iter < size/2; ++iter)
	{
		Complex tmp = base * newOdd[iter];
		newCoefs[iter] = newEven[iter] + tmp;
		newCoefs[iter + size/2] = newEven[iter] - tmp;
		base = base * fourierBase;
	}

	return newCoefs;
}
