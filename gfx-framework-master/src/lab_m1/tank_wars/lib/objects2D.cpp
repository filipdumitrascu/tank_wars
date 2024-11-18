#include "../headers/objects2D.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

#include <vector>

Mesh* objects2D::CreateSquare(const std::string& name, glm::vec3 leftUpperCorner,
    float side, glm::vec3 color)
{
    glm::vec3 corner = leftUpperCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, -side, 0), color), // leftBottomCorner

        VertexFormat(corner + glm::vec3(side, -side, 0), color), // rightBottomCorner
        VertexFormat(corner + glm::vec3(side, 0, 0), color) // rightUpperCorner
    };

    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };

    Mesh* square = new Mesh(name);
    square->InitFromData(vertices, indices);

    return square;
}

Mesh* objects2D::CreateRectangle(const std::string& name, glm::vec3 centerLowerSide,
    float base, float height, glm::vec3 color, bool fill)
{
    glm::vec3 center = centerLowerSide;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color),
        VertexFormat(center + glm::vec3(base / 2.0f, 0, 0), color), // rightBottomCorner

        VertexFormat(center + glm::vec3(base / 2.0f, height, 0), color), // rightUpperCorner
        VertexFormat(center + glm::vec3(-base / 2.0f, height, 0), color), // leftUpperCorner

        VertexFormat(center + glm::vec3(-base / 2.0f, 0, 0), color) // leftBottomCorner
    };

    std::vector<unsigned int> indices = { 3, 4, 1, 2 };

    Mesh* rectangle = new Mesh(name);

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    
    } else {
        indices.push_back(3);
        indices.push_back(1);
    }

    rectangle->InitFromData(vertices, indices);
    
    return rectangle;
}

Mesh* objects2D::CreateCircle(const std::string& name, glm::vec3 center, float radius,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center, color)
    };

    for (int i = 0; i <= 30; i++) {
        float angle = 2.0f * glm::pi<float>() * float(i) / 30.0f;
        glm::vec3 vertex = center + glm::vec3(radius * cos(angle), radius * sin(angle), 0);

        vertices.push_back(VertexFormat(vertex, color));
    }

    std::vector<unsigned int> indices;
    for (int i = 1; i <= 30; i++) {
        indices.push_back(i);
    }

    Mesh* circle = new Mesh(name);

    circle->SetDrawMode(GL_TRIANGLE_FAN);
    circle->InitFromData(vertices, indices);

    return circle;
}

Mesh* objects2D::CreateTrapezoidsWithCircle(const std::string& name, glm::vec3 centerLowerSide,
    float len1, float len2, float len3, float len4, float radius,
    float height1, float height2, glm::vec3 color1, glm::vec3 color2)
{
    glm::vec3 middleLen4 = centerLowerSide;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(middleLen4, color2), // centerLen4
        VertexFormat(middleLen4 + glm::vec3(len4 / 2.0f, 0, 0), color2), // rightCornerLen4

        VertexFormat(middleLen4 + glm::vec3(len3 / 2.0f, height2, 0), color2), // rightCornerLen3
        VertexFormat(middleLen4 + glm::vec3(len2 / 2.0f, height2, 0), color1), // rightCornerLen2

        VertexFormat(middleLen4 + glm::vec3(len1 / 2.0f, height2 + height1, 0), color1), // rightCornerLen1
        VertexFormat(middleLen4 + glm::vec3(0, height2 + height1, 0), color1), // centerUpperSide

        VertexFormat(middleLen4 + glm::vec3(-len1 / 2.0f, height2 + height1, 0), color1), // leftCornerLen1
        VertexFormat(middleLen4 + glm::vec3(-len2 / 2.0f, height2, 0), color1), // leftCornerLen2

        VertexFormat(middleLen4 + glm::vec3(-len3 / 2.0f, height2, 0), color2), // leftCornerLen3
        VertexFormat(middleLen4 + glm::vec3(-len4 / 2.0f, 0, 0), color2), // leftCornerLen4
    };

    std::vector<unsigned int> indices = { 9, 1, 8,
                                          8, 1, 2,
                                          7, 3, 6,
                                          6, 3, 4 };

    glm::vec3 centerSemiCircle = vertices[5].position;

    for (int i = 0; i <= 30; i++) {
        float angle = glm::pi<float>() * i / 30.0f;
        glm::vec3 vertex = centerSemiCircle + glm::vec3(radius * cos(angle), radius * sin(angle), 0);

        vertices.push_back(VertexFormat(vertex, color1));
    }

    for (int i = 10; i <= 39; i++) {
        indices.push_back(5);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    Mesh* tankBody = new Mesh(name);
    tankBody->InitFromData(vertices, indices);

    return tankBody;
}
