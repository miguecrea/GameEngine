#include "Component.h"
#include <iostream>
#include "GameObject.h"

class HasOwnerException{};

bool dae::Component::operator<(const Component & other) const
{
	return m_Priority < other.m_Priority;


}

void dae::Component::SetOwner(GameObject * pGameObject)
{
	if (m_pOwner == nullptr)
	{
		m_pOwner = pGameObject;
	}
	else
	{
		throw HasOwnerException{};   //ok understood
	}
}

void dae::Component::SetPriority(int priority)
{
	m_Priority = priority;   //set ptiority 
}

int dae::Component::GetPriority() const
{
	return m_Priority;
}

dae::GameObject * dae::Component::GetOwner() const
{
	return m_pOwner;  //get owner 
}

void dae::Component::Update()
{
}

void dae::Component::FixedUpdate()
{
}

void dae::Component::Render()
{
}

dae::Component::Component(int priority)
	:m_pOwner{ nullptr }, m_Priority{ priority }
{
}
