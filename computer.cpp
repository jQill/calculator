#include "computer.h"

long int fact(long int x)noexcept { return x > 1 ? x * fact(x - 1) : 1; }

template<typename numType>
bool prtyComp(const Num<numType>& first, const Num<numType>& second)
{
    return get<Priority>(first) < get<Priority>(second);
}

inline string to_string(const rational& num)
{
    return to_string(num.numerator) +
        (num.denominator == 1 ? "" : '/' + to_string(num.denominator));
}

string erase_extra_zeroes(string str)
{
    int i = str.find_last_not_of('0');
    if (str[i] != '.')++i;
    return str.erase(i, str.size());
}

void make_calculations(
    rational& numL, const rational& numR,
    char& operationL, const char operationR,
    int& prtyL, const int prtyR)
{
    switch (operationL)
    {
    case'+': numL += numR; break;
    case'-': numL -= numR; break;
    case'*': numL *= numR; break;
    case'/':
        if (numR == 0)
            throw myException("division by zero", -2);
        numL /= numR; break;
    case'^':
        if (numR.denominator != 1)
            throw myException("not real power", -2);
        numL.numerator = pow(numL.numerator, numR.numerator);
        numL.denominator = pow(numL.denominator, numR.numerator);
    }
    prtyL = prtyR;
    operationL = operationR;
}

void make_calculations(
    double& numL, const double& numR,
    char& operationL, const char operationR,
    int& prtyL, const int prtyR)
{
    switch (operationL)
    {
    case'+': numL += numR; break;
    case'-': numL -= numR; break;
    case'*': numL *= numR; break;
    case'/':
        if (numR == 0)
            throw myException("division by zero", -2);
        numL /= numR; break;
    case'^': numL = pow(numL, numR); break;
    case'f':
        if (numR < 0)
            throw myException("negative factorial", -2);
        if (numR - static_cast<int>(numR))
            throw myException("not real factorial", -2);
        numL *= fact(numR); break;
    case's':
        if (numR < 0)
            throw myException("negative number in sqrt", -2);
        numL = sqrt(numR); break;
    case'a':numL *= fabs(numR); break;
    case'i':numL *= sin(numR); break;
    case'c':numL *= cos(numR); break;
    case't':numL *= tan(numR); break;
    case'o':numL /= tan(numR); break;
    case'l':
        if (numR < 0)
            throw myException("negative logarithm", -2);
        numL *= log10(numR); break;
    }
    prtyL = prtyR;
    operationL = operationR;
}

template<typename numType,
    typename it = typename Expression<numType>::iterator>
    it calculate_1_oper(it&& R)
{
    it L(R++);
    make_calculations
    (
        get<Number>(*L), get<Number>(*R),
        get<Operation>(*L), get<Operation>(*R),
        get<Priority>(*L), get<Priority>(*R)
    );
    return R;
}

template<typename numType>
numType calculate_res(Expression<numType>&& exp)
{
    while (exp.size() != 1)
        exp.erase(calculate_1_oper<numType>(
            std::max_element(exp.begin(), exp.end(), prtyComp<numType>)));
    return get<Number>(*exp.cbegin());
}

template<typename numType>
std::pair<int, string> call_calculator(const string& str)noexcept
{
    try
    {
        is_expression<numType>(str);
        return std::make_pair(-1, to_string(
            calculate_res(makeExpression<numType>(str))));
    }
    catch (const myException& ex)
    {
        return std::make_pair(ex.indx, ex.what());
    }
    catch (...)
    {
        return std::make_pair(-3, "unknown error");
    }
}
using it = Expression<double>::iterator;
template it calculate_1_oper<double>(it&& R);
template double calculate_res(Expression<double>&& exp);
template std::pair<int, string> call_calculator<double>(const string& str)noexcept;

using it2 = Expression<double>::iterator;
template it2 calculate_1_oper<rational>(it2&& R);
template rational calculate_res(Expression<rational>&& exp);
template std::pair<int, string> call_calculator<rational>(const string& str)noexcept;
