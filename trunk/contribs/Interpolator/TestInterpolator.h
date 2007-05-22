//TestInterpolator.h
#pragma once
#include <rgde/input/input.h>
#include <rgde/input/helper.h>
#include <rgde/math/mathTargetCamera.h>
#include <rgde/math/mathSplines.h>

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