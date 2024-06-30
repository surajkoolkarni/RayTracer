#include <glm/glm.hpp>

#include <cstdint>
#include <fstream>
#include <vector>

#include "Triangle.h"

float clamp(float min, float max, float value)
{
    if (value <= min)
        return min;
    else if (value >= max)
        return max;

    return value;
}

int main(int argc, char** argv)
{
    glm::vec3 v0(-1, -1, -5);
    glm::vec3 v1(1, -1, -5);
    glm::vec3 v2(0, 1, -5);

    const uint32_t width = 640;
    const uint32_t height = 480;
    glm::vec3 cols[3] = { {0.6, 0.4, 0.1}, {0.1, 0.5, 0.3}, {0.1, 0.3, 0.7} };
    std::vector<glm::vec3> framebuffer(width * height, glm::vec3(0.f));
    auto pix = framebuffer.begin();
    float fov = 51.52;
    float scale = tan(glm::radians(fov * 0.5));
    float imageAspectRatio = width / (float)height;
    glm::vec3 orig(0);
    Triangle triangle(v0, v1, v2);
    for (uint32_t j = 0; j < height; ++j) {
        for (uint32_t i = 0; i < width; ++i) {
            // compute primary ray
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            glm::vec3 dir(x, y, -1);
            //cameraToWorld.multDirMatrix(glm::vec3(x, y, -1), dir);
            dir = glm::normalize(dir);
            float t;
            if (triangle.intersect(dir, orig, t)) {
                *pix = triangle.baryCentric.u * cols[0] + triangle.baryCentric.v * cols[1] + (1.f - (triangle.baryCentric.u + triangle.baryCentric.v))  * cols[2];
            }
            pix++;
        }
    }

    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (uint32_t i = 0; i < height * width; ++i) {
        unsigned char r = (unsigned char)(255 * clamp(0, 1, framebuffer[i].x));
        unsigned char g = (unsigned char)(255 * clamp(0, 1, framebuffer[i].y));
        unsigned char b = (unsigned char)(255 * clamp(0, 1, framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

    return 0;
}