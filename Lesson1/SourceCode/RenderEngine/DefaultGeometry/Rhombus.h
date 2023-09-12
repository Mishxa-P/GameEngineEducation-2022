#pragma once

#include "../RenderObject.h"

namespace
{
	struct RhombusPosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class Rhombus : public RenderObject
{
public:
	Rhombus();

private:
	inline static const RhombusPosColorVertex s_rhombusVertices[] =
	{
		{-1.0f,  0.0f,  0.0f, 0xff0000ff },
		{ 1.0f,  0.0f,  0.0f, 0xff0000ff },
		{ 0.0f, -1.0f,  0.0f, 0xff0000ff },
		{ 0.0f,  1.0f,  0.0f, 0xff0000ff },
		{ 0.0f,  0.0f, -1.0f, 0xff00ff00 },
		{ 0.0f,  0.0f,  1.0f, 0xff00ff00 },
	};

	inline static const uint16_t s_rhombusTriList[] =
	{
		0, 4, 3, 
		3, 4, 1,
		2, 4, 0, 
		2, 1, 4,
		0, 5, 3,
		3, 5, 1,
		2, 5, 0,
		2, 1, 5,
	};
};

