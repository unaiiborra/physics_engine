#pragma once

#include "body.hpp"

class Euler: public PhysicsIntegrator {
    void integrate(
        double dt,
        size_t count,
        const decimal_t* acc,
        decimal_t* vel,
        decimal_t* pos
    ) override;
};

class SemiImplicitEuler: public PhysicsIntegrator {
    void integrate(
        double dt,
        size_t count,
        const decimal_t* acc,
        decimal_t* vel,
        decimal_t* pos
    ) override;
};
