#include "functions.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

namespace aushev
{
  void displayFigure(const std::weak_ptr<Shape>& fig, const std::string& nm, size_t id)
  {
    auto sh = fig.lock();
    if (!sh)
    {
      throw std::runtime_error("Expired weak pointer");
    }

    rectangle_t fr = sh->getFrameRect();

    std::cout << id << ". " << nm << "\n";
    std::cout << "area = " << sh->getArea() << "\n";
    std::cout << "frame: (" << fr.pos_.x_ << ";" << fr.pos_.y_ << "), width = "
              << fr.width_ << ", height = " << fr.height_ << "\n";
  }

  void displayAll(const std::vector<std::weak_ptr<Shape>>& figs, const std::vector<std::string>& nms)
  {
    double sum = 0.0;
    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < figs.size(); ++i)
    {
      auto sh = figs[i].lock();
      if (sh)
      {
        displayFigure(figs[i], nms[i], i + 1);
        sum += sh->getArea();
      }
    }

    std::cout << "\nTotal area = " << sum << "\n";
  }

  rectangle_t getTotalFrame(const std::vector<std::weak_ptr<Shape>>& figs)
  {
    if (figs.empty())
    {
      return rectangle_t(0.0, 0.0, point_t(0.0, 0.0));
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto& wptr : figs)
    {
      auto sh = wptr.lock();
      if (!sh) continue;

      rectangle_t fr = sh->getFrameRect();
      double hw = fr.width_ / 2.0;
      double hh = fr.height_ / 2.0;

      double l = fr.pos_.x_ - hw;
      double r = fr.pos_.x_ + hw;
      double b = fr.pos_.y_ - hh;
      double t = fr.pos_.y_ + hh;

      if (l < minX) minX = l;
      if (r > maxX) maxX = r;
      if (b < minY) minY = b;
      if (t > maxY) maxY = t;
    }

    double w = maxX - minX;
    double h = maxY - minY;
    point_t c((minX + maxX) / 2.0, (minY + maxY) / 2.0);

    return rectangle_t(w, h, c);
  }

  void displayTotalFrame(const rectangle_t& fr)
  {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total frame: (" << fr.pos_.x_ << ";" << fr.pos_.y_ << ") ";
    std::cout << "width = " << fr.width_ << ", height = " << fr.height_ << "\n";
  }

  void scaleFigures(std::vector<std::weak_ptr<Shape>>& figs, const point_t& ctr, double k)
  {
    for (auto& wptr : figs)
    {
      auto sh = wptr.lock();
      if (!sh) continue;

      rectangle_t fr = sh->getFrameRect();
      point_t oc = fr.pos_;

      point_t nc(
        ctr.x_ + (oc.x_ - ctr.x_) * k,
        ctr.y_ + (oc.y_ - ctr.y_) * k
      );

      sh->scale(k);
      sh->move(nc);
    }
  }
}
