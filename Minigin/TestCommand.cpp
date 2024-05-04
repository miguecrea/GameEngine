#include "TestCommand.h"
#include"iostream"
#include"staticHeader.h"
#include"Audio.h"
dae::TestCommand::TestCommand()
{
}

void dae::TestCommand::Execute()
{
    m_pacmanState = 2;
   std::cout<<"Command\n";
   std::cout<<m_pacmanState<<"\n";


   Audio::Get().ToggleMute();

}

void dae::TestCommand::Undo()
{
}
