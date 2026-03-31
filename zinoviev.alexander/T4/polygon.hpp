#ifndef POLYGON_HPP

#define POLYGON_HPP
#include "shape.hpp"
#include <vector>
#include <stdexcept>

namespace zinoviev
{
	class Polygon : public Shape
	{
		std::vector< point_t > vertices_;
		point_t centroid_;

	public:

		Polygon(std::vector< point_t > vertices) :
			vertices_(vertices)
		{
			if (!vertices_.size())
				throw std::logic_error("Polygon must have vertices");

			double x_c = 0.0, y_c = 0.0;

			for (size_t i = 0; i < vertices.size(); ++i)
			{
				x_c += vertices[i].x;
				y_c += vertices[i].y;
			}

			centroid_ = point_t{ x_c / vertices.size(), y_c / vertices.size() };
		}

		double getArea() const override;
		rectangle_t getFrameRect() const override;
		void move(const point_t& newPos) override;
		void move(double dx, double dy) override;
		void scale(double k) override;
	};
}
#endif
