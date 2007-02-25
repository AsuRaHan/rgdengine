//MapLevelObject.cpp
#include "MapLevelObject.h"
#include <iostream>

MapLevelObject::MapLevelObject()
{
    std::cout << "3: MapLevelObject created. (press SPACE for send CCompliteLevelEvent)" << std::endl;

    {
        using namespace input;

        CInput::addCommand(L"Space");
        CInput::getDevice(Keyboard)->getControl(KeySpace )->bind(L"Space");
        m_cSpace.attach(L"Space");
        m_cSpace += boost::bind(&MapLevelObject::onSpace, this);
    }
}

MapLevelObject::~MapLevelObject()
{
	std::cout << "MapLevelObject destroyed." << std::endl;
}

void MapLevelObject::onSpace()
{
	sendEvent(game::CCompliteLevelEvent());
}

namespace game
{
  REGISTER_LEVEL_TYPE(MapLevelObject)
}