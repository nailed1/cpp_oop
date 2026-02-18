#include "rational.h"
#include <iostream>
#include <cmath>

using namespace std;
//Определение рациональной дроби

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
//опреаторы сложение, вычитания, умножения, деления

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

//функция упрощения рациональной дроби с помощью алгоритма Евклида

void Rational::simplify() {
    int a = abs(num);
    int b = abs(den);
    while (b!=0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int commonDivisor = a; // НОД

    num /= commonDivisor;
    den /= commonDivisor;

    if (den < 0) {
        num = -num;
        den = -den;
    }
}

//Функция вычисления квадратного уравнения с 3 аргументами классами Rational (a,b,c)

void Rational::quadratic_function(const Rational& a, const Rational& b, const Rational& c) {
    Rational disc;
    disc = b*b - Rational(4)*a*c;
    //дискриминант<0 => нету корней
    if (double(disc) < 0) {
        cout << "no roots" << endl;
    }
    //если дискриминант равен нулю, то вычисляем только один корень, во весь оставшихся случаях по 2 корня
    else if (double(disc) == 0.0) {
        Rational neg_b = Rational(-1) * b;
        Rational two_a = Rational(2) * a;
        Rational x1 = neg_b / two_a;
        cout << "Only one root and it is: " << x1.num << "/" << x1.den << endl;
    }
    else {
        //выделяем две переменные для проверки того, что в дискрименанте можно вычислить точные корни
        int sq_num = (int)round(sqrt((double)disc.num));
        int sq_den = (int)round(sqrt((double)disc.den));
        //если можно вычислить точные корни => продолжаем рациональную запись
        if (sq_num * sq_num == disc.num && sq_den * sq_den == disc.den) {
            Rational sqrt_disc(sq_num, sq_den);

            Rational neg_b = Rational(-1) * b;
            Rational two_a = Rational(2) * a;

            Rational x1 = (neg_b + sqrt_disc) / two_a;
            Rational x2 = (neg_b - sqrt_disc) / two_a;

            cout << "First root (rational): " << x1.num << "/" << x1.den << endl;
            cout << "Second root (rational): " << x2.num << "/" << x2.den << endl;
        }
        //во всех остальных случаях переходим к вещественной записи числа (double)
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

//операторы перевода рациональной дроби в int (с потерей) и double

Rational::operator int() const {
    return num / den;
}

Rational::operator double() const {
    return ((double)num)/den;
}

//функция перевода вещественного числа в рациональную дробь

Rational::Rational(double val) {
    double eps = 1e-9;
    long n = 0, d = 1, n_prev = 1, d_prev = 0;

    while (true) {
        long a = (long)val;
        long next_n = a * n + n_prev; n_prev = n; n = next_n;
        long next_d = a * d + d_prev; d_prev = d; d = next_d;

        if (abs(val - a) < eps) break;
        val = 1.0 / (val - a);
    }
    this->den = n;
    this->num = d;
}

//лог. операции

bool Rational::operator==(const Rational& r) const {
    return num == r.num && den == r.den;
}

bool Rational::operator!=(const Rational& r) const {
    return !(*this == r);
}

bool Rational::operator<(const Rational& r) const {
    return num * r.den < r.num * den;
}

bool Rational::operator<=(const Rational& r) const {
    return *this < r || *this == r;
}

bool Rational::operator>(const Rational& r) const {
    return !(*this <= r);
}

bool Rational::operator>=(const Rational& r) const {
    return !(*this < r);
}