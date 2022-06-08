#pragma once
#include <iostream>

using namespace std::literals;

namespace dz8
{
	namespace div
	{
		class DivisionByZero
		{
		public:
			DivisionByZero(const std::string& what) : what_(what)
			{}

			void What() const
			{
				std::cerr << what_ << std::endl;
			}

		private:
			std::string what_;

		};

		int Div()
		{
			int x = 0, y = 0;
			std::cout << "Pleas enter dividend and divisor"s << std::endl;
			std::cin >> x >> y;
			if (y == 0)
			{
				throw DivisionByZero("Divisor equal zero"s);
			}
			return x / y;
		}

		void TestDiv()
		{
			std::cout << "Start test Div"s << std::endl;
			try
			{
				Div();
			}
			catch (DivisionByZero& e)
			{
				e.What();
			}
			std::cout << "Test Div is Ok"s << std::endl;
		}

	} // namespace div

	namespace bar_ex
	{
		class Ex
		{
		public:

			Ex() = default;

			Ex(double x) : x_(x)
			{}

			void What()
			{
				std::cout << "You enter number: "s << x_ << std::endl;
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
			std::cout << "Start test BarEx"s << std::endl;
			Bar bar;
			while (true)
			{
				int x = 0;
				std::cout << "Pleas enter number. If you want to stop enter \"0\""s << std::endl;
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
	} // namespace bar_ex

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
				FillSpace();
			}

			void FillSpace()
			{
				for (size_t i = 0; i < BASE; ++i)
				{
					for (size_t j = 0; j < BASE; ++j)
					{
						space_[i][j] = Space::ZIRO;
					}
				}
				space_[0][0] = Space::BUSY;
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
					throw OffTheField("You can set not correct coordinat. Your coordinet now is: "s, p_);
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
					throw OffTheField("You want to shift to right. Your move isn't correct. Your coordinet now is: "s, p_);
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
					throw OffTheField("You want to shift to left. Your move isn't correct. Your coordinet now is: "s, p_);
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
					throw OffTheField("You want to shift to up. Your move isn't correct. Your coordinet now is: "s, p_);
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
					throw OffTheField("You want to shift to down. Your move isn't correct. Your coordinet now is: "s, p_);
				}
			}

			void MoveRobot()
			{
				bool is_true = true;
				while (is_true)
				{
					std::cout << "Where do you want to shift your robot? Pleas enter command. \"r\" : right,"s
						<< " \"l\" : left, \"u\" : up, \"d\" : down, or \"b\" for stop"s << std::endl;
					try
					{
						switch (char command(std::getchar()); command)

						{
						case 'l':
							ShiftLeft();
							PrintSpace();
							command = std::getchar();
							break;
						case 'r':
							ShiftRight();
							PrintSpace();
							command = std::getchar();
							break;
						case 'u':
							ShiftUp();
							PrintSpace();
							command = std::getchar();
							break;
						case 'd':
							ShiftDown();
							PrintSpace();
							command = std::getchar();
							break;
						case 'b':
							is_true = false;
							break;
						default:
							throw robot::IlLegalCommand("Your command isn't correct"s);
							break;
						}
					}
					catch (robot::IlLegalCommand& e)
					{
						e.What();
						std::cout << "Please try agen"s << std::endl;
					}							
				}
			}

		private:
			Point p_;
			Space space_[BASE][BASE];
		};

		void TestRobot()
		{
			robot::Robot r;
			r.PrintSpace();
			try
			{
				r.MoveRobot();
					
			}
			catch (robot::OffTheField& e)
			{

				e.What();
			}			
		}
	} // namespace robot

	

	void Dz8()
	{
		div::TestDiv();
		bar_ex::TestBarEx();
		robot::TestRobot();
	}
}