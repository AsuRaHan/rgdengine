#pragma once

#include <rgde/math/camera_controller.h>

namespace math
{

    typedef boost::shared_ptr<class CTargetCamera> PTargetCamera;

    //���������� ������ ��� "���������� ������"
    class CTargetCamera: public BaseCameraController
    {
        CTargetCamera(PCamera pCamera);

    public:
        static PTargetCamera Create(PCamera pCamera);

        //���������
        void setPosition(const Vec3f& vUp, const Vec3f& vEyePt, const Vec3f& vLookatPt);
        void getPosition(Vec3f& vUp, Vec3f& vEyePt, Vec3f& vLookatPt);

        //��������
        void goForward(float delta);
        void goBackward(float delta) {goForward(-delta);}

        //��������
        void rotateRight(float angle);
        void rotateLeft(float angle) {rotateRight(-angle);}
        void rotateUp(float angle);
        void rotateDown(float angle) {rotateUp(-angle);}

	    //������
        void rotateCW(float);
        void rotateCCW(float angle) {rotateCW(-angle);}

        void activate();

    private:
        void apply();
        void doOrthoNormal();

        Vec3f m_vUp;
        Vec3f m_vEyePt;
        Vec3f m_vLookatPt;
    };

} //namespace math