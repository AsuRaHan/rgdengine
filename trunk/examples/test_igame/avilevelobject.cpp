//AviLevelObject.cpp
#include "AviLevelObject.h"
#include <iostream>

AviLevelObject::AviLevelObject()
{
	std::cout << "1: AviLevelObject created. (press SPACE for send CCompliteLevelEvent)\n";
	m_cSpace.attachToControl(input::Keyboard,input::KeySpace);
	m_cSpace.addHandler(this,&AviLevelObject::onSpace);
}

AviLevelObject::~AviLevelObject()
{
	std::cout << "AviLevelObject destroyed." << std::endl;
}

//����� ����� if, ����� ����������� ������ �� ������� (��� ���� ����� ���������� � �� �������)
void AviLevelObject::onSpace(const input::CButtonEvent&) 
{
	if (m_cSpace) 
		sendEvent(game::CCompliteLevelEvent());
}

namespace game
{
	REGISTER_LEVEL_TYPE(AviLevelObject)
}