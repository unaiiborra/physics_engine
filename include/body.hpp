#pragma once

#include <atomic>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "types.hpp"

class PhysicsBody {
    size_t id;

    PhysicsBody(size_t id) : id(id) {}
    friend class PhysicsSolver;
};

struct PhysicsBodySnapshot {
    size_t id;
    Vec2<decimal_t> pos, vel, acc;
};

class PhysicsSolver {
    std::atomic_size_t id_counter = 0;

    std::unordered_map<size_t, size_t> bodies; // id to idx
    std::vector<size_t> indexes; // idx to id

    std::vector<decimal_t> inv_mass;
    std::vector<Vec2<decimal_t>> pos, vel, acc;

  public:
    PhysicsBody spawn(
        decimal_t mass,
        Vec2<decimal_t> pos,
        Vec2<decimal_t> vel,
        Vec2<decimal_t> acc
    );

    PhysicsBody spawn(decimal_t mass, Vec2<decimal_t> pos);
    void remove(PhysicsBody body);

    void step(double dt);
};
