#include "commands.hpp"
#include "utils.hpp"
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iterator>
#include <cctype>
#include <limits>

static velizade::Polygon readPolygonFromStream(std::istream& in)
{
  velizade::Polygon p;
  size_t n;
  if (!(in >> n))
  {
    in.setstate(std::ios::failbit);
    return p;
  }
  p.points.reserve(n);
  std::copy_n(std::istream_iterator<velizade::Point>(in), n, std::back_inserter(p.points));
  if (in.fail() || p.points.size() != n || n < 3)
  {
    in.setstate(std::ios::failbit);
    p.points.clear();
    return p;
  }
  in >> std::ws;
  int next = in.peek();
  if (next != EOF && next != '\n')
  {
    in.setstate(std::ios::failbit);
    p.points.clear();
  }
  return p;
}

static void printDouble(double val, std::ostream& out)
{
  velizade::StreamGuard guard(out);
  out << std::fixed << std::setprecision(1) << val;
}

void velizade::area(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
  std::string arg;
  if (!(in >> arg))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  bool isNum = !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);
  if (isNum)
  {
    size_t count = static_cast<size_t>(std::stoul(arg));
    if (count < 3)
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    HasVertexCount pred{count};
    SumAreaIf<HasVertexCount> summer{pred};
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, summer);
    printDouble(sum, out);
    out << '\n';
  }
  else if (arg == "EVEN")
  {
    IsEvenVertex pred;
    SumAreaIf<IsEvenVertex> summer{pred};
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, summer);
    printDouble(sum, out);
    out << '\n';
  }
  else if (arg == "ODD")
  {
    IsOddVertex pred;
    SumAreaIf<IsOddVertex> summer{pred};
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, summer);
    printDouble(sum, out);
    out << '\n';
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    AlwaysTrue pred;
    SumAreaIf<AlwaysTrue> summer{pred};
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0, summer);
    printDouble(sum / polygons.size(), out);
    out << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void velizade::max(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
  std::string arg;
  if (!(in >> arg))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (polygons.empty())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (arg == "AREA")
  {
    CompareAreaLess comp;
    auto it = std::max_element(polygons.begin(), polygons.end(), comp);
    printDouble(getArea(*it), out);
    out << '\n';
  }
  else if (arg == "VERTEXES")
  {
    CompareVertexLess comp;
    auto it = std::max_element(polygons.begin(), polygons.end(), comp);
    out << it->points.size() << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void velizade::min(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
  std::string arg;
  if (!(in >> arg))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (polygons.empty())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (arg == "AREA")
  {
    CompareAreaLess comp;
    auto it = std::min_element(polygons.begin(), polygons.end(), comp);
    printDouble(getArea(*it), out);
    out << '\n';
  }
  else if (arg == "VERTEXES")
  {
    CompareVertexLess comp;
    auto it = std::min_element(polygons.begin(), polygons.end(), comp);
    out << it->points.size() << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void velizade::count(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
  std::string arg;
  if (!(in >> arg))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  bool isNum = !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);
  if (isNum)
  {
    size_t count = static_cast<size_t>(std::stoul(arg));
    if (count < 3)
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
    HasVertexCount pred{count};
    size_t n = std::count_if(polygons.begin(), polygons.end(), pred);
    out << n << '\n';
  }
  else if (arg == "EVEN")
  {
    IsEvenVertex pred;
    size_t n = std::count_if(polygons.begin(), polygons.end(), pred);
    out << n << '\n';
  }
  else if (arg == "ODD")
  {
    IsOddVertex pred;
    size_t n = std::count_if(polygons.begin(), polygons.end(), pred);
    out << n << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void velizade::rects(std::istream&, std::ostream& out, const std::vector<Polygon>& polygons)
{
  IsRectangleShape pred;
  size_t n = std::count_if(polygons.begin(), polygons.end(), pred);
  out << n << '\n';
}

void velizade::same(std::istream& in, std::ostream& out, const std::vector<Polygon>& polygons)
{
  Polygon target = readPolygonFromStream(in);
  if (in.fail() || target.points.empty())
  {
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    out << "<INVALID COMMAND>\n";
    return;
  }
  IsSameTranslationOf pred{target};
  size_t n = std::count_if(polygons.begin(), polygons.end(), pred);
  out << n << '\n';
}
