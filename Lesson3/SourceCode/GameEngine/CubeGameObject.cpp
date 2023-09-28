#include "CubeGameObject.h"
#include "../RenderEngine/CubeRenderProxy.h"

CubeGameObject::CubeGameObject(CubeType type, float posX, float posY, float posZ)
	:m_Type(type)
{
	m_pRenderProxy = new CubeRenderProxy();
	SetPosition(posX, posY, posZ);
	m_StartPos[0] = posX;
	m_StartPos[1] = posY;
	m_StartPos[2] = posZ;

	m_EndPos[0] = posX;
	m_EndPos[1] = posY;
	m_EndPos[2] = posZ + 5.0f;

}

void CubeGameObject::MoveLeft(float deltaTime)
{
	if (m_Type == ControllableCube)
	{
		SetPosX(GetPosX() - 5.0f * deltaTime);
	}
	
}

void CubeGameObject::MoveRight(float deltaTime)
{
	if (m_Type == ControllableCube)
	{
		SetPosX(GetPosX() + 5.0f * deltaTime);
	}
}

void CubeGameObject::Jump()
{
	if (m_StartPos[1] >= GetPosY())
	{
		AddVelocityY(3.2f);
	}
	else
	{
		AddVelocityY(-0.1f);
	}
}

void CubeGameObject::Update(float deltaTime)
{
	switch (m_Type)
	{

	case JumpingCube:
		Jump();
		break;

	case ControllableCube:
		break;

	case MovableCube:

		if (GetPosZ() < m_EndPos[2] && m_ForwardDirection)
		{
			SetVelocityZ(2.0f);
		}
		else
		{
			m_ForwardDirection = false;
		}

		if(GetPosZ() > m_StartPos[2] && !m_ForwardDirection)
		{
			SetVelocityZ(-2.0f);
		}
		else
		{
			m_ForwardDirection = true;
		}
		break;
	}

	Move(deltaTime);
}
