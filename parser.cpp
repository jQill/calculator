#include "parser.h"

int calc_priority(const char& oper, int& prty)noexcept
{
    switch (oper)
    {
    case'f':case's':case'a':
    case'i':case'c':case't':
    case'o':case'l':
        return prty + 2; break;
    case'*':case'/':case'^':
        return prty + 1; break;
    case'+':case'-':
        return prty; break;
    default:
        return -1; break;
    }
}

double from_string(const string& s)
{
    double result = 0; char end;
    std::istringstream is(s);
    is >> std::noskipws >> result;
    if ((!is.fail()) && (is >> end).eof())
        return result;
    else throw "Fail";
}

template<typename numType>
void get_num(numType& num, const string& str, int& i)
{
    int j = i;
    if (is_minus(str[i]))++i;
    while (is_float(str[i]) || is_digit(str[i]))++i;
    num = from_string(string(&str[j], &str[i]));
}

void cnt_priority(const string& str, int& i, int& prty)noexcept
{
    while (str[i] == '(') { i++; prty += 3; }
    while (str[i] == ')') { i++; prty -= 3; }
}

template<typename numType>
Num<numType> get_func(const string& str, int& i, int& prty)
{
    cnt_priority(str, i, prty);
    char operation = function_hash(get_func_name(str, i));
    int priority = calc_priority(operation, prty);
    Num<numType> t{ priority, operation, 1 };
    cnt_priority(str, i, prty);
    return t;
}

template<typename numType>
Num<numType> parse(const string& str, int& i, int& prty)
{
    cnt_priority(str, i, prty);
    if ((is_function(str[i])))
        return get_func<numType>(str, i, prty);

    char oper = '\0'; numType num = 0;
    get_num(num, str, i);
    cnt_priority(str, i, prty);
    if (i != str.size())oper = str[i++];
    int priority = calc_priority(oper, prty);
    return Num<numType>{ priority, oper, num };
}

template<typename numType>
Expression<numType> makeExpression(const string& str)
{
    int priority = 1, i = 0, size = str.size();
    Expression<numType> exp;
    while (i != size)
        exp.emplace_back(parse<numType>(str, i, priority));
    return exp;
}


template void get_num(double& num, const string& str, int& i);
template Num<double> get_func(const string& str, int& i, int& prty);
template Num<double> parse(const string& str, int& i, int& prty);
template Expression<double> makeExpression(const string& str);

template void get_num(rational& num, const string& str, int& i);
template Num<rational> get_func(const string& str, int& i, int& prty);
template Num<rational> parse(const string& str, int& i, int& prty);
template Expression<rational> makeExpression(const string& str);
