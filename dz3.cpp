#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <vector>
#include <numeric>
#include <sstream>

#include "dz3.h"

namespace figures
{
	//-----------Parallelogram-----------

	Parallelogram::Parallelogram() = default;

	Parallelogram::Parallelogram(double side_x, double side_y)
		: side_x_(side_x), side_y_(side_y)
	{}

	double Parallelogram::Area() const
	{
		return side_x_ * side_y_;
	}

	double Parallelogram::GetSideX() const
	{
		return side_x_;
	}

	//-----------Circle----------------------

	Circle::Circle() = default;

	Circle::Circle(double radius) : radius_(radius) {}

	double Circle::Area() const
	{
		return M_PI * pow(radius_, 2);
	}

	std::string Circle::GetNameFigure() const
	{
		return "Circle";
	}

	//-----------------Rhombus---------------------

	Rhombus::Rhombus() = default;

	Rhombus::Rhombus(double side, double height) : Parallelogram(side, height) {}

	std::string Rhombus::GetNameFigure() const
	{
		return "Rhombus";
	}

	//-----------------Square-------------------

	Square::Square() = default;

	Square::Square(double side) : Parallelogram(side) {}

	double Square::Area() const
	{
		return pow(GetSideX(), 2);
	}

	std::string Square::GetNameFigure() const
	{
		return "Square";
	}


	//-------------------Rectangle--------------

	Rectangle::Rectangle() = default;

	Rectangle::Rectangle(double side_x, double side_y) : Parallelogram(side_x, side_y) {}

	std::string Rectangle::GetNameFigure() const
	{
		return "Rectangle";
	}

	//--------------------TestArea-------------------

	void TestArea()
	{ 
		size_t count = 0;
		std::cout << "How many figures do you want qreate" << std::endl;
		std::cin >> count;
		std::vector<std::unique_ptr<Figure>> figures;
		figures.reserve(count);
		for (size_t i = 0; i < count; ++i)
		{			
			std::string figure;
			std::cout << "Enter figure: \"Circle\" or \"Rhombus\" or \"Square\" or \"Rectangle\"" << std::endl;
			std::cin >> figure;
			if (figure == "Circle")
			{
				double radius = 0;
				std::cout << "Enter radius circle" << std::endl;
				std::cin >> radius;
				figures.push_back(std::make_unique<Circle>(Circle(radius)));
			}
			else if (figure == "Rhombus")
			{
				double side, height;
				std::cout << "Enter length of side and height rhombus" << std::endl;
				std::cin >> side >> height;
				figures.push_back(std::make_unique<Rhombus>(Rhombus(side, height)));
			}
			else if (figure == "Square")
			{
				double side;
				std::cout << "Enter length of square's side " << std::endl;
				std::cin >> side;
				figures.push_back(std::make_unique<Square>(Square(side)));
			}
			else if (figure == "Rectangle")
			{
				double side_x, side_y;
				std::cout << "Enter length of side \"x \"and length of side \"y \"" << std::endl;
				std::cin >> side_x >> side_y;
				figures.push_back(std::make_unique<Rectangle>(Rectangle(side_x, side_y)));
			}
		}
		for (auto it = figures.begin(); it != figures.end(); ++it)
		{
			std::cout << "Area " << it->get()->GetNameFigure() << " equal: " << it->get()->Area() << std::endl;
		}
	}	
	
}// end namespace figures

namespace cars
{
	//--------------Car-------------

	Car::Car()
	{
		std::cout << "Default " << __FUNCTION__ << std::endl;
	}

	Car::Car(const std::string& company, const std::string& model) : company_(company), model_(model)
	{
		std::cout << "With parameters " << __FUNCTION__ << std::endl;
	}

	Car::~Car()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//--------------PassengerCar--------------

	PassengerCar::PassengerCar()
	{
		std::cout << "Default " << __FUNCTION__ << std::endl;
	}

	PassengerCar::PassengerCar(const std::string& company, const std::string& model)
		: Car(company, model)
	{
		std::cout << "With parameters " << __FUNCTION__ << std::endl;
	}

	PassengerCar::~PassengerCar()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//-------------Bus------------------

	Bus::Bus()
	{
		std::cout << "Default " << __FUNCTION__ << std::endl;
	}

	Bus::Bus(const std::string& company, const std::string& model)
		: Car(company, model)
	{
		std::cout << "With parameters " << __FUNCTION__ << std::endl;
	}

	Bus::~Bus()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//-------------Minivan---------------

	Minivan::Minivan()
	{
		std::cout << "Default " << __FUNCTION__ << std::endl;
	}

