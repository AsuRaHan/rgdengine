#pragma once
#include <rgde/engine.h>

//�����
class MapLevelObject : public game::level_object, public event::sender
{	
public:
    MapLevelObject();
   ~MapLevelObject();

private:
	void onSpace();

private:
	input::key_down m_cSpace;
};