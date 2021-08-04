#ifndef STR_VALIDATION
#define STR_VALIDATION

#include "Exception.h"
#include "Types.h"

struct rational;

template<typename numType>void is_expression(const string& exp);

bool is_minus(const char c)noexcept;
bool is_float(const char c)noexcept;
bool is_digit(const char c)noexcept;
bool is_function(const char c)noexcept;
bool is_opertaion(const char c)noexcept;
bool is_opening_bracket(const char c)noexcept;
bool is_closing_bracket(const char c)noexcept;
bool is_beginning_valid(const char c)noexcept;
bool is_ending_valid(const char c)noexcept;
bool is_expression_valid(const char prev, const char curr)noexcept;
bool is_rational_expression_valid(const char prev, const char curr)noexcept;

bool check_func_name(const string& exp, int& i);
bool check_float_num(bool& fl, const char c)noexcept;

void brackets(int& cnt, const char& c)noexcept;

char function_hash(const string& key)noexcept;

string get_func_name(const string& exp, int& i);

#endif //!STR_VALIDATION
