#ifndef OBJECTS2D_H
#define OBJECTS2D_H

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include <string>

namespace objects2D
{
    // Creates squares used for field.
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftUpperCorner,
        float side, glm::vec3 color);

    // Creates rectangles used for lifebars and cannons.
    Mesh* CreateRectangle(const std::string& name, glm::vec3 centerLowerSide,
        float base, float height, glm::vec3 color, bool fill);
    
    // Creates a circle used for projectiles. 
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius,
        glm::vec3 color);
    
    /* Creates two trapezoids, one upside down on top of the other for tank's body.
    
          len1
         ______
        /      \     | 
       /  len2  \    |  height1
      /__________\   |
     ______________
      \   len3   /   |
       \        /    |  height2
        \      /     |
         ______      |
          len4
    */
    Mesh* CreateTrapezoidsWithCircle(const std::string& name, glm::vec3 centerLowerSide,
        float len1, float len2, float len3, float len4, float radius,
        float height1, float height2, glm::vec3 color1, glm::vec3 color2);
}

#endif /* OBJECTS2D_H */
