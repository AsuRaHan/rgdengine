#pragma once
#include "engine.h"

//�����
class MapLevelObject : public game::ILevelObject, public event::CActor
{	
public:
    MapLevelObject();
   ~MapLevelObject();

private:
	void onSpace();

private:
	input::CKeyDown m_cSpace;
};