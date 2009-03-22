#pragma once

#include "rgde/event/events.h"

#include "rgde/game/level.h"
#include "rgde/game/dynamic_object.h"
#include "rgde/game/level_object.h"

#include "rgde/base/singelton.h"

namespace game
{
	namespace events
	{
		class on_close_game_event
		{
		};

		class on_complite_level_event
		{
		};

		class on_level_set_event
		{
		public:
			on_level_set_event(const std::string& next_level)
				: m_next_level(next_level)
			{
			}

			const std::string& get_next_level()  const { return m_next_level; }

		private:
			std::string m_next_level;
		};
	}


	class game_system: public event::listener
	{
	public:
        //������������� �� xml �����
		void init(const std::string&); 

        //��� ������������ �������� ������� ����
        void addLevel(const std::string &name, const std::string &nextlevel);
        void addLevelTypeToCreate(const std::string &name, const std::string& type_name);

		//������ ��� �������� ������
		const std::string& getCurrentLevel() const {return m_strCurrentLevel;} 

		//������ ������� ������� (�� �����)
		void setCurrentLevel(const std::string&);   

		void update();

		void onCloseGame(events::on_close_game_event);
		void onCompliteLevel(events::on_complite_level_event);
		void onSetLevel(events::on_level_set_event);

		void register_object(dynamic_object*);   //���������������� ������������ (�.�. � ������� update) ������
		void unregister_object(dynamic_object*); //����������������� ������������ ������

	private:
		Level* get_level(const std::string& level_name);
	
	protected:
		game_system();
		~game_system();

	private:
		std::string                m_strCurrentLevel;    //��� �������� ������
		std::string                m_next_level;       //��� ���������� ������
		std::list<Level*>         m_listLevels;         //������ �������
		std::list<dynamic_object*> m_objects; //������ ������������ ��������
		bool                       m_change_level;
	};

	typedef base::singelton<game_system>	TheGame;
}