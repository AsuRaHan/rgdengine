#pragma once

#include <rgde/math/mathTrack.h>
#include <rgde/math/mathFlyCamera.h>
#include <rgde/math/mathTrackCamera.h>

#include <rgde/input/input.h>

class TrackEditor: public game::IDynamicObject
{
public:
    TrackEditor();
    ~TrackEditor();

protected:
    void initInput();
    void initCamera();
    void initLights();
    void initEditor();

    void update (float dt);

    void onEsc        ();
    void onInfo       ();
    void onReset      ();
    void onLoadModel  ();
    void onLoadTrack  ();
    void onSaveTrack  ();
    void onChangeMode ();
    void onPrevKey    ();
    void onNextKey    ();
    void onFaster     ();
    void onSlower     ();
    void onAddKey     ();
    void onDelKey     ();
    void onXAxis      (int dx);
    void onYAxis      (int dy);

private:
    render::PModel m_spModel;  //������
    render::PFont  m_spFont;   //�����
    math::PCamera  m_spCamera; //������

    bool m_bPlay;              //����� ������������
    bool m_bInfo;              //����� ����������� ����������
    math::CTrack::iterator i; //��������, ����������� �� ������� ���� �����

    //->
    math::Vec3fCatmulRomSpline m_cSpline;
    void moveTrack2Spline();
    //-<

    //�������� �����
    input::KeyDown      m_cEsc;   //�����
    input::KeyDown      m_cTab;   //������ / �������� ����������
    input::KeyDown      m_c0;     //�������� ��������� � ��������� ���������
    input::Button       m_cQ;     //������� ������ �������
    input::Button       m_cW;     //������
    input::Button       m_cE;     //������� �� �������
    input::Button       m_cA;     //����� �����
    input::Button       m_cS;     //�����
    input::Button       m_cD;     //����� ������
    input::Button       m_cF;     //�����
    input::Button       m_cC;     //����
    input::KeyDown      m_cF1;    //�������� ������
    input::KeyDown      m_cF2;    //�������� ����
    input::KeyDown      m_cF3;    //��������� ����
    input::KeyDown      m_cF4;    //������������ / �������������� �����
    input::KeyDown      m_cZ;     //���������� ����
    input::KeyDown      m_cX;     //��������� ����
    input::KeyDown      m_cO;     //��������� ��������
    input::KeyDown      m_cP;     //��������� ��������
    input::KeyDown      m_cSpace; //�������� ����
    input::KeyDown      m_cDel;   //������� ����
    input::RelativeAxis m_cXAxis; //�������������� ��� ��������
    input::RelativeAxis m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera   m_spFlyCamera;   //��������� ������
    math::PTrackCamera m_spTrackCamera; //������ �������������� �� �������� ����������
};