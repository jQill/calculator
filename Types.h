#ifndef TYPES
#define TYPES

#include <list>
#include <tuple>
#include <string>

using std::string;
using std::list;

template<typename numType> using Num = std::tuple<int, char, numType>;
template<typename numType> using Expression = list<Num<numType>>;

constexpr int Priority = 0, Operation = 1, Number = 2;

#endif // !TYPES