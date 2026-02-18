#include "rational.h"
#include <iostream>

using namespace std;

int main(){
    Rational a(1, 3);
    Rational b(1, 1);
    Rational c(1, 5);
    a.quadratic_function(a, b, c);
    double j = 0.5;
    cout << "double: " << j << endl;
    Rational r1(0.5);
    cout <<"double to rational: " << r1.num << "/" << r1.den << endl;
    bool res = a>=b;
    cout << res << endl;
}