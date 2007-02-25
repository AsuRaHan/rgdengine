//TestCamera.h
#pragma once
#include "input/input.h"
#include "input/helper.h"
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

    void onEsc          ();
    void onWireframe    ();
    void onReset        ();
    void onChangeCamera ();
    void onXAxis        (int dx);
    void onYAxis        (int dy);

private:
    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    int m_nCameraType; //����� ������������ ������

    //�������� �����
    input::CKeyUp        m_cEsc;   //�����
    input::CKeyDown      m_cSpace; //������������ ������ wirframe/solid
    input::CKeyDown      m_cTab;   //����������� ������
    input::CKeyDown      m_cR;     //�������� ��������� � ��������� ���������
    input::CButton       m_cQ;     //������� ������ �������
    input::CButton       m_cW;     //������
    input::CButton       m_cE;     //������� �� �������
    input::CButton       m_cA;     //����� �����
    input::CButton       m_cS;     //�����
    input::CButton       m_cD;     //����� ������
    input::CButton       m_cF;     //�����
    input::CButton       m_cC;     //����
    input::CRelativeAxis m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxis m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera         m_spFlyCamera;         //��������� ������
    math::PTargetCamera      m_spTargetCamera;      //���������� ������
    math::PFirstPersonCamera m_spFirstPersonCamera; //fps ������
};