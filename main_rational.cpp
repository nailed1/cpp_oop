#include "rational.h"
#include <iostream>

using namespace std;

int main(){
    Rational a(1, 1);
    Rational b(-11, 12);
    Rational c(2, 12);
    a.quadratic_function(a, b, c);
    double j = 2.0/9.0;
    cout << "double: " << j << endl;
    Rational r1(j);
    cout <<"double to rational: " << r1.num << "/" << r1.den << endl;
}