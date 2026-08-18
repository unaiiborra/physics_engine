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

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<decimal_t> Vec2dec;
