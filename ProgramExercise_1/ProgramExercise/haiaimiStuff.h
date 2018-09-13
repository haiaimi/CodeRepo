#pragma once

#include <vector>

namespace WidgetStuff
{
	template<typename T>
	class WidgetImp
	{
	public:
	private:
		int a, b, c;
		std::vector<double> v;
	};

	template<typename T>
	class Widget
	{
	public:
		explicit Widget(int a)
		{}
		Widget & operator=(const Widget& rhs)
		{
			*pImpl = *(rhs.pImpl);
		}

		template<typename T>
		void swap(Widget<T>& other)
		{
			using std::swap;         //曝光标准库里的 swap函数，十分有必要
			swap(pImpl, other.pImpl);  //这里调用的是标准库 swap
		}

	private:
		WidgetImp<T> * pImpl;
	};

	template<typename T>
	void swap(Widget<T>& a, Widget<T>& b)
	{
		a.swap(b);
	}

	void doSomeWork(const Widget<int>& w)
	{

	}
};

void fun_1()
{
	using namespace WidgetStuff;
	Widget<int> A(1);
	Widget<int> B(2);

	Widget<int> a = static_cast<Widget<int>>(10);
	swap(A, B);
}

//下面的方法适用于Widget不是模板类
//namespace std 
//{
//	template<>
//	void swap<Widget>(Widget& a, Widget& b)
//	{
//		a.swap(b);
//
//	}
//}