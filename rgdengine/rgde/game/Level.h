#pragma once

#include "rgde/core/property.h"
#include "rgde/game/level_object.h"

namespace game
{
	//������� ����� ������
	class Level : public core::FunctionsOwner
	{
	public:
		Level(const std::string& name, const std::string& next_level);
		~Level();

		void addTypeToCreate(const std::string& type_name);	//���������� ���� ��� ��������
		void enter();											//������������� ������
		void leave();											//��������������� ������

		//������ ��� ������
		const std::string& getName() const		{return m_name;}
		//������ ��� ��������� ������
		const std::string& getNextLevel() const {return m_strNextLevel;}

	private:
		std::list<ILevelObject*> m_listLevelObjs; //������ ��������, ������� ������� �������
		std::list<std::string>   m_listTypes;     //���� �������� ������� ���� �������
		std::string              m_name;       //��� ������
		std::string              m_strNextLevel;  //��� ������, ������� ������ ���� ���������
	};
}