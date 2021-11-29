#include "pch.h"
#include "CppUnitTest.h"

#include "../Jammed/Jammed.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestJammed
{
	TEST_CLASS(UnitTestJammed)
	{
	public:

		//тест считывания
		TEST_METHOD(Test_read)
		{
			istringstream input("ACM8002#");
			Combination l;
			l.read(input);
			
			Combination r;
			r.data[0][0] = 'A';
			r.data[0][1] = 'C';
			r.data[0][2] = 'M';
			r.data[0][3] = '8';
			r.data[1][0] = '0';
			r.data[1][1] = '0';
			r.data[1][2] = '2';
			r.data[1][3] = '#';
			Assert::AreEqual(compare(l, r), 0);
		}

		//тест сдвига
		TEST_METHOD(Test_shift)
		{
			istringstream input("ACM8002#");
			Combination l;
			l.read(input);

			Combination r;
			r.data[0][0] = 'A';
			r.data[0][1] = 'C';
			r.data[0][2] = 'M';
			r.data[0][3] = '#';
			r.data[1][0] = '0';
			r.data[1][1] = '0';
			r.data[1][2] = '2';
			r.data[1][3] = '8';
			
			Combination shifted = l.shift(-1, 0);
			Assert::AreEqual(compare(shifted, r), 0);
		}

		//тест сравнения
		TEST_METHOD(Test_compare)
		{
			istringstream input("ACM8002#");
			Combination l;
			l.read(input);

			istringstream input_("AMC8002#");
			Combination r;
			r.read(input_);

			Assert::IsTrue(compare(l, r) < 0);
		}

		//входные данные первого теста
		TEST_METHOD(Test_solution_1)
		{
			istringstream input("ACM8002#");
			Combination l;
			l.read(input);

			istringstream input_("ACM#2008");
			Combination r;
			r.read(input_);

			Assert::AreEqual(solution(l, r), 17);
		}

		//входные данные второго теста
		TEST_METHOD(Test_solution_2)
		{
			istringstream input("rogpmar#");
			Combination l;
			l.read(input);

			istringstream input_("program#");
			Combination r;
			r.read(input_);

			Assert::AreEqual(solution(l, r), 26);
		}
	};
}
