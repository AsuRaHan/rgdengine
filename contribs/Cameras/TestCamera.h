#pragma once

#include <rgde/input/input.h>
#include <rgde/input/helper.h>

#include <rgde/math/mathFlyCamera.h>
#include <rgde/math/mathTargetCamera.h>
#include <rgde/math/mathFirstPersonCamera.h>

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
    input::KeyUp        m_cEsc;   //�����
    input::KeyDown      m_cSpace; //������������ ������ wirframe/solid
    input::KeyDown      m_cTab;   //����������� ������
    input::KeyDown      m_cR;     //�������� ��������� � ��������� ���������
    input::Button       m_cQ;     //������� ������ �������
    input::Button       m_cW;     //������
    input::Button       m_cE;     //������� �� �������
    input::Button       m_cA;     //����� �����
    input::Button       m_cS;     //�����
    input::Button       m_cD;     //����� ������
    input::Button       m_cF;     //�����
    input::Button       m_cC;     //����
    input::RelativeAxis m_cXAxis; //�������������� ��� ��������
    input::RelativeAxis m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera         m_spFlyCamera;         //��������� ������
    math::PTargetCamera      m_spTargetCamera;      //���������� ������
    math::PFirstPersonCamera m_spFirstPersonCamera; //fps ������
};