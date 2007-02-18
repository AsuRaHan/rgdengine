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

    void onEsc        (const input::CButtonEvent &event);
    void onInfo       (const input::CButtonEvent &event);
    void onReset      (const input::CButtonEvent &event);
    void onLoadModel  (const input::CButtonEvent &event);
    void onLoadTrack  (const input::CButtonEvent &event);
    void onSaveTrack  (const input::CButtonEvent &event);
    void onChangeMode (const input::CButtonEvent &event);
    void onPrevKey    (const input::CButtonEvent &event);
    void onNextKey    (const input::CButtonEvent &event);
    void onFaster     (const input::CButtonEvent &event);
    void onSlower     (const input::CButtonEvent &event);
    void onAddKey     (const input::CButtonEvent &event);
    void onDelKey     (const input::CButtonEvent &event);
    void onXAxis      (const input::CRelativeAxisEvent &event);
    void onYAxis      (const input::CRelativeAxisEvent &event);

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
    input::CButtonCommand       m_cEsc;   //�����
    input::CButtonCommand       m_cTab;   //������ / �������� ����������
    input::CButtonCommand       m_c0;     //�������� ��������� � ��������� ���������
    input::CButtonCommand       m_cQ;     //������� ������ �������
    input::CButtonCommand       m_cW;     //������
    input::CButtonCommand       m_cE;     //������� �� �������
    input::CButtonCommand       m_cA;     //����� �����
    input::CButtonCommand       m_cS;     //�����
    input::CButtonCommand       m_cD;     //����� ������
    input::CButtonCommand       m_cF;     //�����
    input::CButtonCommand       m_cC;     //����
    input::CButtonCommand       m_cF1;    //�������� ������
    input::CButtonCommand       m_cF2;    //�������� ����
    input::CButtonCommand       m_cF3;    //��������� ����
    input::CButtonCommand       m_cF4;    //������������ / �������������� �����
    input::CButtonCommand       m_cZ;     //���������� ����
    input::CButtonCommand       m_cX;     //��������� ����
    input::CButtonCommand       m_cO;     //��������� ��������
    input::CButtonCommand       m_cP;     //��������� ��������
    input::CButtonCommand       m_cSpace; //�������� ����
    input::CButtonCommand       m_cDel;   //������� ����
    input::CRelativeAxisCommand m_cXAxis; //�������������� ��� ��������
    input::CRelativeAxisCommand m_cYAxis; //������������ ��� ��������

    //����������� ������
    math::PFlyCamera   m_spFlyCamera;   //��������� ������
    math::PTrackCamera m_spTrackCamera; //������ �������������� �� �������� ����������
};