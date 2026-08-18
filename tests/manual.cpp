#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

#include "body.hpp"
#include "integrators.hpp"
#include "types.hpp"

int main(void) {
    PhysicsSolver solver(std::make_unique<SemiImplicitEuler>());
    std::vector<PhysicsBody> bodies;

    for (size_t i = 0; i < 5; i++) {
        bodies.push_back(solver.spawn(
            i + 1,
            Vec2dec(5 - i, 5 + i),
            Vec2dec(5 - i, 5 + i),
            Vec2dec(5 - i, 5 + i)
        ));
    }

    size_t step_count = 0;

    while (true) {
        char input = fgetc(stdin);

        if (input == '\n') {
            solver.step(0.01);
            step_count++;

            std::cout << "--- step " << step_count << " ---\n";

            for (size_t i = 0; i < bodies.size(); i++) {
                PhysicsBodySnapshot snapshot = solver.get_snapshot(bodies[i]);
                std::cout << "Body(" << bodies[i].get_id() << ") "
                          << "pos=(" << snapshot.pos.x << ", " << snapshot.pos.y
                          << ") "
                          << "vel=(" << snapshot.vel.x << ", " << snapshot.vel.y
                          << ") "
                          << "acc=(" << snapshot.acc.x << ", " << snapshot.acc.y
                          << ")\n";
            }

            if (bodies.size()) {
                solver.remove(bodies.front());
                bodies.erase(bodies.begin());
            }
        }
    }

    return 0;
}
