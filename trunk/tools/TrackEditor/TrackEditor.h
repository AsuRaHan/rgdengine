//TrackEditor.h
#pragma once
#include "math/mathTrack.h"
#include "math/mathFlyCamera.h"
#include "math/mathTrackCamera.h"

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
    input::CKeyDown      m_cEsc;   //�����
    input::CKeyDown      m_cTab;   //������ / �������� ����������
    input::CKeyDown      m_c0;     //�������� ��������� � ��������� ���������
    input::CButton       m_cQ;     //������� ������ �������
    input::CButton       m_cW;     //������
    input::CButton       m_cE;     //������� �� �������
    input::CButton       m_cA;     //����� �����
    input::CButton       m_cS;     //�����
    input::CButton       m_cD;     //����� ������
    input::CButton       m_cF;     //�����
    input::CButton       m_cC;     //����
    input::CKeyDown      m_cF1;    //�������� ������
    input::CKeyDown      m_cF2;    //�������� ����
    input::CKeyDown      m_cF3;    //��������� ����
    input::CKeyDown      m_cF4;    //������������ / �������������� �����
    input::CKeyDown      m_cZ;     //���������� ����
    input::CKeyDown      m_cX;     //��������� ����
    input::CKeyDown      m_cO;     //��������� ��������
    input::CKeyDown      m_cP;     //��������� ��������
    input::CKeyDown      m_cSpace; //�������� ����
    input::CKeyDown      m_cDel;   //������� ����
    input::CRelativeAxis m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxis m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera   m_spFlyCamera;   //��������� ������
    math::PTrackCamera m_spTrackCamera; //������ �������������� �� �������� ����������
};