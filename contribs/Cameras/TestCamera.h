//TestCamera.h
#pragma once
#include "math/mathFlyCamera.h"
#include "math/mathTargetCamera.h"
#include "math/mathFirstPersonCamera.h"

class TestCamera: public game::IDynamicObject
{
public:
    TestCamera();
    ~TestCamera();

protected:
    void initInput();
    void initCamera();
    void initLights();

    void update (float dt);

    void onEsc          (const input::CButtonEvent &event);
    void onReset        (const input::CButtonEvent &event);
    void onChangeCamera (const input::CButtonEvent &event);
    void onXAxis        (const input::CRelativeAxisEvent &event);
    void onYAxis        (const input::CRelativeAxisEvent &event);

private:
    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    int m_nCameraType; //����� ������������ ������

    //�������� �����
    input::CButtonCommand       m_cEsc;   //�����
    input::CButtonCommand       m_cTab;   //����������� ������
    input::CButtonCommand       m_cR;     //�������� ��������� � ��������� ���������
    input::CButtonCommand       m_cQ;     //������� ������ �������
    input::CButtonCommand       m_cW;     //������
    input::CButtonCommand       m_cE;     //������� �� �������
    input::CButtonCommand       m_cA;     //����� �����
    input::CButtonCommand       m_cS;     //�����
    input::CButtonCommand       m_cD;     //����� ������
    input::CButtonCommand       m_cF;     //�����
    input::CButtonCommand       m_cC;     //����
    input::CRelativeAxisCommand m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxisCommand m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera         m_spFlyCamera;         //��������� ������
    math::PTargetCamera      m_spTargetCamera;      //���������� ������
    math::PFirstPersonCamera m_spFirstPersonCamera; //fps ������
};