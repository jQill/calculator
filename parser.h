#ifndef PARSER
#define PARSER

#include <sstream>
#include "Types.h"
#include "Rational.h"
#include "str_validation.h"

int calc_priority(const char& oper, int& prty)noexcept;
double from_string(const string& s);
void cnt_priority(const string& str, int& i, int& prty)noexcept;

template<typename numType> void get_num(numType& num, const string& str, int& i);
template<typename numType> Num<numType> get_func(const string& str, int& i, int& prty);
template<typename numType> Num<numType> parse(const string& str, int& i, int& prty);
template<typename numType> Expression<numType> makeExpression(const string& str);

#endif // !PARSER
