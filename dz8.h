#pragma once
#include <iostream>

namespace dz8
{
	class DivisionByZero
	{};

	int Div()
	{
		int x = 0, y = 0;
		std::cin >> x >> y;
		if (y == 0)
		{
			throw DivisionByZero();
		}
		return x / y;
	}

	void TestDiv()
	{
		try
		{
			Div();
		}
		catch (DivisionByZero)
		{
			std::cout << "Catch exception y = 0" << std::endl;
		}
	}

	class Ex
	{
	public:

		Ex() = default;

		Ex(double x) : x_(x)
		{}

		void What()
		{
			std::cout << "You enter number: " << x_ << std::endl;
		}

	private:
		double x_ = 0.;
	};

	class Bar
	{
	public:
		Bar() = default;

		void Set(double a)
		{
			if (y_ + a > 100)
			{
				throw Ex(y_ * a);
			}
			else
			{
				y_ += a;
			}
		}

	private:
		double y_ = 0;
	};

	void TestBarEx()
	{
		Bar bar;
		while (true)
		{
			int x = 0;
			std::cin >> x;
			if (x != 0)
			{
				try
				{
					bar.Set(x);
				}
				catch (Ex& e)
				{
					e.What();
				}
			}
			else
			{
				break;
			}
		}
	}

	namespace robot
	{
		static const size_t BASE = 10;

		enum class Space
		{
			ZIRO,
			BUSY
		};

		std::ostream& operator<<(std::ostream& out, Space s)
		{
			if (s == Space::BUSY)
			{
				out << 'X';
			}
			else
			{
				out << '0';
			}
			return out;
		}

		enum class Direction
		{
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		struct Point
		{
			Point() = default;
			Point(int y, int x) :  y_(y), x_(x)
			{}

			void SetPoint(size_t y, size_t x)
			{
				x_ = x;
				y_ = y;
			}
			
			int x_ = 0;
			int y_ = 0;
		};

		std::ostream& operator<<(std::ostream& out, const Point& p)
		{
			out << "x = " << p.x_ << " y = " << p.y_ << std::endl;
			return out;
		}


		class OffTheField
		{
		public:
			OffTheField(std::string what, Point p) : what_(what), p_(p)
			{}

			void What() const noexcept
			{
				std::cerr << what_ << " " << p_ << std::endl;
			}

		private:
			std::string what_;
			Point p_;
		};

		class IlLegalCommand
		{
		public:
			IlLegalCommand(std::string what) :what_(what)
			{}

			void What() const noexcept
			{
				std::cerr << what_ << std::endl;
			}

		private:
			std::string what_;
		};

		class Robot
		{
		public:
			Robot(): p_()
			{
				for (size_t i = 0; i < BASE; ++i)
				{
					for (size_t j = 0; j < BASE; ++j)
					{
						space_[i][j] = Space::ZIRO;
					}
				}
				space_[0][0]= Space::BUSY;
			}

			void PrintSpace() const
			{
				for (size_t i = 0; i < BASE; ++i)
				{
					for (size_t j = 0; j < BASE; ++j)
					{
						std::cout << space_[i][j] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}

			void SetPoint(size_t y, size_t x)
			{
				if (x <= BASE && y <= BASE && x >= 0 && y >=0)
				{
					space_[p_.y_][p_.x_] = Space::ZIRO;
					p_.SetPoint(y, x);
					space_[p_.y_][p_.x_] = Space::BUSY;
				}
				else
				{
					throw OffTheField("You can set not correct coordinat. Your coordinet now is: ", p_);
				}
			}

			void ShiftRight()
			{
				if (p_.x_ + 1 < BASE - 1)
				{
					SetPoint(p_.y_, p_.x_ + 1);
				}
				else
				{
					throw OffTheField("You want to shift to right. Your shift isn't correct. Your coordinet now is: ", p_);
				}
			}

			void ShiftLeft()
			{
				
				if (p_.x_ - 1 > 0)
				{
					SetPoint(p_.y_, p_.x_ - 1);
				}
				else
				{
					throw OffTheField("You want to shift to left. Your shift isn't correct. Your coordinet now is: ", p_);
				}
			}

			void ShiftUp()
			{
				if ((p_.y_ - 1) > 0)
				{
					SetPoint(p_.y_ - 1, p_.x_);
				}
				else
				{
					throw OffTheField("You want to shift to up. Your shift isn't correct. Your coordinet now is: ", p_);
				}
			}

			void ShiftDown()
			{
				if (p_.y_ + 1 < BASE - 1)
				{
					SetPoint(p_.y_ + 1, p_.x_);
				}
				else
				{
					throw OffTheField("You want to shift to down. Your shift isn't correct. Your coordinet now is: ", p_);
				}
			}

			void ShiftPoint(Direction d)
			{
				if (d == Direction::RIGHT)
				{
					ShiftRight();
				}
				else if (d == Direction::LEFT)
				{
					ShiftLeft();
				}
				else if (d == Direction::UP)
				{
					ShiftUp();
				}
				else if (d == Direction::DOWN)
				{
					ShiftDown();
				}
			}

		private:
			Point p_;
			Space space_[BASE][BASE];
		};
	}

	void TestRobot()
	{
		robot::Robot r;
		r.PrintSpace();
		while (true)
		{
			try
			{
				std::string command;
				std::cout << "Where do you want to shift your robot? Pleas enter command. \"r\" : right,"
					<< " \"l\" : left, \"u\" : up, \"d\" : down, or \"b\" for stop" << std::endl;
				std::cin >> command;
				if (command == "l")
				{
					r.ShiftLeft();
					r.PrintSpace();
				}
				else if (command == "r")
				{
					r.ShiftRight();
					r.PrintSpace();
				}
				else if (command == "u")
				{
					r.ShiftUp();
					r.PrintSpace();
				}
				else if (command == "d")
				{
					r.ShiftDown();
					r.PrintSpace();
				}
				else if (command == "b")
				{
					break;
				}
				else
				{
					throw robot::IlLegalCommand("Your command isn't correct");
				}				
			}
			catch (robot::OffTheField& e)
			{
				e.What();
			}
			catch (robot::IlLegalCommand& e)
			{
				e.What();
				std::cout << "Please try agen" << std::endl;
			}
		}
	}

	void Dz8()
	{
		TestDiv();
		TestBarEx();
		TestRobot();
	}
}