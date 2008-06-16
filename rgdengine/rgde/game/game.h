#pragma once

#include "rgde/event/events.h"

#include "rgde/game/Level.h"
#include "rgde/game/DynamicObject.h"
#include "rgde/game/LevelObject.h"

#include "rgde/base/singelton.h"

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
	class CGame: public event::Listener
	{
	public:
        //������������� �� xml �����
		void init(const std::string&);

        //��� ������������ �������� ������� ����
        void addLevel(const std::string &name, const std::string &nextlevel);
        void addLevelTypeToCreate(const std::string &name, const std::string& type_name);

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
		Level* getLevel(std::string);
	
	protected:
		CGame();
		~CGame();

	private:
		std::string                m_strCurrentLevel;    //��� �������� ������
		std::string                m_strNextLevel;       //��� ���������� ������
		std::list<Level*>         m_listLevels;         //������ �������
		std::list<IDynamicObject*> m_listDynamicObjects; //������ ������������ ��������
		bool                       m_bChangeLevel;
	};

	typedef base::TSingelton<CGame>	TheGame;
}