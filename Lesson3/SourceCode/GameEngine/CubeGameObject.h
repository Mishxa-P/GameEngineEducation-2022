#pragma once

#include "GameObject.h"

enum CubeType : UINT32
{
	JumpingCube, ControllableCube, MovableCube	
};

class CubeGameObject final : public GameObject
{
public:
	CubeGameObject(CubeType type, float posX, float posY, float posZ);
	void MoveLeft(float deltaTime) override;
	void MoveRight(float deltaTime) override;
	void Jump();
	virtual void Update(float deltaTime) override;

private:
	CubeType m_Type;
	float m_StartPos[3];
	float m_EndPos[3];
	bool m_ForwardDirection = false;
};

