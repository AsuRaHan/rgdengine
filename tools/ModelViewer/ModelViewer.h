#pragma once
#include "engine.h"
#include "utils.h"

class ModelViewer: public game::IDynamicObject
{
public:
    ModelViewer();	
   ~ModelViewer();

protected:
	void initInput();
	void initCamera();

	void createModel(const std::string& strFileName);
	void createLights();

	virtual void update(float dt);
	
	void onEsc();	//����� �� ���������
	void onO();	//open model
	void onL();
	void onK();
	void onB();
	void onG();
	void onW();
	void onXAxis(int dx);
	void onYAxis(int dy);
	void onWheelAxis(int dz);

protected:
	render::PModel m_spModel;
	render::PFont  m_spFont;
	math::PCamera  m_camera; //��������� �� ������

	bool m_bRenderGrid;

	//������ ��� �����
	input::CKeyDown      m_cEsc;
	input::CKeyDown      m_cO;
	input::CKeyDown      m_cL;
	input::CKeyDown      m_cK;
	input::CKeyDown      m_cB;
	input::CKeyDown      m_cG;
	input::CKeyDown      m_cW;
    input::CButton       m_cMouseLeft;
    input::CButton       m_cMouseRight;
	input::CRelativeAxis m_cXAxis;
	input::CRelativeAxis m_cYAxis;
	input::CRelativeAxis m_cZAxis;

	//������ ��� ������
	math::PTargetCamera  m_spTargetCamera; //���������� ������ "���������� ������"	
};