#pragma once
#include <engine.h>
#include "glass.h"

//����
class PlayLevelObject : public game::ILevelObject, public event::CActor
{
public:
	PlayLevelObject();
	~PlayLevelObject();

private:
	game::Glass m_glass;
};