	Minivan::Minivan(const std::string& company, const std::string& model)
		: PassengerCar(company, model), Bus(company, model)
	{
		std::cout << "With parameters " << __FUNCTION__ << std::endl;
	}

	Minivan::~Minivan()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	//------------TestCars-------------

	void TestCars()
	{
		PassengerCar passenger_car("BMW", "X3");
		Bus bus("Mercedec", "XL300");
		Minivan minivan("WV", "500");		
	}

}// end namespace cars


namespace fraction
{
	Fraction::Fraction() = default;

	Fraction::Fraction(int value)
		: numerator_(value)
		, denominator_(1)
	{}

	Fraction::Fraction(int numerator, int denominator)
		: numerator_(numerator)
		, denominator_(denominator)
	{
		Normalize();
	}

	int Fraction::Numerator() const
	{
		return numerator_;
	}

	int Fraction::Denominator() const
	{
		return denominator_;
	}

	Fraction& Fraction::operator+=(Fraction right)
	{
		numerator_ = numerator_ * right.denominator_ + right.numerator_ * denominator_;
		denominator_ *= right.denominator_;
		Normalize();
		return *this;
	}

	Fraction& Fraction::operator-=(Fraction right)
	{
		numerator_ = numerator_ * right.denominator_ - right.numerator_ * denominator_;
		denominator_ *= right.denominator_;
		Normalize();
		return *this;
	}

	Fraction& Fraction::operator*=(Fraction right)
	{
		numerator_ *= right.numerator_;
		denominator_ *= right.denominator_;
		Normalize();
		return *this;
	}

	Fraction& Fraction::operator/=(Fraction right)
	{
		numerator_ *= right.denominator_;
		denominator_ *= right.numerator_;
		Normalize();
		return *this;
	}

	double Fraction::GetValueFraction() const
	{
		return numerator_ * 1. / denominator_;
	}

	void Fraction::Normalize()
	{
		if (denominator_ < 0)
		{
			numerator_ = -numerator_;
			denominator_ = -denominator_;
		}
		int n = std::gcd(numerator_, denominator_);
		numerator_ /= n;
		denominator_ /= n;
	}

	Fraction operator+(Fraction value)
	{
		return value;
	}

	Fraction operator-(Fraction value)
	{
		return { -value.Numerator(), value.Denominator() };
	}

	Fraction operator+(Fraction left, Fraction right)
	{
		return left += right;
	}

	Fraction operator-(Fraction left, Fraction right)
	{
		return left -= right;
	}

	Fraction operator*(Fraction left, Fraction right)
	{
		return left *= right;
	}

	Fraction operator/(Fraction left, Fraction right)
	{
		return left /= right;
	}

	bool operator==(Fraction left, Fraction right)
	{
		return left.Numerator() == right.Numerator() &&
			left.Denominator() == right.Denominator();
	}

	bool operator!=(Fraction left, Fraction right)
	{
		return !(left == right);
	}

	bool operator>(Fraction left, Fraction rigth)
	{		
		return left.GetValueFraction() > rigth.GetValueFraction();
	}

	bool operator<(Fraction left, Fraction rigth)
	{		
		return !(left > rigth);
	}

	bool operator<=(Fraction left, Fraction rigth)
	{		
		return left.GetValueFraction() <= rigth.GetValueFraction();
	}

	bool operator>=(Fraction left, Fraction rigth)
	{		
		return !(left < -rigth);
	}

	std::ostream& operator<<(std::ostream& out, Fraction rational)
	{
		return out << rational.Numerator() << '/' << rational.Denominator();
	}

	std::istream& operator>>(std::istream& in, Fraction& fraction)
	{
		int numerator;
		int denominator;
		char slash;
		if ((in >> numerator) && (in >> slash) && (slash == '/') && (in >> denominator))
		{
			if (denominator == 0)
			{
				std::cout << "You entered denomenator = 0" << std::endl;
			}
			else
			{
				fraction = Fraction{ numerator, denominator };
			}
		}
		return in;
	}

	void TestFraction()
	{
		Fraction left(1, 2);
		Fraction rigth(2, 4);
		assert(left == rigth);
		rigth += left;
		assert(rigth == Fraction(1, 1));
		assert(rigth.GetValueFraction() == 1);
		assert(left.GetValueFraction() == 0.5);
		assert(left != rigth);
		assert(left < rigth);
		assert(rigth > left);

		Fraction fraction;
		std::stringstream in_str("1 / 2");		
		in_str >> fraction;
		std::stringstream out_str;
		out_str << fraction;
		assert(out_str.str() == "1/2");
		assert(fraction.GetValueFraction() == 0.5);
	}

}//end namespace fraction

void Dz3()
{
	figures::TestArea();
	cars::TestCars();
	fraction::TestFraction();
}
