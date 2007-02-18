#pragma once

#include "engine.h"

//������������ �������
class AviLevelObject: public game::ILevelObject, public event::CActor
{	
public:
	AviLevelObject();
	~AviLevelObject();

private:
	void onSpace(const input::CButtonEvent&);

private:
	input::CButtonCommand m_cSpace;
};