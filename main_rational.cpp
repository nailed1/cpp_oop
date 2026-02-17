#include "rational.h"
#include <iostream>

using namespace std;

int main(){
    Rational r(3);
    Rational t(15, 2);
    Rational m;
    m = r * t;
    Rational a(1, 1);
    Rational b(-11, 12);
    Rational c(2, 12);
    a.quadratic_function(a, b, c);

    cout << "m_num: " << m.num << " m_den: " << m.den << endl;
    cout << "double: " << double(m) << endl;
}