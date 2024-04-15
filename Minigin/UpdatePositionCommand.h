#pragma once
#include "Command.h"
#include <glm/glm.hpp>
#include"functional"

namespace dae
{
    class GameObject;
    class SceneManager;

    struct Point2f

    {
        int x, y;
    };

    class UpdatePositionCommand final : public Command
    {
    public:
        UpdatePositionCommand(GameObject* pGameObject, const glm::vec3& direction);

        Point2f GridToWorld(int row,int column);

        void Execute() override;
        void Undo() override;

    private:
        GameObject* m_pGameObject;
        SceneManager* m_pSceneManager{ nullptr };
        glm::vec3 m_OldPosition;
        glm::vec3 m_Direction;
    };
}

