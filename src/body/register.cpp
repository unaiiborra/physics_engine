#include <cassert>
#include <cstddef>
#include <vector>

#include "body.hpp"
#include "types.hpp"

PhysicsBody PhysicsSolver::spawn(
    decimal_t mass,
    Vec2dec position,
    Vec2dec velocity,
    Vec2dec acceleration
) {
    size_t idx = get_count();

    inv_mass.push_back(1 / mass);
    pos.push_back(position);
    vel.push_back(velocity);
    acc.push_back(acceleration);

    size_t id = id_counter.fetch_add(1);
    bodies[id] = idx;
    indexes.push_back(id);

    return PhysicsBody(id);
}

PhysicsBody PhysicsSolver::spawn(decimal_t mass, Vec2dec pos) {
    return this->spawn(mass, pos, Vec2dec(0.0, 0.0), Vec2dec(0.0, 0.0));
}

void PhysicsSolver::remove(PhysicsBody body) {
    size_t id = body.id;

    if (!bodies.count(id))
        return;

    size_t idx = bodies[id];
    size_t last_idx = get_count() - 1;

    if (idx != last_idx) {
        pos[idx] = pos[last_idx];
        vel[idx] = vel[last_idx];
        acc[idx] = acc[last_idx];
        inv_mass[idx] = inv_mass[last_idx];

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

PhysicsBodySnapshot PhysicsSolver::get_snapshot(PhysicsBody body) {
    if (!bodies.count(body.id))
        return PhysicsBodySnapshot(Vec2<>(), Vec2<>(), Vec2<>());

    size_t idx = bodies[body.id];

    return PhysicsBodySnapshot(pos[idx], vel[idx], acc[idx]);
}
