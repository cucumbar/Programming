#include <iostream>
#include <set>
#include <sstream>
#include <istream>
#include <vector>
#include <string>
#include <algorithm>

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        num = numerator;
        den = (num == 0) ? 1 : denominator;

        if ((num < 0) && (den < 0)) {
            num = std::abs(num);
            den = std::abs(den);
        }

        else if ((num > 0) && (den < 0)) {
            num = -num;
            den = -den;
        }

        int temp = euclides(std::abs(num), std::abs(den));

        num /= temp;
        den /= temp;
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }

private:
    int num{ 0 }, den{ 1 };

    int euclides(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) {
                a %= b;
            }
            else {
                b %= a;
            }

        }
        return a + b;
    }

};

//======================= ^^(1 chast)^^ vv(2 chast)vv

int euclides(int a, int b) {
    while (a > 0 && b > 0) {
        if (a > b) {
            a %= b;
        }
        else {
            b %= a;
        }

    }
    return a + b;
}

bool operator== (const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator+ (const Rational& lhs, const Rational& rhs) {
    int temp = ((lhs.Denominator() * rhs.Denominator()) / euclides(lhs.Denominator(), rhs.Denominator()));
    return { (lhs.Numerator() * temp / lhs.Denominator()) + (rhs.Numerator() * temp / rhs.Denominator()), temp };
}

Rational operator- (const Rational& lhs, const Rational& rhs) {
    int temp = ((lhs.Denominator() * rhs.Denominator()) / euclides(lhs.Denominator(), rhs.Denominator()));
    return { (lhs.Numerator() * temp /  lhs.Denominator()) - (rhs.Numerator() * temp / rhs.Denominator()), temp};
}

//======================= ^^(2 chast)^^ vv(3 chast)vv

Rational operator* (const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/ (const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
}

//======================= ^^(3 chast)^^ vv(4 chast)vv

std::ostream& operator<< (std::ostream& out, const Rational& rhs) {
    out << rhs.Numerator() << '/' << rhs.Denominator();
    return out;
}

std::istream& operator>> (std::istream& in, Rational& rhs) {
    int t1, t2;
    char slash('/'), t_c;
    if (!(in >> t1) || !(in >> t_c) || !(in >> t2)){
        return in;
    }

    else if (t_c != slash) {
        return in;
    }

    else {
        rhs = Rational(t1, t2);
        return in;
    }
}

//======================= ^^(4 chast)^^ vv(5 chast)vv
bool operator< (const Rational& lhs, const Rational& rhs) {
    double t1, t2;
    t1 = ((double)lhs.Numerator()) / lhs.Denominator();
    t2 = ((double)rhs.Numerator()) / rhs.Denominator();
    return (t1 < t2);
}

using namespace std;


int main() {
    cout << "OK" << endl;
    return 0;
}
