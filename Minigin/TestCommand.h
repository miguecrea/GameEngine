#pragma once



#pragma once
#include "Command.h"
namespace dae
{
    class TestCommand final : public Command
    {
    public:
        TestCommand();
        void Execute() override;
        virtual void Undo() override;

    private:
       

    };
}
