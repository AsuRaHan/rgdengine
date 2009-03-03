#pragma once

#include "rgde/core/factory.h"

namespace game
{
	//������� ������ ��� ���� ��������, ������� ������� �������
	//(����� ���� �����, ���� ���� ����� ����������� ����� ����������
	//� ����� ��������)
	class level_object
	{
	public:
		virtual ~level_object(){}
	};

	//������� ��������, ������� ����� ��������� ������
	typedef factory::TFactory<game::level_object> LevelObjFactory;

	template <class T>
	class _registrator
	{
	public:
		_registrator(){LevelObjFactory::Instance().RegisterType<T>();}
	protected:
		static _registrator<T> instance;
	};

	#define REGISTER_LEVEL_TYPE(type) _registrator<type> _registrator<type>::instance;
}