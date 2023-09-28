#include "GameObject.h"


void GameObject::SetPosX(float x)
{
	m_vPosition[0] = x;
	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::SetPosY(float y)
{
	m_vPosition[1] = y;
	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::SetPosZ(float z)
{
	m_vPosition[2] = z;
	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::SetPosition(float x, float y, float z)
{
	m_vPosition[0] = x;
	m_vPosition[1] = y;
	m_vPosition[2] = z;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::SetVelocityX(float x)
{
	m_Velocity[0] = x;
}

void GameObject::SetVelocityY(float y)
{
	m_Velocity[1] = y;
}

void GameObject::SetVelocityZ(float z)
{
	m_Velocity[2] = z;
}

void GameObject::AddVelocityX(float dX)
{
	m_Velocity[0] += dX;
}

void GameObject::AddVelocityY(float dY)
{
	m_Velocity[1] += dY;
}

void GameObject::AddVelocityZ(float dZ)
{
	m_Velocity[2] += dZ;
}

void GameObject::SetVelocity(float x, float y, float z)
{
	m_Velocity[0] = x;
	m_Velocity[1] = y;
	m_Velocity[2] = z;
}

void GameObject::MoveLeft(float deltaTime)
{
}

void GameObject::MoveRight(float deltaTime)
{
}

void GameObject::Move(float deltaTime)
{
	m_vPosition[0] += m_Velocity[0] * deltaTime;
	m_vPosition[1] += m_Velocity[1] * deltaTime;
	m_vPosition[2] += m_Velocity[2] * deltaTime;

	m_pRenderProxy->SetPosition(m_vPosition);
}

void GameObject::Update(float deltaTime)
{
	Move(deltaTime);
}
