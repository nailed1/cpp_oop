#include "rational.h"
#include <iostream>
#include <cmath>

using namespace std;

Rational::Rational() {
    num = 0;
    den = 1;
}

Rational::Rational(int n) {
    num = n;
    den = 1;
}

Rational::Rational(int n, int d) {
    num = n;
    den = d;
}

Rational& Rational::operator+=(const Rational& r) {
    num = num * r.den + den * r.num;
    den = den * r.den;
    simplify();
    return(*this);
}

Rational Rational::operator+(const Rational& r) const {
    Rational R(*this);
    return R += r;
}

Rational& Rational::operator-=(const Rational& r) {
    num = num * r.den - den * r.num;
    den = den * r.den;
    simplify();
    return(*this);
}

Rational Rational::operator-(const Rational& r) const {
    Rational R(*this);
    return R -= r;
}

Rational& Rational::operator*=(const Rational& r) {
    num = num * r.num;
    den = den * r.den;
    simplify();
    return(*this);
}

Rational Rational::operator*(const Rational& r) const {
    Rational R(*this);
    return R *= r;
}

Rational& Rational::operator/=(const Rational& r) {
    num = num * r.den;
    den = den * r.num;
    simplify();
    return(*this);
}

Rational Rational::operator/(const Rational& r) const {
    Rational R(*this);
    return R /= r;
}

void Rational::simplify() {
    int a = abs(num);
    int b = abs(den);
    while (b!=0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int commonDivisor = a;

    num /= commonDivisor;
    den /= commonDivisor;

    if (den < 0) {
        num = -num;
        den = -den;
    }
}

void Rational::quadratic_function(const Rational& a, const Rational& b, const Rational& c) {
    Rational disc;
    disc = b*b - Rational(4)*a*c;

    if (double(disc) < 0) {
        cout << "no roots" << endl;
    }
    else if (double(disc) == 0.0) {
        Rational neg_b = Rational(-1) * b;
        Rational two_a = Rational(2) * a;
        Rational x1 = neg_b / two_a;
        cout << "Only one root and it is: " << x1.num << "/" << x1.den << endl;
    }
    else {
        int sq_num = (int)round(sqrt((double)disc.num));
        int sq_den = (int)round(sqrt((double)disc.den));

        if (sq_num * sq_num == disc.num && sq_den * sq_den == disc.den) {
            Rational sqrt_disc(sq_num, sq_den);

            Rational neg_b = Rational(-1) * b;
            Rational two_a = Rational(2) * a;

            Rational x1 = (neg_b + sqrt_disc) / two_a;
            Rational x2 = (neg_b - sqrt_disc) / two_a;

            cout << "First root (rational): " << x1.num << "/" << x1.den << endl;
            cout << "Second root (rational): " << x2.num << "/" << x2.den << endl;
        }
        else {
            Rational neg_b = Rational(-1) * b;
            double sq = sqrt(double(disc));
            double denom = double(Rational(2) * a);
            double x1 = (double(neg_b) + sq) / denom;
            double x2 = (double(neg_b) - sq) / denom;
            cout << "First root (irrational): " << x1 << endl;
            cout << "Second root (irrational): " << x2 << endl;
        }
    }
}

Rational::operator int() const {
    return num / den;
}

Rational::operator double() const {
    return ((double)num)/den;
}

Rational::Rational(double val) {
    double eps = 1e-9;
    long n = 0, d = 1, n_prev = 1, d_prev = 0;

    while (true) {
        long a = (long)val;
        long next_n = a * n + n_prev; n_prev = n; n = next_n;
        long next_d = a * d + d_prev; d_prev = d; d = next_d;

        if (std::abs(val - a) < eps) break; // Останавливаемся, если дробная часть исчезла
        val = 1.0 / (val - a);
    }
    this->den = n;
    this->num = d;
}
