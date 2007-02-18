//MapLevelObject.cpp
#include "MapLevelObject.h"
#include <iostream>

MapLevelObject::MapLevelObject()
{
  std::cout << "3: MapLevelObject created. (press SPACE for send CCompliteLevelEvent)" << std::endl;
  m_cSpace.attachToControl(input::Keyboard,input::KeySpace);
  m_cSpace.addHandler(this, &MapLevelObject::onSpace);
}

MapLevelObject::~MapLevelObject()
{
	std::cout << "MapLevelObject destroyed." << std::endl;
}

//����� ����� if, ����� ����������� ������ �� ������� (��� ���� ����� ���������� � �� �������)
void MapLevelObject::onSpace(const input::CButtonEvent&)
{
	if (m_cSpace) 
		sendEvent(game::CCompliteLevelEvent());
}

namespace game
{
  REGISTER_LEVEL_TYPE(MapLevelObject)
}