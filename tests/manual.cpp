#include <cstdio>
#include <memory>

#include "body.hpp"
#include "integrators.hpp"

int main(void) {
    PhysicsSolver solver(std::make_unique<SemiImplicitEuler>());

    while (true) {
        char input = fgetc(stdin);

        if (input == '\n') {
            solver.step(0.01);
        }
    }

    return 0;
}
