#pragma once
#include <rgde/engine.h>

//������������ �������
class AviLevelObject: public game::level_object, public event::sender
{
public:
    AviLevelObject();
   ~AviLevelObject();

private:
	void onSpace();

private:
	input::KeyDown m_cSpace;
};