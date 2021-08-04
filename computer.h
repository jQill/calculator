#ifndef COMPUTER
#define COMPUTER

#include <algorithm>
#include <cmath>
#include "Types.h"
#include "parser.h"
#include "Exception.h"

using std::get;
using std::to_string;

long int fact(long int x)noexcept;

template<typename numType>bool prtyComp(const Num<numType>& first, const Num<numType>& second);

string to_string(const rational& num);
string erase_extra_zeroes(string str);

void make_calculations(rational& numL, const rational& numR, char& operationL, const char operationR, int& prtyL, const int prtyR);
void make_calculations(double& numL, const double& numR,char& operationL, const char operationR,int& prtyL, const int prtyR);

template<typename numType,typename it>it calculate_1_oper(it&& R);
template<typename numType>numType calculate_res(Expression<numType>&& exp);
template<typename numType>std::pair<int, string> call_calculator(const string& str)noexcept;

#endif // !COMPUTER
