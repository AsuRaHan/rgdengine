#pragma once

#include "engine.h"

//�����
class MapLevelObject : public game::ILevelObject, public event::CActor
{	
public:
	MapLevelObject();
	~MapLevelObject();

private:
	void onSpace(const input::CButtonEvent&);

private:
	input::CButtonCommand m_cSpace;
};