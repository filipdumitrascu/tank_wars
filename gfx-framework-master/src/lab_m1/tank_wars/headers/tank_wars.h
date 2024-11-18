#ifndef TANK_WARS_H
#define TANK_WARS_H

#include "components/simple_scene.h"
#include "../headers/projectile.h"

namespace m1
{
    class TankWars : public gfxc::SimpleScene
    {
     public:
        TankWars();
        ~TankWars();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void CreateMeshes();
        void RenderTank(int tankLife, float oxTank, float& oyTank, float& angleTank, float angleCannon,
            std::vector<std::pair<float, float>>& fieldHeights, const std::string& name);

        void RenderProjectiles(int& tankLife, float oxTank, float oyTank, float angleTank, float deltaTimeSeconds,
            std::vector<std::pair<float, float>>& fieldHeights, std::list<projectile::Projectile>& projectilesTank);
        
        void RenderLifeBar(int tankLife, float oxTank, float oyTank);
        void RenderTrajectory(glm::vec2& startPos, float angleCanon, float angleTank);

     protected:
        std::vector<std::pair<float, float>> fieldHeights;

        std::list<projectile::Projectile> projectilesTank1;
        std::list<projectile::Projectile> projectilesTank2;

        std::vector<glm::vec2> trajectoryPoints1;
        std::vector<glm::vec2> trajectoryPoints2;

        int tank1Life;
        int tank2Life;

        float oxTank1;
        float oxTank2;

        float oyTank1;
        float oyTank2;

        float angleCannon1;
        float angleCannon2;

        float angleTank1;
        float angleTank2;

        float frstTrpzTopLen;
        float scndTrpzTopLen;

        float frstTrpzBottomLen;
        float scndTrpzBottomLen;

        float frstTrpzHeight;
        float scndTrpzHeight;

        float cannonBase;
        float cannonHeight;

        float turretRadius;
        float projectileRadius;
    };
}

#endif /* TANK_WARS_H */
