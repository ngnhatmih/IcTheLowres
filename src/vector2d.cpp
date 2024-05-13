#include "vector2d.h"
#include "math.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D::~Vector2D() {}

Vector2D Vector2D::operator+(const Vector2D &v2) const
{
    return Vector2D(x + v2.x, y + v2.y);
}

Vector2D Vector2D::operator-(const Vector2D &v2) const
{
    return Vector2D(x - v2.x, y - v2.y);
}

Vector2D Vector2D::operator*(float scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const
{
    return Vector2D(x / scalar, y / scalar);
}

Vector2D &Vector2D::operator+=(const Vector2D &v2)
{
    x += v2.x;
    y += v2.y;
    return *this;
}

Vector2D &Vector2D::operator-=(const Vector2D &v2)
{
    x -= v2.x;
    y -= v2.y;
    return *this;
}

Vector2D &Vector2D::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D &Vector2D::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

void Vector2D::normalize()
{
    float l = length();
    if (l > 0) {
        (*this) *= 1 / l;
    }
}

float Vector2D::length() const
{
    return sqrt(x * x + y * y);
}
