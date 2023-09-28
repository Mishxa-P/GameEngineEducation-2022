#pragma once

#include "Common.h"
#include "RenderProxy.h"


class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}
	
	float GetPosX() const { return m_vPosition[0]; }
	float GetPosY() const { return m_vPosition[1]; }
	float GetPosZ() const { return m_vPosition[2]; }
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetPosition(float x, float y, float z);
	float GetVelocityX() const { return m_Velocity[0]; };
	float GetVelocityY() const { return m_Velocity[1]; };
	float GetVelocityZ() const { return m_Velocity[2]; };
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	void SetVelocityZ(float z);
	void AddVelocityX(float dX);
	void AddVelocityY(float dY);
	void AddVelocityZ(float dZ);
	void SetVelocity(float x, float y, float z);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void Move(float deltaTime);
	virtual void Update(float deltaTime);

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];
	float m_Velocity[3];
};

