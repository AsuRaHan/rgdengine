//TestInterpolator.h
#pragma once
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

    void onEsc   (const input::CButtonEvent &event);
    void onReset (const input::CButtonEvent &event);
    void onXAxis (const input::CRelativeAxisEvent &event);
    void onYAxis (const input::CRelativeAxisEvent &event);

private:
    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    math::Vec3fCatmulRomDistSpline m_spline; //������

    //�������� �����
    input::CButtonCommand       m_cEsc;   //�����
    input::CButtonCommand       m_cR;     //�������� ��������� � ��������� ���������
    input::CButtonCommand       m_cQ;     //������� ������ �������
    input::CButtonCommand       m_cE;     //������� �� �������
    input::CButtonCommand       m_cW;     //����������
    input::CButtonCommand       m_cS;     //�������
    input::CRelativeAxisCommand m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxisCommand m_cYAxis; //������������ ��� ��������

    //���������� ������
    math::PTargetCamera m_spTargetCamera; //���������� ������
};