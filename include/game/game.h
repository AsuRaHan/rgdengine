#pragma once

#include "event/event.h"

#include "game/Level.h"
#include "game/DynamicObject.h"
#include "game/LevelObject.h"

#include "base/singelton.h"

namespace game
{
	//����� "��������� ����"
	class CCloseGameEvent
	{
	};

	//����� "��������� ������� �������"
	class CCompliteLevelEvent
	{
	};

	//����� "������ ����� �������"
	class CSetLevelEvent
	{
	public:
		CSetLevelEvent(const std::string& strNextLevel)
			: m_strNextLevel(strNextLevel)
		{
		}

		const std::string& getNextLevel()  const { return m_strNextLevel; }

	private:
		std::string m_strNextLevel;
	};

	//������� ����� ����
	class CGame: public event::CListener
	{
	public:
		void init(const std::string&);
		
		//������ ��� �������� ������
		std::string getCurrentLevel() const {return m_strCurrentLevel;} 

		//������ ������� ������� (�� �����)
		void setCurrentLevel(const std::string&);   

		void update();

		void onCloseGame(CCloseGameEvent);
		void onCompliteLevel(CCompliteLevelEvent);
		void onSetLevel(CSetLevelEvent);

		void registerDynamicObject(IDynamicObject*);   //���������������� ������������ (�.�. � ������� update) ������
		void unregisterDynamicObject(IDynamicObject*); //����������������� ������������ ������

	private:
		void addLevel(CLevel*);
		CLevel* getLevel(std::string);
	
	protected:
		CGame();
		~CGame();

	private:
		std::string                m_strCurrentLevel;    //��� �������� ������
		std::string                m_strNextLevel;       //��� ���������� ������
		std::list<CLevel*>         m_listLevels;         //������ �������
		std::list<IDynamicObject*> m_listDynamicObjects; //������ ������������ ��������
		bool                       m_bChangeLevel;
	};

	typedef base::TSingelton<CGame>	TheGame;
}