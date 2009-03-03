#include "precompiled.h"

#include <rgde/game/level.h>

namespace game
{
	Level::Level(const std::string& name, const std::string& next_level)
		:	m_name(name),
			m_next_level(next_level)
	{
		base::lmsg << "Level::Level() " << name << base::endl;

		core::Function::Func func = boost::bind(&Level::addTypeToCreate, this, _1);
		core::FunctionsOwner::addFunction(core::Function("AddTypeToCreate", func));
	}

	void Level::addTypeToCreate(const std::string& type_name)
	{
		m_listTypes.push_back(type_name);
	}

	Level::~Level()
	{
		base::lmsg << "Level::~Level()" << base::endl;
	}

	//������������� ������
	void Level::enter()
	{
		typedef std::list<std::string> StringList;
		for (StringList::iterator it = m_listTypes.begin(); it != m_listTypes.end(); ++it)
		{
			std::string& type_name = *it;
			level_object* pLevelObj = LevelObjFactory::Instance().create(type_name);
			m_listLevelObjs.push_back(pLevelObj);
		}
	}

	//��������������� ������
	void Level::leave()
	{
		//... �������, ��� ������� ��������� �������� ���� ������� ���:
		//(�� ���� � �������)
		std::list<level_object*>::iterator i = m_listLevelObjs.begin();
		while (i != m_listLevelObjs.end())
		{
			delete (*i);
			++i;
		}
		m_listLevelObjs.clear();
	}
}