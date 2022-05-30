#pragma once
#include <iostream>
#include <numeric>
#include <cassert>

namespace figures 
{
	class Figure
	{
	public:
		virtual ~Figure() = default;
		virtual double Area() const = 0;
		virtual std::string GetNameFigure() const = 0;
	};

	class Parallelogram : public Figure
	{
	public:
		Parallelogram();

		Parallelogram(double side_x, double side_y = 0);

		double Area() const override;

		double GetSideX() const;

		std::string GetNameFigure() const override = 0;

	private:
		double side_x_ = 0;
		double side_y_ = 0;
	};

	class Rectangle : public Parallelogram
	{
	public:
		Rectangle();

		Rectangle(double side_x, double side_y);

		std::string GetNameFigure() const override;		
	};

	class Square : public Parallelogram
	{
	public:
		Square();

		explicit Square(double side);

		double Area() const override;

		std::string GetNameFigure() const override;		
	};

	class Rhombus : public Parallelogram
	{
	public:
		Rhombus();

		Rhombus(double side, double height);

		std::string GetNameFigure() const override;		
	};

	class Circle :public Figure
	{
	public:
		Circle();

		Circle(double radius);

		double Area() const override;

		std::string GetNameFigure() const override;
		
	private:
		double radius_ = 0;		
	};

	void TestArea();
}

namespace cars
{
	class Car 
	{
	public:
		Car();		

		Car(const std::string& company, const std::string& model);
				
		~Car();
		
	private:
		std::string company_;
		std::string model_;
	};

	class PassengerCar : virtual public Car
	{
	public:
		PassengerCar();		

		PassengerCar(const std::string& company, const std::string& model);			

		~PassengerCar();		
	};

	class Bus : virtual public Car
	{
	public:
		Bus();		

		Bus(const std::string& company, const std::string& model);
			
		~Bus();		
	};

	class Minivan : public PassengerCar, public Bus
	{
	public:
		Minivan();		

		Minivan(const std::string& company, const std::string& model);
			
		~Minivan();		
	};

	void TestCars();	
}

namespace fraction
{

    class Fraction
    {
    public:
        Fraction();

        explicit Fraction(int value);            

		Fraction(int numerator, int denominator);            

		int Numerator() const;        

		int Denominator() const;  

		double GetValueFraction() const;

		Fraction& operator+=(Fraction right);        

		Fraction& operator-=(Fraction right);       

		Fraction& operator*=(Fraction right);        

		Fraction& operator/=(Fraction right);  

    private:
		void Normalize();      

        int numerator_ = 0;
        int denominator_ = 1;
    };

	std::ostream& operator<<(std::ostream& output, Fraction rational);    

	std::istream& operator>>(std::istream& input, Fraction& rational);   

	Fraction operator+(Fraction value);

	Fraction operator-(Fraction value);

	Fraction operator-(Fraction left, Fraction right);

	Fraction operator*(Fraction left, Fraction right);

	Fraction operator/(Fraction left, Fraction right);

	bool operator==(Fraction left, Fraction right);

	bool operator!=(Fraction left, Fraction right);

	bool operator>(Fraction left, Fraction rigth);

	bool operator<(Fraction left, Fraction rigth);

	bool operator<=(Fraction left, Fraction rigth);

	bool operator>=(Fraction left, Fraction rigth);

	std::ostream& operator<<(std::ostream& output, Fraction rational);

	std::istream& operator>>(std::istream& input, Fraction& rational);

    void TestFraction();   

}//end namespace fraction

void Dz3();