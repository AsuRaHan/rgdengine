//TestTrack.h
#pragma once
#include "input/input.h"
#include "input/helper.h"
#include "math/mathTargetCamera.h"
#include "math/mathSplines.h"
#include "math/mathTrack.h"

class TestTrack: public game::IDynamicObject
{
public:
    TestTrack();
    ~TestTrack();

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
    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    math::CTrack m_track; //����

    //�������� �����
    input::KeyUp        m_cEsc;   //�����
    input::KeyDown      m_cR;     //�������� ��������� � ��������� ���������
    input::Button       m_cQ;     //������� ������ �������
    input::Button       m_cE;     //������� �� �������
    input::Button       m_cW;     //����������
    input::Button       m_cS;     //�������
    input::RelativeAxis m_cXAxis; //�������������� ��� ��������
    input::RelativeAxis m_cYAxis; //������������ ��� ��������

    //���������� ������
    math::PTargetCamera m_spTargetCamera; //���������� ������
};