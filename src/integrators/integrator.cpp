#include <cstddef>

#include "integrators.hpp"

void Euler::integrate(
    double dt,
    size_t count,
    const decimal_t* __restrict__ acc,
    decimal_t* __restrict__ vel,
    decimal_t* __restrict__ pos
) {
    for (size_t i = 0; i < count; i++) {
        pos[i] += vel[i] * dt;
        vel[i] += acc[i] * dt;
    }
}

void SemiImplicitEuler::integrate(
    double dt,
    size_t count,
    const decimal_t* __restrict__ acc,
    decimal_t* __restrict__ vel,
    decimal_t* __restrict__ pos
) {
    for (size_t i = 0; i < count; i++) {
        vel[i] += acc[i] * dt;
        pos[i] += vel[i] * dt;
    }
}
