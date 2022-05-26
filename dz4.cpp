#include "dz4.h"

namespace array_int
{
	ArrayInt::ArrayInt() : m_length_(0), m_data_(nullptr)
	{}

	ArrayInt::ArrayInt(int length) : m_length_(length)
	{
		assert(length >= 0);
		if (length > 0)
		{
			m_data_ = new int[length];
		}
		else
		{
			m_data_ = nullptr;
		}
	}

	ArrayInt::~ArrayInt()
	{
		delete[] m_data_;
	}

	void ArrayInt::Erase() noexcept
	{
		delete[] m_data_;
		m_data_ = nullptr;
		m_length_ = 0;
	}

	int ArrayInt::GetLength() const noexcept
	{
		return m_length_;
	}

	int& ArrayInt::operator[](int index) const
	{
		assert(index >= 0 && index < m_length_);
		return m_data_[index];
	}

	void ArrayInt::Resize(int newLength) noexcept
	{
		if (newLength == m_length_)
		{
			return;
		}

		if (newLength <= 0)
		{
			Erase();
			return;
		}
		// Теперь знаем, что newLength >0
		// Выделяем новый массив
		int* data = new int[newLength];
		// Затем нужно разобраться с количеством копируемых элементов в новый	массив		
		// Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
		if (m_length_ > 0)
		{
			int elementsToCopy = (newLength > m_length_) ? m_length_ : newLength;
			// Поочередно копируем элементы
			for (int index = 0; index < elementsToCopy; ++index)
			{
				data[index] = m_data_[index];
			}
		}
		// Удаляем старый массив, так как он нам уже не нужен
		delete[] m_data_;
		// И используем вместо старого массива новый! Обратите внимание,m_data указывает
		// на тот же адрес, на который указывает наш новый динамически	выделенный массив.Поскольку
		// данные были динамически выделенные — они не будут уничтожены, когда	выйдут из области видимости
		m_data_ = data;
		m_length_ = newLength;
	}

	void ArrayInt::InsertBefore(int value, int index)
	{
		// Проверка корректности передаваемого индекса
		assert(index >= 0 && index <= m_length_);
		// Создаем новый массив на один элемент больше старого массива
		int* data = new int[m_length_ + 1];
		// Копируем все элементы до index-а
		for (int before = 0; before < index; ++before)
		{
			data[before] = m_data_[before];
		}
		// Вставляем новый элемент в новый массив
		data[index] = value;
		// Копируем все значения после вставляемого элемента
		for (int after = index; after < m_length_; ++after)
		{
			data[after + 1] = m_data_[after];
		}
		// Удаляем старый массив и используем вместо него новый
		delete[] m_data_;
		m_data_ = data;
		++m_length_;
	}

	void ArrayInt::Print(std::ostream& out) const
	{
		if (!m_length_)
		{
			out << "ArrayInt is clear";
		}
		for (int i = 0; i < m_length_; ++i)
		{
			out << m_data_[i] << " ";
		}
		out << std::endl;
	}

	void ArrayInt::PopBack()
	{
		if (!m_length_)
		{
			throw std::logic_error("ArrayInt is clear");
		}
		--m_length_;
	}

	void ArrayInt::PopFront()
	{
		if (!m_length_)
		{
			throw std::logic_error("ArrayInt is clear");
		}
		int* temp = new int[m_length_];
		int count_temp = 0;
		for (int i = 1; i < m_length_; ++i, ++count_temp)
		{
			temp[count_temp] = m_data_[i];
		}
		delete[] m_data_;
		m_data_ = temp;
		temp = nullptr;
		--m_length_;
	}

	void ArrayInt::Fill(int x) noexcept
	{
		for (int i = 0; i < m_length_; ++i)
		{
			m_data_[i] = x;
		}
	}

	void ArrayInt::FillRand() noexcept
	{
		srand(time(NULL));
		for (int i = 0; i < m_length_; ++i)
		{
			m_data_[i] = rand() % m_length_;
		}
	}

