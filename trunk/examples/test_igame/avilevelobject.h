#pragma once
#include "engine.h"

//������������ �������
class AviLevelObject: public game::ILevelObject, public event::CActor
{
public:
    AviLevelObject();
   ~AviLevelObject();

private:
	void onSpace();

private:
	input::CKeyDown m_cSpace;
};