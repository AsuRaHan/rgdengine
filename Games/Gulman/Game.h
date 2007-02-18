#pragma once

#include <engine.h>

namespace gulman
{
	class Game :  public game::IDynamicObject
	{
	public:
		Game();	
		~Game();

	protected:
		void initInput();
		void initCamera();

		void createModel();

		virtual void update(float dt);
		
		void onEsc(const input::CButtonEvent&);	//����� �� ���������
		void onXAxis(const input::CRelativeAxisEvent &event);
		void onYAxis(const input::CRelativeAxisEvent &event);
		void onWheelAxis(const input::CRelativeAxisEvent &event);

	protected:
		render::PModel			m_spModel;
		render::PFont			m_spFont;
		math::PCamera			m_camera;            //��������� �� ������

		//������ ��� �����
		input::CButtonCommand       m_cEsc;
		input::CRelativeAxisCommand m_cXAxis;
		input::CRelativeAxisCommand m_cYAxis;
		input::CRelativeAxisCommand m_cZAxis;

		//������ ��� ������
		math::PTargetCamera      m_spTargetCamera;      //���������� ������ "���������� ������"	
	};
}