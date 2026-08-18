#include <cassert>
#include <cstddef>

#include "body.hpp"
#include "types.hpp"

PhysicsBody PhysicsSolver::spawn(
    decimal_t mass,
    Vec2<decimal_t> position,
    Vec2<decimal_t> velocity,
    Vec2<decimal_t> acceleration
) {
    size_t idx = pos.size();

#ifdef DEBUG
    assert(
        idx == vel.size() && idx == acc.size() && idx == inv_mass.size()
        && idx == indexes.size()
    );
#endif

    inv_mass.push_back(1 / mass);
    pos.push_back(position);
    vel.push_back(velocity);
    acc.push_back(acceleration);

    size_t id = id_counter.fetch_add(1);
    bodies[id] = idx;
    indexes.push_back(id);

    return PhysicsBody(id);
}

PhysicsBody PhysicsSolver::spawn(decimal_t mass, Vec2<decimal_t> pos) {
    return this->spawn(
        mass,
        pos,
        Vec2<decimal_t>(0.0, 0.0),
        Vec2<decimal_t>(0.0, 0.0)
    );
}

void PhysicsSolver::remove(PhysicsBody body) {
    size_t id = body.id;

    if (!bodies.count(id))
        return;

    size_t idx = bodies[id];
    size_t last_idx = pos.size() - 1;

    if (idx != last_idx) {
        pos[idx] = pos[pos.size() - 1];
        vel[idx] = vel[vel.size() - 1];
        acc[idx] = acc[acc.size() - 1];
        inv_mass[idx] = inv_mass[inv_mass.size() - 1];

        size_t moved_id = indexes[last_idx];
        indexes[idx] = moved_id;
        bodies[moved_id] = idx;
    }

    pos.pop_back();
    vel.pop_back();
    acc.pop_back();
    inv_mass.pop_back();

    indexes.pop_back();
    bodies.erase(id);
}
