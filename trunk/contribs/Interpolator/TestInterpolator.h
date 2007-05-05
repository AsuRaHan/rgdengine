//TestInterpolator.h
#pragma once
#include "input/input.h"
#include "input/helper.h"
#include "math/mathTargetCamera.h"
#include "math/mathSplines.h"

class TestInterpolator: public game::IDynamicObject
{
public:
    TestInterpolator();
    ~TestInterpolator();

protected:
    void initInput();
    void initCamera();
    void initLights();

    void update (float dt);

    void onEsc   ();
    void onReset ();
    void onXAxis (int dx);
    void onYAxis (int dy);

private:
	std::vector<math::Vec3f> m_lines;

    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    math::Vec3fCatmulRomDistSpline m_spline; //������

    //�������� �����
    input::CKeyUp        m_cEsc;   //�����
    input::CKeyDown      m_cR;     //�������� ��������� � ��������� ���������
    input::CButton       m_cQ;     //������� ������ �������
    input::CButton       m_cE;     //������� �� �������
    input::CButton       m_cW;     //����������
    input::CButton       m_cS;     //�������
    input::CRelativeAxis m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxis m_cYAxis; //������������ ��� ��������

    //���������� ������
    math::PTargetCamera m_spTargetCamera; //���������� ������
};