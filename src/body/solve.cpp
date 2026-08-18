#include <cassert>

#include "body.hpp"
#include "types.hpp"

void PhysicsSolver::step(double dt) {
    integrate(dt);
}

void PhysicsSolver::integrate(double dt) {
    integrator->integrate(
        dt,
        pos.size() * 2,
        reinterpret_cast<const decimal_t*>(acc.data()),
        reinterpret_cast<decimal_t*>(vel.data()),
        reinterpret_cast<decimal_t*>(pos.data())
    );
}
