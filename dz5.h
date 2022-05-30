#pragma once
#include <iostream>

namespace pair
{
	template<typename T>
	class Pair1
	{
	public:
		Pair1(const T& first, const T& second);

		T GetFirst() const;		

		T GetSecond() const;
		
	private:
		T first_;
		T second_;
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Pair1<T>& p);
	

	template<typename T, typename T1>
	class Pair
	{
	public:
		Pair(const T& first, const T1& second);			

		T GetFirst() const;		

		T1 GetSecond() const;
		
	private:
		T first_;
		T1 second_;
	};

	template<typename T, typename T1>
	std::ostream& operator<<(std::ostream& out, const Pair<T, T1>& p);	


	template<class T>
	class StringValuePair : public Pair<std::string, T>
	{
	public:
		StringValuePair(const std::string& first, const T& second);			
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const StringValuePair<T>& p);	

	void TestPair();

	//--------------resalution------------------

	//-----------------Paur1<T>-------------------	

	template<typename T>
	Pair1<T>::Pair1(const T& first, const T& second)
		: first_(first), second_(second)
	{}
	template<typename T>
	T Pair1<T>::GetFirst() const
	{
		return first_;
	}

	template<typename T>
	T Pair1<T>::GetSecond() const
	{
		return second_;
	}
	
	template<typename T>
	std::ostream& operator<<(std::ostream& out, const Pair1<T>& p)
	{
		out << "Pair: " << p.GetFirst() << " " << p.GetSecond();
		return out;
	}

	//-----------Pair<T, T1>-------------------------

	template<typename T, typename T1>
	inline Pair<T, T1>::Pair(const T& first, const T1& second) 
		: first_(first), second_(second)
	{}

	template<typename T, typename T1>
	inline T pair::Pair<T, T1>::GetFirst() const
	{
		return first_;
	}

	template<typename T, typename T1>
	inline T1 pair::Pair<T, T1>::GetSecond() const
	{
		return second_;
	}

	template<typename T, typename T1>
	std::ostream& operator<<(std::ostream& out, const Pair<T, T1>& p)
	{
		out << "Pair: " << p.GetFirst() << " " << p.GetSecond();
		return out;
	}

	//-------------------StringValuePair--------------------

	template<class T>
	inline StringValuePair<T>::StringValuePair(const std::string& first, const T& second)
		: Pair<std::string, T>(first, second)
	{}

	template<typename T>
	std::ostream& operator<<(std::ostream& out, const StringValuePair<T>& p)
	{
		out << "Pair: " << p.GetFirst() << " " << p.GetSecond();
		return out;
	}	
}

void Dz5();
