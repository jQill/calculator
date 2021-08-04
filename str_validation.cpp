#include "str_validation.h"

bool is_minus(const char c)noexcept { return c == '-'; }
bool is_opening_bracket(const char c)noexcept { return c == '('; }
bool is_closing_bracket(const char c)noexcept { return c == ')'; }
bool is_float(const char c)noexcept { return c == '.'; }
bool is_digit(const char c)noexcept { return c >= '0' && c <= '9'; }
bool is_function(const char c)noexcept { return c >= 'a' && c <= 't'; }
bool is_opertaion(const char c)noexcept
{
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '^';
}

void brackets(int& cnt, const char& c)noexcept
{
    if (c == '(')cnt++;
    if (c == ')')cnt--;
}

char function_hash(const string& key)noexcept
{
    return
        key == "fact" ? 'f' :
        key == "sqrt" ? 's' :
        key == "abs" ? 'a' :
        key == "sin" ? 'i' :
        key == "cos" ? 'c' :
        key == "tan" ? 't' :
        key == "cot" ? 'o' :
        key == "log" ? 'l' :
        '\0';
}

bool is_expression_valid(const char prev, const char curr)noexcept
{
    return
        is_digit(prev) && (
            is_digit(curr) ||
            is_opertaion(curr) ||
            is_closing_bracket(curr)) ||

        is_opertaion(prev) && (
            is_digit(curr) ||
            is_opening_bracket(curr)) ||

        is_opening_bracket(prev) && (
            is_digit(curr) ||
            is_minus(curr) ||
            is_opening_bracket(curr)) ||

        is_closing_bracket(prev) && (
            is_opertaion(curr) ||
            is_closing_bracket(curr));
}

bool is_rational_expression_valid(const char prev, const char curr)noexcept
{
    return
        is_expression_valid(prev, curr) ||

        is_float(prev) && is_digit(curr) ||
        is_digit(prev) && is_float(curr) ||
        is_opertaion(prev) && is_function(curr) ||
        is_opening_bracket(prev) && is_function(curr) ||

        is_function(prev) && (
            is_function(curr) ||
            is_opening_bracket(curr));
}

string get_func_name(const string& exp, int& i)
{
    int j = i;
    while (is_function(exp[i]))++i;
    return string(&exp[j], &exp[i]);
}

bool check_func_name(const string& exp, int& i)
{
    string name = get_func_name(exp, i);
    return function_hash(name) == '\0' || !is_opening_bracket(exp[i]);
}

bool check_float_num(bool& fl, const char c)noexcept
{
    if (fl)
    {
        if (is_float(c))
            return true;
        fl = is_opertaion(c);
    }
    fl = is_float(c);
    return false;
}

bool is_beginning_valid(const char c)noexcept
{
    return is_digit(c) || is_opening_bracket(c) || is_minus(c);
}

bool is_ending_valid(const char c)noexcept
{
    return is_digit(c) || is_closing_bracket(c);
}

template<>void is_expression<double>(const string& exp)
{
    int bracket_cnt = 0, i = 0;
    bool float_num = false;
    if (!is_beginning_valid(exp[0]) && !is_function(exp[0]) ||
            is_function(exp[i]) && check_func_name(exp, i))
        throw myException("incorrect input", 0);
    while (i < exp.size() - 1)
    {
        if (is_function(exp[i]) && check_func_name(exp, i))
            throw myException("incorrect input", i);
        else
        {
            brackets(bracket_cnt, exp[i]);
            if (!is_rational_expression_valid(exp[i], exp[i + 1]) ||
                    check_float_num(float_num, exp[i]))
                throw myException("incorrect input", i);
            ++i;
        }
    }
    if (!is_ending_valid(exp[i]))
        throw myException("incorrect input", i);
    brackets(bracket_cnt, exp[i]);
    if (bracket_cnt)
        throw myException("ops! problem with brackets", i);
}

template<>void is_expression<rational>(const string& exp)
{
    int bracket_cnt = 0, i;
    if (!is_beginning_valid(exp[0]))
        throw myException("incorrect input", 0);
    for (i = 0; i < exp.size() - 1; ++i)
    {
        brackets(bracket_cnt, exp[i]);
        if (!is_expression_valid(exp[i], exp[i + 1]))
            throw myException("incorrect input", i);
    }
    if (!is_ending_valid(exp[i]))
        throw myException("incorrect input", i);
    brackets(bracket_cnt, exp[i]);
    if(bracket_cnt)
        throw myException("ops! problem with brackets", i);
}
