#pragma once

#include "rgde/core/Property.h"
#include "rgde/game/LevelObject.h"

namespace game
{
	//������� ����� ������
	class CLevel : public core::CFunctionsOwner
	{
	public:
		CLevel(const std::string& name, const std::string& next_level);
		~CLevel();

		void addTypeToCreate(const std::string& type_name);	//���������� ���� ��� ��������
		void enter();											//������������� ������
		void leave();											//��������������� ������

		//������ ��� ������
		const std::string& getName() const		{return m_strName;}
		//������ ��� ��������� ������
		const std::string& getNextLevel() const {return m_strNextLevel;}

	private:
		std::list<ILevelObject*> m_listLevelObjs; //������ ��������, ������� ������� �������
		std::list<std::string>   m_listTypes;     //���� �������� ������� ���� �������
		std::string              m_strName;       //��� ������
		std::string              m_strNextLevel;  //��� ������, ������� ������ ���� ���������
	};
}