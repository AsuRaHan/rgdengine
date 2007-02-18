//mathTrackCamera.h
#pragma once

#include "mathCameraController.h"
#include "mathTrack.h"

namespace math
{
    typedef boost::shared_ptr<class CTrackCamera> PTrackCamera;

    //���������� ������ ��� "������ �������� �� ��������� ����������"
    class CTrackCamera: public BaseCameraController
    {
        CTrackCamera(PCamera pCamera);

    public:
        static PTrackCamera Create(PCamera pCamera);

        CTrack m_cTrack;

        //����������
        void  goTo(float position);
        void  goForward(float delta);
        void  goBackward(float delta) {goForward(-delta);}
        float getPosition() {return m_fPosition;}

        void activate();

    private:
        void apply();

        float m_fPosition;
    };
}