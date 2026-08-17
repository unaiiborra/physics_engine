#pragma once

#include <cstddef>

#include "types.hpp"

class PhysicsBody {
    size_t id;
};

struct PhysicsBodySnapshot {
    PhysicsBody body;
    Vec2<decimal_t> pos, vel, acc;
};
