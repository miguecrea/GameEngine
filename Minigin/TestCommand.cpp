#include "TestCommand.h"
#include"iostream"
#include"staticHeader.h"
dae::TestCommand::TestCommand()
{
}

void dae::TestCommand::Execute()
{
    m_pacmanState = 2;
   std::cout<<"Command\n";
   std::cout<<m_pacmanState<<"\n";



}

void dae::TestCommand::Undo()
{
}
