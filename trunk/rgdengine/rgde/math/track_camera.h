//track_camera.h
#pragma once

#include "camera_controller.h"
#include "track.h"

namespace math
{
    typedef boost::shared_ptr<class CTrackCamera> PTrackCamera;

    //���������� ������ ��� "������ �������� �� ��������� ����������"
    class CTrackCamera: public BaseCameraController
    {
        CTrackCamera(camera_ptr pCamera);

    public:
        static PTrackCamera create(camera_ptr pCamera);

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