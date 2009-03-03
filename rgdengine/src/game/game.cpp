#include "precompiled.h"

#include <rgde/game/game.h>

#include <rgde/core/Timer.h>
#include <rgde/core/application.h>

namespace game
{
	//�������������
	void game_system::init(const std::string& strXmlGameConfig)
	{
        //������ �� ������, ���� ��� ������� �� ������
        if (strXmlGameConfig == "")
            return;

		std::string fname = "Media/" + strXmlGameConfig;
		TiXmlDocument doc(fname);

		if (!doc.LoadFile())
		{
			//... ��������, ��� �� ������� ��������� xml ���� � ������������� ���������
			//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		}
		else
		{
			TiXmlNode *root = doc.FirstChild("game");

			if (!root)
				return;

			TiXmlElement *game = root->ToElement();

			if (!game)
				return;

			//������ ��������� ������� ����
			std::string strCurrentLevel = game->Attribute("startlevel");

			//��������� ��� ������, ������� ��������� � ����
			TiXmlElement *level = game->FirstChildElement("level");

			while (level)
			{
				std::string name = level->Attribute("name");
				std::string nextlevel = level->Attribute("nextlevel");

				//�������� �������
				Level* pLevel = new Level(name,nextlevel);
				addLevel(name,nextlevel);

				//��������� ������ ��������, ������� ������ ������� �������	
				TiXmlElement *levelobject = level->FirstChildElement("levelobject");

				while (levelobject)
				{
					std::string type = levelobject->Attribute("type");
					pLevel->callFunction("AddTypeToCreate", type);
					levelobject = levelobject->NextSiblingElement("levelobject");
				}

				level = level->NextSiblingElement("level");
			}

			setCurrentLevel(strCurrentLevel);
		}
	}

    void game_system::addLevel(const std::string &name, const std::string &nextlevel)
    {
        //��������, ��� ������� � ����� ������ ���
        if (get_level(name) != 0)
        {
            //... �������� � ��� � ������� �� ������� (�� �������� ������ ������)
            return;
        }

        //��������� �������
		Level* pLevel = new Level(name,nextlevel);
		m_listLevels.push_back(pLevel);
    }

    //�������� ��������� �������, ���� �� �� ������ ������� �
    //�������� �� Level: � ������������ ���� ������ ������ �� ����� ������
    void game_system::addLevelTypeToCreate(const std::string &name, const std::string& type_name)
    {
        Level *pLevel = get_level(name);

        //���� ������ ������ ���
        if (!pLevel)
        {
            //... �������� � ��� � ������� �� �������
            return;
        }

        pLevel->callFunction("AddTypeToCreate", type_name);
    }

	game_system::game_system(): m_change_level(false)
	{
		subscribe<events::on_close_game>     (&game_system::onCloseGame);
		subscribe<events::on_complite_level> (&game_system::onCompliteLevel);
		subscribe<events::on_level_set>      (&game_system::onSetLevel);
		core::TheTimer::get().start();
	}

	game_system::~game_system()
	{
		typedef std::list<dynamic_object*> DinamicObjects;
		typedef DinamicObjects::iterator DinamicObjsIter;

		//�������� ��� ������������ �������
		for (DinamicObjsIter it = m_objects.begin();
			it != m_objects.end(); ++it)
		{
			(*it)->unsubscribe();
		}

		m_objects.clear();

		Level* current_level = get_level(m_strCurrentLevel);
		if (0 != current_level)
			current_level->leave();

        while (m_listLevels.begin() != m_listLevels.end())
        {
            delete *m_listLevels.begin();
            m_listLevels.erase(m_listLevels.begin());
        }
	}	
	
	void game_system::onCloseGame(events::on_close_game)
	{
		setCurrentLevel("");
		core::application::get()->close();
	}

	void game_system::onCompliteLevel(events::on_complite_level)
	{
		std::string next_level;
		Level *pLevel = get_level(m_strCurrentLevel);

		if (0 != pLevel)
			next_level = pLevel->get_next_level();

		setCurrentLevel(next_level);
	}

	void game_system::onSetLevel(events::on_level_set event)
	{
		setCurrentLevel(event.get_next_level());
	}

	void game_system::setCurrentLevel(const std::string& next_level)
	{
		m_change_level = true;
		m_next_level = next_level;
	}

	void game_system::update()
	{
		float dt = core::TheTimer::get().getElapsedTime();

		//static_cast<float>(m_timer.elapsed());
		typedef std::list<dynamic_object*> DinamicObjects;
		typedef DinamicObjects::iterator DinamicObjsIter;

		//����������� ��� ������������ �������
		for (DinamicObjsIter it = m_objects.begin();
			it != m_objects.end(); ++it)
		{
			(*it)->update(dt);
		}

		//������ ������� (���� ����)
		if (m_change_level)
		{
			Level* current_level = get_level(m_strCurrentLevel);

			if (0 != current_level)
				current_level->leave();

			m_strCurrentLevel = m_next_level;

			current_level = get_level(m_strCurrentLevel);

			if (0 != current_level)
				current_level->enter();

			m_change_level = false;
		}
	}

	//���������������� ������������ (�.�. � ������� update) ������
	void game_system::register_object(dynamic_object *obj)
	{
#ifdef _DEBUG		
		std::list<dynamic_object*>::iterator i = find
			(
				m_objects.begin(),
				m_objects.end(),
				obj
			);

		//��������� �� ������� �����������		//(����, �������� �������� :))
		if (i != m_objects.end())
			throw std::exception("List of DynamicObjects in game_system corrupted!");

#endif
		m_objects.push_back(obj);
	}

	//����������������� ������������ ������	
	void game_system::unregister_object(dynamic_object *obj)
	{
#ifdef _DEBUG
		std::list<dynamic_object*>::iterator i = find
			(
				m_objects.begin(),
				m_objects.end(),	
				obj
			);

		if (i == m_objects.end())
			throw std::exception("List of DynamicObjects in game_system corrupted!");
#endif
		m_objects.remove(obj);
	}

	Level* game_system::get_level(const std::string& name)
	{
		for(std::list<Level*>::iterator i = m_listLevels.begin(); i != m_listLevels.end(); ++i)
		{
			if ((*i)->getName() == name)
				return (*i);
		}
		return 0;
	}
} //namespace game