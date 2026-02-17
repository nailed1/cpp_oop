class Rational 
{
private:
    void simplify();


public:
    int num;
    int den;

    Rational();
    Rational(int n);
    Rational(int n, int d);
    Rational(double val);
    void quadratic_function(const Rational& a, const Rational& b, const Rational& c);


    Rational& operator +=(const Rational& r);
    Rational operator + (const Rational& r) const;
    Rational& operator -=(const Rational& r);
    Rational operator - (const Rational& r) const;
    Rational& operator *=(const Rational& r);
    Rational operator * (const Rational& r) const;
    Rational& operator /=(const Rational& r);
    Rational operator / (const Rational& r) const;
    operator int () const;
    operator double() const;
};