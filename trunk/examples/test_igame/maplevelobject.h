#pragma once
#include <rgde/engine.h>

//�����
class MapLevelObject : public game::ILevelObject, public event::CSender
{	
public:
    MapLevelObject();
   ~MapLevelObject();

private:
	void onSpace();

private:
	input::KeyDown m_cSpace;
};