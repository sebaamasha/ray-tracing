#pragma once

class Vec3 {
public:
    double x, y, z;

    Vec3();
    Vec3(double x, double y, double z);
    Vec3 operator*(const Vec3& v) const;
    
    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(double s) const;
    Vec3 operator/(double s) const;

    double dot(const Vec3& v) const;

    double length() const;

    Vec3 normalize() const;
};