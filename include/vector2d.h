#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
public:
    Vector2D();
    Vector2D(float x, float y);
    ~Vector2D();

    float getX() const { return x; }
    float getY() const { return y; }

    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }

    Vector2D operator+(const Vector2D &v2) const;
    Vector2D operator-(const Vector2D &v2) const;
    Vector2D operator*(float scalar) const;
    Vector2D operator/(float scalar) const;

    Vector2D &operator+=(const Vector2D &v2);
    Vector2D &operator-=(const Vector2D &v2);
    Vector2D &operator*=(float scalar);
    Vector2D &operator/=(float scalar);

    void normalize();
    float length() const;

private:
    float x;
    float y;
};

#endif // VECTOR2D_H