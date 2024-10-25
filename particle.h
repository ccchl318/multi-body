#include <Eigen/Eigen>

class particle {
public:
    particle() : x(0, 0), v(0, 0) {}

    particle(const Eigen::Vector2f xx) : x(xx), v(0, 0) {}

    Eigen::Vector2f x;
    Eigen::Vector2f v;
};