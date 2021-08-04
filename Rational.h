#ifndef RATIONAL
#define RATIONAL

unsigned GCD_Impl(unsigned a, unsigned b)noexcept;
unsigned GCD(signed a, signed b);

struct rational
{
    rational(int numerator = 0, int denominator = 1);

    void add(const rational& other);
    void mul(const rational& other);
    void div(const rational& other);
    void sub(const rational& other);

    rational& operator+=(const rational& other);
    rational& operator-=(const rational& other);
    rational& operator*=(const rational& other);
    rational& operator/=(const rational& other);

    rational operator-()const;
    rational operator+()const;

    bool check_equal(const rational& other)const;
    bool check_greater(const rational& other)const;

    explicit operator double()const { return double(numerator) / denominator; }

    int numerator;
    int denominator;
};

rational operator+(rational dst, rational const& src);
rational operator-(rational dst, rational const& src);
rational operator*(rational dst, rational const& src);
rational operator/(rational dst, rational const& src);

bool operator==(const rational& lhs, const rational& rhs);
bool operator>(const rational& lhs, const rational& rhs);

bool operator<(const rational& lhs, const rational& rhs);
bool operator!=(const rational& lhs, const rational& rhs);
bool operator<=(const rational& lhs, const rational& rhs);
bool operator>=(const rational& lhs, const rational& rhs);

#endif // !RATIONAL