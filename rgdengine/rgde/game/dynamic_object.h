#pragma once

namespace game
{
	//������������ ������ ��� ����
	//(� ���� ���������� ����� update �� GameTask)
	class IDynamicObject
	{
		friend class CGame;
	public:
		IDynamicObject();
		virtual ~IDynamicObject();
		virtual void update(float dt)=0;

	private:
		void unsubscribe() {m_bIsSubscribed = false;}

	private:
		bool m_bIsSubscribed;
	};
}