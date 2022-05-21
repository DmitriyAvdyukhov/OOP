#pragma once
#include <cstdint>
#include <iostream>
#include <cmath>
#include <cassert>
#include <sstream>
#include <stdexcept>

using namespace std::literals;

class Power
{
public:

	Power() = default;

	void SetNumbers(double value1, double value2) noexcept
	{
		value1_ = value1;
		value2_ = value2;
	}

	double Colculate() const noexcept
	{
		return pow(value1_, value2_);
	}

private:
	double value1_ = 1.;
	double value2_ = 1.;
};

void TestPower()
{
	std::cout << "Test Power" << std::endl;
	Power power;
	assert(1 == power.Colculate());
	power.SetNumbers(2, 5);
	assert(32 == power.Colculate());
	power.SetNumbers(2.1, 2);
	assert(4.41 == power.Colculate());
	power.SetNumbers(0, 0);
	assert(1 == power.Colculate());
	std::cout << "Test Power is Ok" << std::endl;
}
void RunPowerClass()
{
	std::cout << "Run class Power\n Please enter two number \"x\" and \"y\"" << std::endl;
	double a = 0., b = 0.;
	std::cin >> a >> b;
	Power power;
	power.SetNumbers(a, b);
	std::cout <<"\"x\" to the power of \"y\" equal: "  << power.Colculate() << std::endl;
}

class Rgba
{
public:
	Rgba() = default;

	Rgba(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255)
		: m_red_(red)
		, m_green_(green)
		, m_blue_(blue)
		, m_alpha_(alpha)
	{}

	void Print(std::ostream& out)
	{
		out << "m_red = " << static_cast<unsigned int>(m_red_) 
			<< " m_green = " << static_cast<unsigned int>(m_green_)
			<< " m_blue = " << static_cast<unsigned int>(m_blue_) 
			<< " m_alpha = " << static_cast<unsigned int>(m_alpha_) << std::endl;
	}

private:
	std::uint8_t m_red_ = 0;
	std::uint8_t m_green_ = 0;
	std::uint8_t m_blue_ = 0;
	std::uint8_t m_alpha_ = 255;
};

void TestRgba()
{
	std::cout << "Test RGBA" << std::endl;
	{
		Rgba rgba;
		std::stringstream str;
		rgba.Print(str);
		std::cout << "Print RGBA with the default parameters" << std::endl;
		rgba.Print(std::cout);
		assert("m_red = 0 m_green = 0 m_blue = 0 m_alpha = 255\n" == str.str());
	}	
	{
		Rgba rgba(10, 20, 30);
		std::stringstream str;
		rgba.Print(str);
		assert("m_red = 10 m_green = 20 m_blue = 30 m_alpha = 255\n" == str.str());
	}
	{
		Rgba rgba(20, 50, 45, 56);
		std::stringstream str;
		rgba.Print(str);
		assert("m_red = 20 m_green = 50 m_blue = 45 m_alpha = 56\n" == str.str());
	}
	std::cout << "Test RGBA is Ok" << std::endl;
}

void RunRgbaClass()
{
	std::cout << "Run class RGBA\n Please enter four numbers \"r\", \"g\", \"b\" and \"a\"" << std::endl;
	unsigned int r = 0, g = 0, b = 0, a = 0;
	std::cin >> r >> g >> b >> a;
	Rgba rgba(static_cast<uint8_t>(r), static_cast<uint8_t>(g)
		, static_cast<uint8_t>(b), static_cast<uint8_t>(a));
	std::cout << "Print RGBA with the given parameters" << std::endl;
	rgba.Print(std::cout);
}

template <typename Type>
class Stack
{
public:

    struct Node
    {
        Node() = default;

        Node(const Type& val)
            : value(val)
        {}

        Type value = Type();
        Node* next = nullptr;
        Node* prev = nullptr;
    };

public:

    Stack() = default;

    ~Stack()
    {
        if (size_)
        {
            size_t count = size_;
            for (size_t i = 0; i < count; ++i)
            {
                Pop();
            }
        }
    }

