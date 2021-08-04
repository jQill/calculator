#include "Rational.h"

unsigned GCD_Impl(unsigned a, unsigned b)noexcept
{
	return b == 0 ? a : GCD_Impl(b, a % b);
}

unsigned GCD(signed a, signed b)
{
	a = a >= 0 ? a : -a;
	b = b >= 0 ? b : -b;
	if (a == b)return a;
	return GCD_Impl(a, b);
}

rational::rational(int numerator, int denominator)
	:numerator(numerator), denominator(denominator) {};

void rational::add(const rational& other)
{
	numerator = numerator * other.denominator +
		other.numerator * denominator;
	denominator *= other.denominator;
	int factor = GCD(numerator, denominator);
	numerator /= factor;
	denominator /= factor;
}

void rational::mul(const rational& other)
{
	int factor = GCD(
		numerator *= other.numerator,
		denominator *= other.denominator);
	numerator /= factor;
	denominator /= factor;
}

void rational::div(const rational& other)
{
	mul(rational(other.denominator, other.numerator));
}

void rational::sub(const rational& other) { add(-other); }

bool rational::check_equal(const rational& other)const
{
	return numerator == other.numerator &&
		denominator == other.denominator ?
		true : false;
}

bool rational::check_greater(const rational& other)const
{
	return other.denominator * numerator > other.numerator * denominator;
}


rational& rational::operator+=(const rational& other) { add(other); return *this; }
rational& rational::operator-=(const rational& other) { sub(other); return *this; }
rational& rational::operator*=(const rational& other) { mul(other); return *this; }
rational& rational::operator/=(const rational& other) { div(other); return *this; }


rational rational::operator-()const { return rational(-numerator, denominator); }
rational rational::operator+()const { return *this; }

rational operator+(rational dst, rational const& src) { dst.add(src); return dst; }
rational operator-(rational dst, rational const& src) { dst.sub(src); return dst; }
rational operator*(rational dst, rational const& src) { dst.mul(src); return dst; }
rational operator/(rational dst, rational const& src) { dst.div(src); return dst; }

bool operator==(const rational& lhs, const rational& rhs) { return lhs.check_equal(rhs); }
bool operator>(const rational& lhs, const rational& rhs) { return lhs.check_greater(rhs); }

bool operator<(const rational& lhs, const rational& rhs) { return rhs > lhs; }
bool operator!=(const rational& lhs, const rational& rhs) { return !(lhs == rhs); }
bool operator<=(const rational& lhs, const rational& rhs) { return !(lhs > rhs); }
bool operator>=(const rational& lhs, const rational& rhs) { return !(rhs > lhs); }