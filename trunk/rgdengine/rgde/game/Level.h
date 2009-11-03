#pragma once

#include "rgde/core/property.h"
#include "rgde/game/level_object.h"

namespace game
{
	//������� ����� ������
	class level : public core::functions_owner
	{
	public:
		level(const std::string& name, const std::string& next_level);
		~level();

		void addTypeToCreate(const std::string& type_name);	//���������� ���� ��� ��������
		void enter();											//������������� ������
		void leave();											//��������������� ������

		//������ ��� ������
		const std::string& get_name() const		{return m_name;}
		//������ ��� ��������� ������
		const std::string& get_next_level() const {return m_next_level_name;}

	private:
		std::list<level_object*> m_listLevelObjs; //������ ��������, ������� ������� �������
		std::list<std::string>   m_listTypes;     //���� �������� ������� ���� �������
		std::string              m_name;       //��� ������
		std::string              m_next_level_name;  //��� ������, ������� ������ ���� ���������
	};
}