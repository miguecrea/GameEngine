#pragma once

#include "Singleton.h"
#include"string"
#include"GameMode.h"

struct PlayerInfo
{
    std::string name;
    int index{ 0 };
    int nrLives{ 4 };
    int score{ 0 };
};




enum class PlayerDirection
{

    LEFT,
    UP,
    DOWN,
    RIGHT

};


namespace dae
{

    class PacmanManager :public dae::Singleton<PacmanManager>
    {


    public:

        //add a player 
        //add a power up



        void SetGameMode(GameMode gameMode)
        {
            m_GameMode = gameMode;
        }

        GameMode GetMode() const
        {
            return m_GameMode;
        }


        PlayerDirection m_pacmanDirection;


    private:

        GameMode m_GameMode{GameMode::Menu};





    };

};