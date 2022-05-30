#include "dz5.h"

namespace pair
{
	void TestPair()
	{
		{
			Pair1<int> p1(6, 9);
			std::cout << p1 << std::endl;
			const Pair1<double> p2(3.4, 7.8);
			std::cout << p2 << std::endl;
		}
		{
			Pair<int, double> p1(6, 7.8);
			std::cout << p1 << std::endl;
			const Pair<double, int> p2(3.4, 5);
			std::cout << p2 << std::endl;
		}
		{
			StringValuePair<int> svp("Amazing", 7);
			std::cout << svp << std::endl;
		}
	}
}

void Dz5()
{
	pair::TestPair();
}
