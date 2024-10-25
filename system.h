#include "particle.h"
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

#define max_num_particles 256
#define connection_length 0.15

class system1 {
private:

    std::vector<particle> particles;
    double bottom = 0.05;


    double dt = 0.001;
    double damping = 20;
    double mass = 1;
    double spring_stiffness = 10000;
    Eigen::Vector2f gravity = Eigen::Vector2f(0, -9.8);


public:
    static void onMouse(int event, int x, int y, int flags, void *userdata) {
        if (event == cv::EVENT_LBUTTONDOWN) {
            system1 *self = static_cast<system1 *>(userdata);
            self->handleMouseClick(x, y);
        }
    }

    void handleMouseClick(int x, int y) {
        float xf = static_cast<float>(x) / 512.0f;
        float yf = 1.0f - static_cast<float>(y) / 512.0f; // 假设你想将y轴翻转
        Eigen::Vector2f pos(xf, yf);
        add_particle(pos);
    }

    void update();

    double rest_length[max_num_particles][max_num_particles];


    void add_particle(const Eigen::Vector2f xx);

    void add_damping() { damping *= 1.1; }

    void minus_damping() { damping /= 1.1; }

    void add_stiffness() { spring_stiffness *= 1.1; }

    void minus_stiffness() { spring_stiffness /= 1.1; }

    system1();

    double get_stiffness() { return spring_stiffness; }

    double get_damping() { return damping; }

    std::vector<particle> get_data() { return particles; }
    void clear();

};