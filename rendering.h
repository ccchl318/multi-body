//
// Created by HL-Chen on 2024/3/12.
//

#ifndef MULTI_BODY_RENDERING_H
#define MULTI_BODY_RENDERING_H

#include"system.h"

class rendering {
public:
    rendering(int w, int v);

    int getindex(int x, int y);

    void draw( std::vector<particle> scene, double rest_length[max_num_particles][max_num_particles]);

    void set_pixel(const Eigen::Vector2f &point, const Eigen::Vector3f &color);

    void clear();

    std::vector<Eigen::Vector3f> *get_frame() { return &framebuffer; };

private:
    void drawline(Eigen::Vector2f begin, Eigen::Vector2f end);

    void draw_circle(Eigen::Vector2f point, int r, Eigen::Vector3f &color);

    std::vector<Eigen::Vector3f> framebuffer;
    int height;
    int width;


};


#endif //MULTI_BODY_RENDERING_H