    bool Push(const Type& value)
    {
		if (size_ >= 10)
		{
			return false;
		}
        Node* node = new Node(value);
        if (size_ == 0)
        {
            head_ = std::move(node);
            ++size_;
        }
        else
        {
            Node* temp = std::move(head_);
            head_ = std::move(node);
            head_->next = std::move(temp);
            head_->next->prev = head_;
            ++size_;
        }
		return true;
    }

    Type Pop()
    {
		Type result;
        if (size_ > 0 && size_ != 1)
        {
			result = head_->value;
            Node* temp = std::move(head_);
            head_ = nullptr;
            head_ = std::move(temp->next);
            head_->prev = nullptr;
            --size_;
            delete temp;
        }
        else if(size_ == 1)
        {
			result = head_->value;
            delete head_;
            head_ = nullptr;
            --size_;
        }
		else
		{
			std::cout << "Stak is clear" << std::endl;
			throw std::logic_error("Exception is expected"s);
		}
		return result;
    }

	void Reset()
	{
		if (size_)
		{
			size_t count = size_;
			for (size_t i = 0; i < count; ++i)
			{
				Pop();
			}
			head_ = nullptr;
			size_ = 0;
		}		
	}

	void Print(std::ostream& out = std::cout) const noexcept
	{
		if (size_)
		{
			out << "( ";
			Node* temp = head_;
			for (size_t i = 0; i < size_; ++i)
			{
				out << temp->value << " ";
				temp = temp->next;
			}
			out << " )" << std::endl;
		}
		else
		{
			out << "( )" << std::endl;
		}
	}

	size_t Size() const noexcept
	{
		return size_;
	}

private:
    Node* head_ = nullptr;
    size_t size_ = 0;
};


namespace simple_stack
{
	class Stack
	{
	public:
		Stack()
		{
			for (int i = 0; i < size; ++i)
			{
				stack_[i] = 0;
			}
		}

		void Reset()
		{
			for (int i = 0; i < size_; ++i)
			{
				stack_[i] = 0;
			}
			size_ = 0;
		}

		bool Push(int value)
		{
			if (size_ == 10)
			{
				return false;
			}
			stack_[size_++] = value;
			
			return true;
		}

		int Pop()
		{
			int result = 0;
			if (size_ == 0)
			{
				std::cout << "Stack is clear" << std::endl;
			}
			else
			{
				result = stack_[--size_];
				stack_[size_] = 0;				
			}
			return result;
		}

		void Print()
		{
			std::cout << "( ";
			for (int i = 0; i < size_; ++i)
			{
				std::cout << stack_[i] << " ";
			}
			std::cout << ")" << std::endl;
		}
	private:
		static const int size = 10;
		int stack_[size];
		size_t size_ = 0;
	};
}
void TestStack()
{
	std::cout << "Test Stack" << std::endl;
	std::cout << "\t Stack from list" << std::endl;
	Stack<int> stack;
	try
	{
		stack.Reset();
		stack.Print();
		stack.Push(3);
		stack.Push(7);
		stack.Push(5);
		assert(stack.Size() == 3);
		stack.Print();
		stack.Pop();
		stack.Print();
		assert(stack.Size() == 2);
		stack.Pop();
		stack.Pop();
		stack.Print();
		assert(stack.Size() == 0);
		stack.Pop(); //size == 0
	}
	catch (std::logic_error)
	{
		assert(stack.Size() == 0);
	}
	std::cout << "\t Stack from array" << std::endl;
	{
		simple_stack::Stack stack;
		stack.Reset();
		stack.Print();

		stack.Push(3);
		stack.Push(7);
		stack.Push(5);
		stack.Print();

		stack.Pop();
		stack.Print();

		stack.Pop();
		stack.Pop();
		stack.Print();
	}
	std::cout << "Test Stack is Ok" << std::endl;
}

void Dz1()
{
	TestPower();
	RunPowerClass();
	TestRgba();
	RunRgbaClass();
	TestStack();
}