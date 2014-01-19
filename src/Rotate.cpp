#include <glm/glm.hpp>
#define DEBUG

glm::mat3 rodriguesMatrix(const float degrees, const glm::vec3& axis) {
    glm::mat3 v = glm::mat3(
            axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
            axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
            axis.x*axis.z, axis.y*axis.z, axis.z*axis.z
            );

    glm::mat3 v2 = glm::mat3(
            0, -axis.z, axis.y,
            axis.z, 0, -axis.x,
            -axis.y, axis.x, 0
            );

    glm::mat3 rotation = cos(degrees * M_PI/180.f) * glm::mat3(1.0f) +
               (1-cos(degrees * M_PI/180.f)) * v +
        sin(degrees * M_PI/180.f) * v2;

    return rotation;
}

void cool_rotate(float degrees, float* x, float* y, float* z)
{
    glm::vec3 y_unit = glm::vec3(0, 1.f, 0);
    glm::mat3 rotationMatrix = rodriguesMatrix(degrees, y_unit);
    glm::vec3 myVertice = glm::vec3(*x,*y,*z);
    glm::vec3 myVerticeRotated = myVertice*rotationMatrix;
    *x = myVerticeRotated[0];
    *y = myVerticeRotated[1];
    *z = myVerticeRotated[2];
}