	void ArrayInt::Sort() noexcept
	{
		if (m_length_)
		{
			QuickSort(m_data_, 0, m_length_ - 1);
		}
	}

	inline void ArrayInt::Swap(int* a, int* b) noexcept
	{
		int t;
		t = *a;
		*a = *b;
		*b = t;
	}

	inline void ArrayInt::QuickSort(int* ar, int first, int last) noexcept
	{
		int i = first;
		int j = last;

		int x = ar[(first + last) / 2];
		if (ar[first] >= x && ar[first] <= ar[last])
		{
			x = ar[first];
		}
		else if (ar[last] >= x && ar[first] >= ar[last])
		{
			x = ar[last];
		}
		do {

			while (ar[i] < x) i++;
			while (ar[j] > x) j--;

			if (i <= j)
			{
				Swap(&ar[i], &ar[j]);
				i++;
				j--;
			}
		} while (i <= j);

		if (i < last)
		{
			QuickSort(ar, i, last);
		}
		if (first < j)
		{
			QuickSort(ar, first, j);
		}
	}

	void TestArrayInt()
	{
		ArrayInt arr(10);
		arr.Fill(5);
		std::stringstream str;
		arr.Print(str);
		assert(arr.GetLength() == 10);
		assert(str.str() == "5 5 5 5 5 5 5 5 5 5 \n");

		arr[0] = 2;
		std::stringstream str1;
		arr.Print(str1);
		assert(str1.str() == "2 5 5 5 5 5 5 5 5 5 \n");

		arr.PopFront();
		std::stringstream str2;
		arr.Print(str2);
		assert(str2.str() == "5 5 5 5 5 5 5 5 5 \n");
		assert(arr.GetLength() == 9);

		arr[arr.GetLength() - 1] = 9;
		std::stringstream str3;
		arr.Print(str3);
		assert(str3.str() == "5 5 5 5 5 5 5 5 9 \n");

		arr.PopBack();
		std::stringstream str4;
		arr.Print(str4);
		assert(str4.str() == "5 5 5 5 5 5 5 5 \n");
		assert(arr.GetLength() == 8);

		arr.FillRand();
		arr.Print(std::cout);
		arr.Sort();
		arr.Print(std::cout);
		arr.Erase();
		assert(arr.GetLength() == 0);
		try
		{
			arr.PopBack();
		}
		catch (std::logic_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}	
}

namespace check_vector
{
	size_t CountIndificaiValues(const std::vector<int>& v)
	{
		std::vector<int>temp{ v.begin(), v.end() };
		std::sort(temp.begin(), temp.end());
		size_t count = 0;
		if (temp.size())
		{
			int current = temp[0];
			bool is_first = true;
			for (auto it = temp.begin(); it != temp.end(); ++it)
			{
				if (is_first)
				{
					is_first = false;
				}
				else
				{
					if (current == *it)
					{
						++count;
						if (it - 1 != temp.begin())
						{

							if (*(it - 2) == current && it - 2 != temp.end())
							{
								--count;
							}
						}
					}
					current = *it;
				}
			}
		}
		return count;
	}
	void CheckVector()
	{
		{
			std::stringstream str;
			std::vector<int> v{ 2, 2, 2, 2 };
			str << CountIndificaiValues(v);
			assert(str.str() == "1");
		}
		{
			std::stringstream str;
			std::vector<int> v{ 2, 7, 8, 9, 10, 8, 2, 2 };
			str << CountIndificaiValues(v);
			assert(str.str() == "2");
		}
		std::stringstream str;
		std::vector<int> v{ 1, 2, 3, 4 };
		str << CountIndificaiValues(v);
		assert(str.str() == "0");
	}
}

void Dz4()
{
	array_int::TestArrayInt();
	check_vector::CheckVector();
}
