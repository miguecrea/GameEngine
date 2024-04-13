#pragma once
namespace dae
{
    enum class ButtonState     //other classes will 
    {
        Up, Down, Pressed
    };

    class Command {
    public:
        virtual ~Command() {}
        virtual void Execute() = 0;
        virtual void Undo() = 0;
    };
}
