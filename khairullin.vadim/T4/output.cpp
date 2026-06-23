#include "output.hpp"

void khairullin::output(std::vector< std::weak_ptr< khairullin::Shape > > & shapes)
{
  double sum_area = 0;
  const size_t N = shapes.size();
  for (size_t i = 0; i < N; i++)
  {
    auto temp = shapes[i].lock();
    if (!temp)
    {
      throw std::logic_error("The shape is empty");
    }
    sum_area += temp->getArea();
    std::cout << temp->getArea();
    if (i == N - 1)
    {
      std::cout << "\n";
    }
    else
    {
      std::cout << " ";
    }
  }
  std::cout << sum_area << "\n";
  auto temp_sh = shapes[0].lock();
  if (!temp_sh)
  {
     throw std::logic_error("The shape is empty");
  }
  rectangle_t frame = temp_sh->getFrameRect();
  double x_min = frame.pos.x - frame.width / 2;
  double x_max = frame.pos.x + frame.width / 2;
  double y_min = frame.pos.y - frame.height / 2;
  double y_max = frame.pos.y + frame.height / 2;
  for (size_t i = 1; i < N; i++)
  {
    temp_sh = shapes[i].lock();
    if (!temp_sh)
    {
      throw std::logic_error("The shape is empty");
    }
    rectangle_t temp = temp_sh->getFrameRect();
    std::cout << temp.pos.x << " " << temp.pos.y << " " << temp.width << " " << temp.height << "\n";
    x_min = x_min > temp.pos.x - temp.width / 2 ? temp.pos.x - temp.width / 2 : x_min;
    x_max = x_max < temp.pos.x + temp.width / 2 ? temp.pos.x + temp.width / 2 : x_max;
    y_min = y_min > temp.pos.y - temp.height / 2 ? temp.pos.y - temp.height / 2 : y_min;
    y_max = y_max < temp.pos.y + temp.height / 2 ? temp.pos.y + temp.height / 2 : y_max;
  }
  double res_width = x_max - x_min;
  double res_height = y_max - y_min;
  frame = khairullin::rectangle_t{khairullin::point_t{res_width / 2, res_height / 2}, res_width, res_height};
  std::cout << frame.pos.x << " " << frame.pos.y << " " << frame.width << " " << frame.height << "\n";
}
