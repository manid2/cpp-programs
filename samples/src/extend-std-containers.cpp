#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

namespace RCN
{

typedef std::map<std::string, std::string> MapItem;
typedef std::vector<MapItem> VectorItem;

typedef VectorItem RcnLinks;
typedef VectorItem RcnUserData;

template <class Vector>
std::string toJsonString(const Vector &v)
{
  std::stringstream ss;
  ss << "[";
  for (const auto &e : v)
  {
    ss << e << ", ";
  }
  ss << "]";
  return ss.str();
}

std::stringstream &operator<<(std::stringstream &ss, const MapItem &mi)
{
  ss << "{";
  for (const auto &e : mi)
  {
    ss << "\"" << e.first << "\": \"" << e.second << "\""
       << ", ";
  }
  ss << "}";
  return ss;
}

} // namespace RCN

int main(int argc, char **argv)
{
  cout << "hw\n";
  RCN::MapItem mi1; // = {"key1", "val1"};
  mi1["mi1_key1"] = "mi1_val1";
  mi1["mi1_key2"] = "mi1_val2";
  
  RCN::MapItem mi2;// = {"key2", "val2"};
  mi2["mi2_key1"] = "mi2_val1";
  mi2["mi2_key2"] = "mi2_val2";
  
  RCN::RcnLinks links = {mi1, mi2};
  cout << "RCN Links=" << RCN::toJsonString<RCN::RcnLinks>(links);
  cout << endl;
  return 0;
}