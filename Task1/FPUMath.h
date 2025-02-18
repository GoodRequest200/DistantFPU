#pragma once
class FPUMath
{
    public : double Task1(double x)
	{
		//1) f(x) = |(2x + 4) / 3|

		double two = 2.0, three = 3.0, four = 4.0;
		double result;

		_asm {	
			FINIT

			FLD three
			FLD four
			FLD two
			FLD x
			
			FMUL
			FADD
			FSUB

			FABS

			FSTP result
		}

		return result;
	}

	public: double Task2(double x)
	{
		//2) f(x) = sinPI√x + 8

		double eight = 8.0, PI = 3.14159265358979323846;
		double temp_sqrt;
		double result;

		_asm {
			FLD x
			FSQRT
			FSTP temp_sqrt

			FLD eight
			FLD temp_sqrt
			FLD PI
									
			FSIN
			FMUL
			FADD

			FSTP result
		}

		return result;
	}

	public: double Task3(double x)
	{
		//3) f(x) = 6cos2𝑥 + 5 sin𝑥−7

		double six = 6, two = 2, five = 5, seven = 7;
		double temp_sin;
		double result;

		_asm {
			FLD five
			FLD x
			FSIN 
			FMUL
			FSTP temp_sin

			FLD seven
			FLD temp_sin
			FLD six
			FLD two
			FLD x

			FMUL
			FCOS
			FMUL
			FADD
			FSUB

			FSTP result
		}

		return result;
	}

	public: double Task4(double x)
	{
		//1) f(x) = log2x +lnx

		double temp_ln;
		double result;

		_asm {


			fld1
			fld x
			fyl2x
			fstp result
		}

		/*_asm{
			FLD1
			FLD x 
			FYL2X
			FMUL
			FSTP temp_ln

			FLD temp_ln
			FLD x

			FYL2X
			FADD

			FSTP result
		}*/

		return result;
	}

	public: double Task5(double x, int num_terms)
	{
		/*5) f(x) =
			  x
		 =	  ∑(𝑥2 + 𝑛2)
			𝑛 = 1*/

		double result = 0.0;
		double term;
		double n_squared;

		for (int n = 1; n <= 10; ++n) {
			_asm {
				// Вычисление n_squared = n * n
				fild dword ptr[n]    // Загружаем n в ST(0)
				fmul st, st          // ST(0) = ST(0) * ST(0)
				fstp qword ptr[n_squared] //Сохраняем результат в n_squared

				// Вычисление term = x / (x^2 + n^2)
				fld qword ptr[x]         // Загружаем x в ST(0)
				fld qword ptr[x]         // Загружаем x в ST(0)
				fmul st, st          // ST(0) = ST(0) * ST(0) - x*x
				fadd qword ptr[n_squared]      // ST(0) = ST(0) + n_squared
				fdiv qword ptr[x]          // ST(0) = x /  (x*x + n_squared)
				fstp qword ptr[term]     // Сохраняем результат в term
			}
			result += term;
		}
		return result;
	}
};

