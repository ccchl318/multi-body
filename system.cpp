#include "system.h"

void system1::add_particle(const Eigen::Vector2f xx) {
    particle new_particle(xx);
    particles.push_back(new_particle);
    int index = particles.size();
    for (int i = 0; i < index - 1; i++) {
        double dist = (new_particle.x - particles[i].x).norm();
        if (dist < connection_length) {
            rest_length[i][index - 1] = 0.1;
            rest_length[index - 1][i] = 0.1;
        }
    }
}

system1::system1() {

    for (int i = 0; i < max_num_particles; i++)
        for (int j = 0; j < max_num_particles; j++)
            rest_length[i][j] = 0;

    Eigen::Vector2f x1(0.5, 0.5);
    Eigen::Vector2f x2(0.6, 0.5);
    Eigen::Vector2f x3(0.55, 0.45);
    add_particle(x1);
    add_particle(x2);
    add_particle(x3);
}

void system1::update() {
    double inv_mass = 1 / mass;
    int n = particles.size();
    for (int i = 0; i < n; i++) {
        particles[i].v *= exp(-dt * damping);
        Eigen::Vector2f total_force = gravity * mass;
        for (int j = 0; j < n; j++) {
            if (rest_length[i][j] != 0) {
                Eigen::Vector2f x_ij = particles[i].x - particles[j].x;
                total_force += -spring_stiffness * (x_ij.norm() - rest_length[i][j]) * x_ij.normalized();

            }
        }
        particles[i].v += dt * total_force * inv_mass;
    }
    for (int i = 0; i < particles.size(); i++) {
        if (particles[i].x.y() < bottom) {
            particles[i].x.y() = bottom;
            particles[i].v.y() = -0.5 * particles[i].v.y();

        }
    }
    for (int i = 0; i < particles.size(); i++) {
        particles[i].x = particles[i].x + particles[i].v * dt;
    }

}

void system1::clear() {
    for (int i = 0; i < max_num_particles; i++)
        for (int j = 0; j < max_num_particles; j++)
            rest_length[i][j] = 0;
    particles.clear();
}

 