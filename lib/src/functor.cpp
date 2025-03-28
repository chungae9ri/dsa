#include <iostream>

#include <functor.hpp>

namespace functor
{
	std::function<double(double)> square_functor::square = [](double x) { 
		return x * x; 
	};
}