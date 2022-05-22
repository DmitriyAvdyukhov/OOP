#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>

namespace person
{	
	enum class Gender
	{
		MALE,
		FEMALE
	};

	std::ostream& operator<<(std::ostream& out, const Gender& gender)
	{
		if (gender == Gender::MALE)
		{
			out << "Male";
		}
		else
		{
			out << "Female";
		}
		return out;
	}	

	class Person
	{
	public:
		Person() = default;

		Person(const std::string& name, size_t age, Gender gender, size_t weight)
			: name_(name), age_(age), gender_(gender), weight_(weight)
		{}

		void SetName(const std::string& name)
		{
			name_ = name;
		}

		void SetAge(size_t age)
		{
			age_ = age;
		}

		void SetWeight(size_t weight) 
		{
			weight_ = weight;
		}

		void SetGender(Gender gender)
		{
			gender_ = gender;
		}

		std::string GetName() const
		{
			return name_;
		}

		size_t GetAge() const
		{
			return age_;
		}

		Gender GetGender() const
		{
			return gender_;
		}

		size_t GetWeight() const
		{
			return weight_;
		}

		std::string GetName() 
		{
			return name_;
		}

		size_t GetAge() 
		{
			return age_;
		}

		Gender GetGender() 
		{
			return gender_;
		}

		size_t GetWeight() 
		{
			return weight_;
		}

	private:
		std::string name_{};
		size_t age_ = 0;
		Gender gender_ = Gender::MALE;
		size_t weight_ = 0;		
	};


	class Student final : public Person
	{
	public:
		Student() = default;		

		Student(const std::string& name, size_t age, Gender gender, size_t weight, size_t year_study)
			: Person(name, age, gender, weight), year_study_(year_study)
		{
			++count_students_;
		}	

		~Student()
		{
			--count_students_;
		}

		Student(Student&& s) noexcept
		{	
			if (*this != s)
			{
				SetAge(s.GetAge());
				s.SetAge(0);
				SetName(s.GetName());
				s.SetName({});
				SetGender(std::move(s.GetGender()));
				SetWeight(s.GetWeight());
				s.SetWeight(0);
				year_study_ = std::exchange(s.year_study_, 0);
			}
		}
		
		Student& operator=(Student&& s) noexcept
		{
			if (*this != s)
			{
				SetAge(s.GetAge());
				s.SetAge(0);
				SetName(s.GetName());
				s.SetName({});
				SetGender(std::move(s.GetGender()));
				SetWeight(s.GetWeight());
				s.SetWeight(0);
				year_study_ = std::exchange(s.year_study_, 0);	
			}
			return *this;
		}

		Student(Student& s) noexcept
		{
			if (*this != s)
			{
				SetAge(s.GetAge());
				SetName(s.GetName());
				SetGender(s.GetGender());
				SetWeight(s.GetWeight());
				year_study_ = s.year_study_;
				++count_students_;
			}						
		}

		Student& operator=(Student& s) noexcept
		{
			if (*this != s)
			{
				SetAge(s.GetAge());
				SetName(s.GetName());
				SetGender(s.GetGender());
				SetWeight(s.GetWeight());
				year_study_ = s.year_study_;
				++count_students_;
			}
			return *this;
		}

		bool operator==(const Student& s) noexcept
		{
			return GetAge() == s.GetAge()
				&& GetName() == s.GetName()
				&& GetGender() == s.GetGender()
				&& GetWeight() == s.GetWeight()
				&& year_study_ == s.year_study_;
		}
		bool operator!=(const Student& s) noexcept
		{
			return !(*this == s);
		}
		void SetYearStudy(size_t year)
		{
			year_study_ = year;
		}

		size_t GetEyarStudy() const
		{
			return year_study_;
		}

		static size_t GetCountStudents() 
		{
			return count_students_;
		}			
		
	private:
		size_t year_study_ = 0;	
		static size_t count_students_;
	};
	size_t Student::count_students_ = 0;
}


