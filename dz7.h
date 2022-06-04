#pragma once
#include <iostream>
#include <iomanip>
#include <memory>
#include<cassert>

class Date
{
public:
	Date() = default;
	Date(size_t day, size_t month, size_t year)
	{
		const size_t MAX_DAY = 31;
		const size_t MAX_MONTH = 12;
		const size_t MIN = 0;
		const size_t MIN_YEAR = 1900;
		const size_t MAX_YEAR = 2200;
		if (day == MIN || day > MAX_DAY || month == MIN || month > MAX_MONTH || year < MIN_YEAR || year > MAX_YEAR)
		{
			std::cout << "Date: \"" << std::setfill('0') << std::setw(2) << day << "."
				      << std::setfill('0') << std::setw(2) << month << "." 
				      << year << "\" is incorrect" << std::endl;
			throw std::logic_error("Date is incorrect");
		}
		else if (month == 2 && day > 28 && year % 4 != 0)
		{
			std::cout << "Date: \"" << std::setfill('0') << std::setw(2) << day << "."
				<< std::setfill('0') << std::setw(2) << month << "."
				<< year << "\" is incorrect" << std::endl;
			throw std::logic_error("Date is incorrect");
		}
		else if (month == 2 && day > 29 && year % 4 == 0)
		{
			std::cout << "Date: \"" << std::setfill('0') << std::setw(2) << day << "."
				<< std::setfill('0') << std::setw(2) << month << "."
				<< year << "\" is incorrect" << std::endl;
			throw std::logic_error("Date is incorrect");
		}
		day_ = day;
		month_ = month;
		year_ = year;
	}

	Date(const Date& d) : day_(d.GetDay()), month_(d.GetMonth()), year_(d.GetYear())
	{}

	Date& operator=(const Date& d) noexcept
	{
		if (*this != d)
		{
			day_ = d.GetDay();
			month_ = d.GetMonth();
			year_ = d.GetYear();
		}
		return *this;
	}

	size_t GetDay() const
	{
		return day_;
	}

	size_t GetMonth() const
	{
		return month_;
	}

	size_t GetYear() const
	{
		return year_;
	}

	Date GetDate() const noexcept
	{
		return { day_, month_, year_ };
	}

	bool operator<(const Date& other) const noexcept
	{
		if (year_ == other.year_ && month_ == other.month_)
		{
			return day_ < other.day_;
		}
		else if (year_ == other.year_)
		{
			return month_ < other.month_;
		}
		else
		{
			return year_ < other.year_;
		}
	}

	bool operator>(const Date& other) const noexcept
	{
		return !(*this < other);
	}

	bool operator==(const Date& other) const noexcept
	{
		return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
	}

	bool operator!=(const Date& other) const noexcept
	{
		return !(*this == other);
	}

	Date& Swap(Date& other) noexcept
	{
		if (*this != other)
		{
			Date temp = other;
			other = *this;
			*this = temp;
		}
		return *this;
	}

private:
	size_t day_ = 1;
	size_t month_ = 1;
	size_t year_ = 1900;
};

std::ostream& operator<<(std::ostream& out, const Date& d)
{
	out << "\"" << std::setfill('0') << std::setw(2) << d.GetDay()
		<< "." << std::setfill('0') << std::setw(2) << d.GetMonth() 
		<< "." << d.GetYear() << "\"";
	
	return out;
}

void PrintDatePtr(std::unique_ptr<Date>& d)
{
	if (d)
	{
		std::cout << *d << std::endl;
	}
	else
	{
		std::cout << "Ptr is nullptr" << std::endl;
	}
}

void TestDate1()
{
	std::unique_ptr<Date> today;	
	try 
	{
		today = std::make_unique<Date>(03, 24, 2022);
		
	}
	catch(...)
	{
		assert(today == nullptr);
	}
	try
	{
		today = std::make_unique<Date>(30, 02, 2022);
		
	}
	catch (...)
	{
		assert(today == nullptr);
	}
	try
	{
		 today = std::make_unique<Date>(29, 02, 2021);		
	}
	catch (...)
	{
		assert(today == nullptr);
	}
	today = std::make_unique<Date>(29, 02, 2020);
	PrintDatePtr(today);
	today = std::make_unique<Date>(03, 06, 2022);
	PrintDatePtr(today);
	std::unique_ptr<Date> data = std::move(today);
	PrintDatePtr(today);
	PrintDatePtr(data);
	std::cout << std::endl;
}

Date ComparisonDates(std::unique_ptr<Date>& d1, std::unique_ptr<Date>& d2)
{	
	return *d1 < *d2 ? *d2 : *d1;
}

void SwapPtrDate(std::unique_ptr<Date>& date1, std::unique_ptr<Date>& date2)
{
	date1->Swap(*date2);
}

void TestDate2()
{
	std::unique_ptr<Date> date1 = std::make_unique<Date>(03, 06, 2023);	
	std::unique_ptr<Date> date2 = std::make_unique<Date>(03, 07, 2022);
	
	assert(date1->GetDate() == Date(03, 06, 2023));	
	assert(date2->GetDate() == Date(03, 07, 2022));

	std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << "Date from ptr date1: " << *date1 << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << "Date from ptr date2: " << *date2 << std::endl;

	SwapPtrDate(date1, date2);

	assert(date1->GetDate() == Date(03, 07, 2022));
	assert(date2->GetDate() == Date(03, 06, 2023));
	std::cout << "\nDates from ptr date1 and from ptr date2 after substitution" << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date from ptr date1: " << *date1 << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date from ptr date2: " << *date2 << std::endl;
	std::cout << std::endl;
	Date d = ComparisonDates(date1, date2);
	assert(d.GetDate() == Date(03, 06, 2023));
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date d: " << d << std::endl;

	Date d1(d);
	assert(d1.GetDate() == Date(03, 06, 2023));
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date d1: " << d1 << std::endl;
	
	d1.Swap(*date1);
	assert(d1.GetDate() == Date(03, 07, 2022));
	assert(date1->GetDate() == Date(03, 06, 2023));
	std::cout << "\nDates d1 and from ptr date1 after substitution" << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date d1: " << d1 << std::endl;
	std::cout << std::setiosflags(std::ios::left) << std::setw(21) << std::setfill(' ') << "Date from ptr date1: " << *date2 << std::endl;
}
void Dz7()
{
	TestDate1();
	TestDate2();
}