#include "../headers/trajectory.h"
#include "../headers/transforms2D.h"

#include "components/simple_scene.h"

glm::mat3 trajectory::GenerateTrajectoryRectangle(glm::vec2& previousPoint, float x, float y)
{
    glm::vec2 currentPoint = glm::vec2(x, y);

    float segmentLength = glm::distance(previousPoint, currentPoint);
    float segmentAngle = atan2(currentPoint.y - previousPoint.y, currentPoint.x - previousPoint.x);

    glm::mat3 modelMatrixTrajectory{ glm::mat3(1) };

    modelMatrixTrajectory *= transforms2D::Translate(previousPoint.x, previousPoint.y)
        * transforms2D::Rotate(segmentAngle)
        * transforms2D::Scale(segmentLength / 2.0f, 1.0f);

    return modelMatrixTrajectory;
}
