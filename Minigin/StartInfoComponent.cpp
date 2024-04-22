#include "StartInfoComponent.h"
#include "GameObject.h"
#include "imgui.h"

dae::StartInfoComponent::StartInfoComponent(int priority)
    :Component(priority)
{
}
void dae::StartInfoComponent::Render()
{
    ImGui::Begin("Start Info");

    ImGui::Spacing();

    ImGui::Text("Controller:");
    ImGui::Text("Pacman");
    ImGui::Text("Move using W, A, S, D");

    ImGui::Spacing();

    ImGui::Text("Goal:");
    ImGui::Text("Eat all the dots");
    ImGui::Text("Avoid ghosts");

    ImGui::Spacing();

    ImGui::Text("Power-Ups:");
    ImGui::Text("Eat power pellets to turn ghosts blue");
    ImGui::Text("Eat blue ghosts for extra points");

    if (ImGui::Button("Click Here to quit Pacman "))
    {
        ExitApplication();
    }
    if (ImGui::Button("Click Here to Close this app "))
    {
        GetOwner()->Destroy();
    }

    ImGui::End();
}

