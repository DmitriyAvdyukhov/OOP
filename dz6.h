#pragma once
#include <iostream>



struct endl{};

std::ostream& operator<<(std::ostream& out, endl)
{
	out << "\n\n";
	out.clear();
	return out;
}

void GetInt()
{
	int i = 0;
	while (true) 
	{
		std::cout << "Please enter integer number: ";
		std::cin >> i;
		if (std::cin.good()) 
		{
			std::cin.ignore(10, '\n'); 
			break;
		} 
		std::cin.clear(); 
		std::cout << "You entered incorrect value. Please try again" << endl();
		std::cin.ignore(10, '\n'); 
	}
	std::cout << "You entered integer number: " << i << endl();
}




void Dz6()
{
	GetInt();
}