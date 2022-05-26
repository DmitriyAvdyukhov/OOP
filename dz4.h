#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <sstream>
#include <ctime>
#include <stdexcept>

namespace array_int
{
	
	

	class ArrayInt
	{
	public:
		ArrayInt();

		ArrayInt(int length); 

		~ArrayInt();		

		void Erase() noexcept;

		int GetLength() const noexcept;		

		int& operator[](int index) const;		

		void Resize(int newLength) noexcept;		

		void InsertBefore(int value, int index);		

		void Print(std::ostream& out = std::cout) const;		

		void PopBack();		

		void PopFront();		

		void Fill(int x) noexcept;		

		void FillRand() noexcept;		

		void Sort() noexcept;		

	private:
		int m_length_ = 0;
		int* m_data_ = nullptr;

		inline void Swap(int* a, int* b) noexcept;		

		inline void QuickSort(int* ar, int first, int last) noexcept; //Sort Hoara		
	};

	void TestArrayInt();
}

namespace check_vector
{
	size_t CountIndificaiValues(const std::vector<int>& v);
	
	void CheckVector();	
}

void Dz4();