std::ostream& operator<<(std::ostream& out, const person::Student& student)
{
	out << "Name: " << std::setiosflags(std::ios::left) << std::setw(15) << student.GetName()
		<< " Age: " << std::setiosflags(std::ios::left) << std::setw(3) << student.GetAge()
		<< " Gender: " << std::setiosflags(std::ios::left) << std::setw(6) << student.GetGender()
		<< " Weight: " << std::setiosflags(std::ios::left) << std::setw(4) << student.GetWeight()
		<< " Year study: " << std::setiosflags(std::ios::left) << std::setw(5) << student.GetEyarStudy();
	return out;
} 

person::Student AddStudent(size_t i)
{
	std::string name, gen;
	size_t age, weight, year_study;
	std::cout << "Please enter last name of " << i + 1 << " student" << std::endl;
	std::cin >> name;
	std::cout << "Please enter age of " << i + 1 << " student" << std::endl;
	std::cin >> age;
	std::cout << "Please enter weight of " << i + 1 << " student" << std::endl;
	std::cin >> weight;
	std::cout << "Please enter gender  if male  press \"M\" or press \"F\" if female of " << i + 1 << " student" << std::endl;
	std::cin >> gen;
	std::cout << "Please enter year study of " << i + 1 << " student" << std::endl;
	std::cin >> year_study;
	person::Gender gender = person::Gender::MALE;
	if (gen == "F")
	{
		gender = person::Gender::FEMALE;
	}
	person::Student student(name, age, gender, weight, year_study);
	return student;
}

std::vector<person::Student> QreatePerson()
{
	std::vector<person::Student> persons;
	size_t count = 0;
	std::cout << "Please inter count students" << std::endl;
	std::cin >> count;
	for (size_t i = 0; i < count; ++i)
	{
		persons.push_back(std::move(AddStudent(i)));
	}
	return persons;
}


void PrintPerson(const std::vector<person::Student>& persons)
{
	for (const auto& person : persons)
	{
		std::cout << person << std::endl;
	}
	std::cout << "\nAmount of the persons: " << person::Student::GetCountStudents();
	std::cout << std::endl;
}

void TestStudents()
{
	person::Student s1("Ivanov", 23, person::Gender::MALE, 67, 2021);
	person::Student s2 = s1;
	assert(s1 == s2);
	assert(person::Student::GetCountStudents() == 2);
	person::Student s3(s2);
	assert(s1 == s3);
	assert(person::Student::GetCountStudents() == 3);
	person::Student s4(person::Student("Petrov", 23, person::Gender::MALE, 67, 2021));
	assert(person::Student::GetCountStudents() == 4);
	assert(s4 != s1);	
	person::Student s5 = std::move(s2);
	assert(s5 == s3);
	assert(person::Student::GetCountStudents() == 4);

	PrintPerson(QreatePerson());	
}

namespace fruit
{
	class Fruit
	{
	public:
		Fruit() = default;

		Fruit(const std::string& name, const std::string& color) : name_(name), color_(color) {}

		std::string GetName() const
		{
			return name_;
		}

		std::string GetColor() const
		{
			return color_;
		}

	private:
		std::string name_;
		std::string color_;
	};

	class Apple : public Fruit
	{
	public:
		explicit Apple(std::string color) : Fruit("apple", color) {}
		Apple(std::string name, std::string color) : Fruit(name, color) {}
	};

	class Banana final : public Fruit
	{
	public:
		Banana() : Fruit("banana", "yellow") {}
	};

	class GrannySmith final : public Apple
	{
	public:
		GrannySmith() : Apple("Granny Smith apple", "green") {}
	};
}

void TestFruits()
{
	fruit::Apple a("red");
	fruit::Banana b;
	fruit::GrannySmith c;
	std::cout << "My " << a.GetName() << " is " << a.GetColor() << ".\n";
	std::cout << "My " << b.GetName() << " is " << b.GetColor() << ".\n";
	std::cout << "My " << c.GetName() << " is " << c.GetColor() << ".\n";
}

void Dz2()
{
	TestStudents();
	TestFruits();
}