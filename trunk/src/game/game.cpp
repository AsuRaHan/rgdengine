#include "precompiled.h"

#include "game/game.h"

#include "core/Timer.h"
#include "core/application.h"

namespace game
{
	//�������������
	void CGame::init(const std::string& strXmlGameConfig)
	{
		//return;

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
				CLevel* pLevel = new game::CLevel(name,nextlevel);
				m_listLevels.push_back(pLevel);

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

	CGame::CGame(): m_bChangeLevel(false)
	{
		subscribe(this, &CGame::onCloseGame);
		subscribe(this, &CGame::onCompliteLevel);
		subscribe(this, &CGame::onSetLevel);
		core::TheTimer::Get().start();
	}

	CGame::~CGame()
	{
		typedef std::list<IDynamicObject*> DinamicObjects;
		typedef DinamicObjects::iterator DinamicObjsIter;

		//�������� ��� ������������ �������
		for (DinamicObjsIter it = m_listDynamicObjects.begin();
			it != m_listDynamicObjects.end(); ++it)
		{
			(*it)->unsubscribe();
		}

		m_listDynamicObjects.clear();

		CLevel* pCurrentLevel = getLevel(m_strCurrentLevel);
		if (0 != pCurrentLevel)
			pCurrentLevel->leave();
	}	
	
	void CGame::onCloseGame(CCloseGameEvent)
	{
		setCurrentLevel("");
		core::IApplication::Get()->close();
	}

	void CGame::onCompliteLevel(CCompliteLevelEvent)
	{
		std::string strNextLevel;
		CLevel *pLevel = getLevel(m_strCurrentLevel);

		if (0 != pLevel)
			strNextLevel = pLevel->getNextLevel();

		setCurrentLevel(strNextLevel);
	}

	void CGame::onSetLevel(CSetLevelEvent event)
	{
		setCurrentLevel(event.getNextLevel());
	}

	void CGame::setCurrentLevel(const std::string& strNextLevel)
	{
		m_bChangeLevel = true;
		m_strNextLevel = strNextLevel;
	}

	void CGame::update()
	{
		float dt = core::TheTimer::Get().getElapsedTime();

		//static_cast<float>(m_timer.elapsed());
		typedef std::list<IDynamicObject*> DinamicObjects;
		typedef DinamicObjects::iterator DinamicObjsIter;

		//����������� ��� ������������ �������
		for (DinamicObjsIter it = m_listDynamicObjects.begin();
			it != m_listDynamicObjects.end(); ++it)
		{
			(*it)->update(dt);
		}

		//������ ������� (���� ����)
		if (m_bChangeLevel)
		{
			CLevel* pCurrentLevel = getLevel(m_strCurrentLevel);

			if (0 != pCurrentLevel)
				pCurrentLevel->leave();

			m_strCurrentLevel = m_strNextLevel;

			pCurrentLevel = getLevel(m_strCurrentLevel);

			if (0 != pCurrentLevel)
				pCurrentLevel->enter();

			m_bChangeLevel = false;
		}
	}

	//���������������� ������������ (�.�. � ������� update) ������
	void CGame::registerDynamicObject(IDynamicObject *pObject)
	{
#ifdef _DEBUG		
		std::list<IDynamicObject*>::iterator i = find
			(
				m_listDynamicObjects.begin(),
				m_listDynamicObjects.end(),
				pObject
			);

		//��������� �� ������� �����������		//(����, �������� �������� :))
		if (i != m_listDynamicObjects.end())
			throw std::exception("List of DynamicObjects in CGame corrupted!");

#endif
		m_listDynamicObjects.push_back(pObject);
	}

	//����������������� ������������ ������	
	void CGame::unregisterDynamicObject(IDynamicObject *pObject)
	{
#ifdef _DEBUG
		std::list<IDynamicObject*>::iterator i = find
			(
				m_listDynamicObjects.begin(),
				m_listDynamicObjects.end(),	
				pObject
			);

		if (i == m_listDynamicObjects.end())
			throw std::exception("List of DynamicObjects in CGame corrupted!");
#endif
		m_listDynamicObjects.remove(pObject);
	}


	void CGame::addLevel(CLevel* pLevel)
	{
		m_listLevels.push_back(pLevel);
	}

	CLevel* CGame::getLevel(std::string strName)
	{
		for(std::list<CLevel*>::iterator i = m_listLevels.begin(); i != m_listLevels.end(); ++i)
		{
			if ((*i)->getName() == strName)
				return (*i);
		}
		return 0;
	}
} //namespace game