#include "Vec3.h"
#include <cmath>

Vec3::Vec3() {
    x = y = z = 0;
}

Vec3::Vec3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3 Vec3::operator+(const Vec3& v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(double s) const {
    return Vec3(x * s, y * s, z * s);
}

Vec3 Vec3::operator/(double s) const {
    return Vec3(x / s, y / s, z / s);
}

double Vec3::dot(const Vec3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

double Vec3::length() const {
    return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const {
    double len = length();
    return Vec3(x / len, y / len, z / len);
}

Vec3 Vec3::operator*(const Vec3& v) const {
    return Vec3(x * v.x, y * v.y, z * v.z);
}