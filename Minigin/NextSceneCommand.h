#pragma once
#include "Command.h"
#include"GameMode.h"
#include<string>
namespace dae
{
    class NextSceneCommand final : public Command
    {
    public:
        NextSceneCommand(const std::string & nameScene, GameMode gamemode);
        void Execute() override;
        virtual void Undo() override;

    private:
        std::string nameOfScene;
        GameMode m_gameMode;  //reference what does it mean 


    };
}

