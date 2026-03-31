#ifndef CIRCLE_HPP

#define CIRCLE_HPP
#include "shape.hpp"
#include <stdexcept>

namespace zinoviev
{
	class Circle : public Shape
	{
		point_t center_;
		double radius_;

	public:

		Circle() :
			radius_(1.0)
		{
		}

		Circle(point_t pt, double r) :
			center_(pt),
			radius_(r)
		{
			if (radius_ <= 0.0)
				throw std::invalid_argument("Radius must be positive");
		}


		double getArea() const override;
		rectangle_t getFrameRect() const override;
		void move(const point_t& newPos) override;
		void move(double dx, double dy) override;
		void scale(double k) override;
	};
}
#endif
