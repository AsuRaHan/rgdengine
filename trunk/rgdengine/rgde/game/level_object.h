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
	typedef core::factory<game::level_object> LevelObjFactory;

	namespace details
	{
		template <class T>
		class _registrator
		{
		public:
			_registrator(){LevelObjFactory::Instance().register_type<T>();}
		protected:
			static _registrator<T> instance;
		};
	}

#define REGISTER_LEVEL_TYPE(type) details::_registrator<type> details::_registrator<type>::instance;
}