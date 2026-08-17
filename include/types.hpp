#pragma once

typedef double decimal_t;

template<typename T = decimal_t>
struct Vec2 {
    T x, y;

  public:
    Vec2(T x, T y) : x(x), y(y) {}
};
