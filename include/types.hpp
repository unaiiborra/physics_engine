#pragma once

typedef double decimal_t;

template<typename T = decimal_t>
struct Vec2 {
    T x, y;

  public:
    Vec2() : x(0), y(0) {}

    Vec2(T x, T y) : x(x), y(y) {}

    Vec2<T> operator+(const Vec2<T>& b) {
        return Vec2<T>(this->x + b.x, this->y + b.y);
    }

    Vec2<T> operator-(const Vec2<T>& b) {
        return Vec2<T>(this->x - b.x, this->y - b.y);
    }

    Vec2<T> operator*(const Vec2<T>& b) {
        return Vec2<T>(this->x * b.x, this->y * b.y);
    }

    Vec2<T> operator/(const Vec2<T>& b) {
        return Vec2<T>(this->x / b.x, this->y / b.y);
    }
};
