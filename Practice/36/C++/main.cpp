#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

const auto PI = 3.141592653589793;

enum class coordinates_system { Cartesian, Polar };

class Point {
public:
    double x, y;
    Point(double = 0, double = 0, coordinates_system = coordinates_system::Cartesian);
    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;

    double get_x() const {
        return x;
    };

    double get_y() const {
        return y;
    };

    double get_r() const {
        return hypot(x, y);
    };

    double get_phi() const {
        return atan2(y, x);
    };

    void set_x(double x_new) {
        x = x_new;
    };

    void set_y(double y_new) {
        y = y_new;
    };

    void set_r(double);
    void set_phi(double);

private:
    std::string chunga{"changa - easter egg"};
};

Point::Point(double a1, double a2, coordinates_system coord_system) {
    if (coord_system == coordinates_system::Cartesian) {
        x = a1;
        y = a2;
    }

    else {
        x = cos(a2) * a1;
        y = sin(a2) * a1;
    }
}

void Point::set_r(double r) {
    double phi = get_phi();

    x = cos(phi) * r;
    y = sin(phi) * r;
}

void Point::set_phi(double phi) {
    double r = get_r();

    x = cos(phi) * r;
    y = sin(phi) * r;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return (fabs(lhs.x - rhs.x) < 1e-10) && (fabs(lhs.y - rhs.y) < 1e-10);
}

bool operator!=(const Point& lhs, const Point& rhs) {
    return !((fabs(lhs.x - rhs.x) < 1e-10) && (fabs(lhs.y - rhs.y) < 1e-10));
}

std::ostream& operator<<(std::ostream& output, const Point& point) {
    output << '(' << point.get_x() << ',' << point.get_y() << ')';
    return output;
}

std::istream& operator>>(std::istream& input, Point& point) {
    double buf;
    input.ignore(1);
    input >> buf;
    point.set_x(buf);
    input.ignore(1);
    input >> buf;
    point.set_y(buf);
    input.ignore(1);
    return input;
}


int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    } else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2);
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180*PI/180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
