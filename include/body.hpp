#pragma once

#include <atomic>
#include <cassert>
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <vector>

#include "types.hpp"

class PhysicsSolver;

class PhysicsBody {
    size_t id;

  public:
    PhysicsBody(size_t id) : id(id) {}

    size_t get_id() const {
        return id;
    }
};

struct PhysicsBodySnapshot {
    Vec2dec pos, vel, acc;

    PhysicsBodySnapshot(Vec2dec pos, Vec2dec vel, Vec2dec acc) :
        pos(pos),
        vel(vel),
        acc(acc) {}
};

class PhysicsIntegrator {
  public:
    virtual void integrate(
        double dt,
        size_t count,
        const decimal_t* acc,
        decimal_t* vel,
        decimal_t* pos
    ) = 0;

    virtual ~PhysicsIntegrator() = default;
};

class PhysicsSolver {
    std::atomic_size_t id_counter = 0;

    std::unordered_map<size_t, size_t> bodies; // id to idx
    std::vector<size_t> indexes; // idx to id

    std::vector<decimal_t> inv_mass;
    std::vector<Vec2dec> pos, vel, acc;

    std::unique_ptr<PhysicsIntegrator> integrator = nullptr;

  public:
    PhysicsSolver(std::unique_ptr<PhysicsIntegrator> integrator) {
        set_integrator(std::move(integrator));
    }

    PhysicsBody spawn(decimal_t mass, Vec2dec pos, Vec2dec vel, Vec2dec acc);

    PhysicsBody spawn(decimal_t mass, Vec2dec pos);

    void remove(PhysicsBody body);

    void set_integrator(std::unique_ptr<PhysicsIntegrator> new_integrator) {
        this->integrator = std::move(new_integrator);
    }

    std::unique_ptr<PhysicsIntegrator>& get_integrator() {
        return integrator;
    }

    PhysicsBodySnapshot get_snapshot(PhysicsBody body);

    decimal_t get_mass(PhysicsBody body) {
        return 1 / inv_mass[body.get_id()];
    }

    decimal_t get_invmass(PhysicsBody body) {
        return inv_mass[body.get_id()];
    }

    Vec2dec get_pos(PhysicsBody body) {
        return pos[body.get_id()];
    }

    void step(double dt);

  private:
    size_t get_count() const {
        size_t count = indexes.size();

        assert(
            count == pos.size() && count == vel.size() && count == acc.size()
            && count == inv_mass.size()
        );

        return count;
    }

    void integrate(double dt);
};
