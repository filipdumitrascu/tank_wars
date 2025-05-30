#ifndef TRANSFORMS2D_H
#define TRANSFORMS2D_H

#include "utils/glm_utils.h"

namespace transforms2D
{
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        return glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
    }

    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        return glm::mat3(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
    }

    inline glm::mat3 Rotate(float radians)
    {
        return glm::mat3(cos(radians), sin(radians), 0, -sin(radians), cos(radians), 0, 0, 0, 1);
    }

    inline glm::mat3 Shear(float slope) {
        return glm::mat3(1, slope, 0, 0, 1, 0, 0, 0, 1);
    }
}

#endif /* TRANSFORMS2D_H */
