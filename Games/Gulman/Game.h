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
		
		void onEsc();	//����� �� ���������
		void onXAxis(int delta);
		void onYAxis(int delta);
		void onWheelAxis(int delta);

	protected:
		render::PModel			m_spModel;
		render::PFont			m_spFont;
		math::PCamera			m_camera;            //��������� �� ������

		//������ ��� �����
		input::Button       m_cEsc;
		input::RelativeAxis m_cXAxis;
		input::RelativeAxis m_cYAxis;
		input::RelativeAxis m_cZAxis;

		//������ ��� ������
		math::PTargetCamera      m_spTargetCamera;      //���������� ������ "���������� ������"	
	};
}