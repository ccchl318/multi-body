//
// Created by HL-Chen on 2024/3/12.
//

#include "rendering.h"

rendering::rendering(int w, int v) : height(v), width(w) {
    framebuffer.resize(w * v);

}

int inline rendering::getindex(int x, int y) {
    return (height - y) * width + x;
}

void rendering::draw( std::vector<particle> scene, double rest_length[max_num_particles][max_num_particles]) {
//    for (auto &i: scene) {
//        Eigen::Matrix2f a;
//        a << width, 0, 0, height;
//        i.x = a * i.x;
//        Eigen::Vector3f color(255, 255, 255);
//        draw_circle(i.x, 1, color);
//    }
    for (int i = 0; i < scene.size(); i++) {
        Eigen::Matrix2f a;
        a << width, 0, 0, height;
        scene[i].x = a * scene[i].x;
        Eigen::Vector3f color(255, 255, 255);
        draw_circle(scene[i].x, 1, color);
    }


    for (int i = 0; i < scene.size(); i++) {
        for (int j = 0; j < scene.size(); j++) {
            if (rest_length[i][j] != 0) {
                drawline(scene.at(i).x, scene.at(j).x);

            }
        }
    }
    drawline(Eigen::Vector2f(0, 25), Eigen::Vector2f(width, 25));
}


void rendering::set_pixel(const Eigen::Vector2f &point, const Eigen::Vector3f &color) {
    if (point.x() < 0 || point.x() >= width ||
        point.y() < 0 || point.y() >= height)
        return;
    auto ind = (height - point.y()) * width + point.x();
    framebuffer[ind] = color;
}

void rendering::clear() {
    for (auto &i: framebuffer)
        i = Eigen::Vector3f(0, 0, 0);
}


void rendering::drawline(Eigen::Vector2f begin, Eigen::Vector2f end) {
    auto x1 = begin.x();
    auto y1 = begin.y();
    auto x2 = end.x();
    auto y2 = end.y();

    Eigen::Vector3f line_color = {255, 255, 255};

    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = x1;
            y = y1;
            xe = x2;
        } else {
            x = x2;
            y = y2;
            xe = x1;
        }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
        set_pixel(point, line_color);
        for (i = 0; x < xe; i++) {
            x = x + 1;
            if (px < 0) {
                px = px + 2 * dy1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
//            delay(0);
            Eigen::Vector2f point = Eigen::Vector2f(x, y);
            set_pixel(point, line_color);
        }
    } else {
        if (dy >= 0) {
            x = x1;
            y = y1;
            ye = y2;
        } else {
            x = x2;
            y = y2;
            ye = y1;
        }
        Eigen::Vector2f point = Eigen::Vector2f(x, y);
        set_pixel(point, line_color);
        for (i = 0; y < ye; i++) {
            y = y + 1;
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
//            delay(0);
            Eigen::Vector2f point = Eigen::Vector2f(x, y);
            set_pixel(point, line_color);
        }
    }
}

void rendering::draw_circle(Eigen::Vector2f point, int r, Eigen::Vector3f &color) {
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y) {
        point.x() = std::round(point.x());
        point.y() = std::round(point.y());

        set_pixel(Eigen::Vector2f(point.x() + x, point.y() + y), color);
        set_pixel(Eigen::Vector2f(point.x() + y, point.y() + x), color);
        set_pixel(Eigen::Vector2f(point.x() - y, point.y() + x), color);
        set_pixel(Eigen::Vector2f(point.x() - x, point.y() + y), color);
        set_pixel(Eigen::Vector2f(point.x() - x, point.y() - y), color);
        set_pixel(Eigen::Vector2f(point.x() - y, point.y() - x), color);
        set_pixel(Eigen::Vector2f(point.x() + y, point.y() - x), color);
        set_pixel(Eigen::Vector2f(point.x() + x, point.y() - y), color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}