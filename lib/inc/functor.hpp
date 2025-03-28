#pragma once

#include <functional>

namespace functor
{
class square_functor {
	public:
		double operator() (double x){
			return x*x;
		};
        static std::function<double(double)> square;
};
}
