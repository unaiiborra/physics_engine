#pragma once
#include <cstddef>
#include <vector>

#include "types.hpp"

class PhysicsSolver;

class PhysicsConstraint {
  public:
    virtual ~PhysicsConstraint() = default;

    virtual size_t row_count() const = 0;
    virtual std::vector<size_t> body_ids() const = 0;

    virtual void compute_jacobian(
        const PhysicsSolver& solver,
        std::vector<Vec2<decimal_t>>& out_blocks
    ) const = 0;
    virtual decimal_t compute_error(const PhysicsSolver& solver) const = 0;
    virtual decimal_t compute_bias(const PhysicsSolver& solver) const = 0;
};
