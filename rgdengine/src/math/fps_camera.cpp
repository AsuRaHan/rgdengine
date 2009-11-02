#include "precompiled.h"

#include <rgde/math/fps_camera.h>

namespace math
{

    fps_camera::fps_camera(camera_ptr camera)
    {
        set_camera(camera);

        base::lmsg << "fps_camera::fps_camera()";
        m_vUp       = Vec3f(0.0f, 1.0f, 0.0f);
        m_vEyePt    = Vec3f(0.0f, 0.0f, 0.0f);
        m_vLookatPt = Vec3f(0.0f, 0.0f, 1.0f);
    }

    fps_camera_ptr fps_camera::create(camera_ptr camera)
    {
        return fps_camera_ptr(new fps_camera(camera));
    }

    void fps_camera::set_position(const Vec3f& vUp, const Vec3f& vEyePt, const Vec3f& vLookatPt)
    {
        m_vUp       = vUp;
        m_vEyePt    = vEyePt;
        m_vLookatPt = vLookatPt;
        apply();
    }

    void fps_camera::getPosition(Vec3f& vUp, Vec3f& vEyePt, Vec3f& vLookatPt)
    {
        vUp       = m_vUp;
        vEyePt    = m_vEyePt;
        vLookatPt = m_vLookatPt;
    }

    void fps_camera::goForward(float delta)
    {
		Vec3f vDir = m_vLookatPt-m_vEyePt;
		normalize(vDir);
		vDir*=delta;
		m_vEyePt+=vDir;
		m_vLookatPt+=vDir;
		apply();
    }

    void fps_camera::goLeft(float delta)
    {
		Vec3f vDir = m_vLookatPt-m_vEyePt;
		Vec3f vRight;
		cross(vRight,m_vUp,vDir);
		normalize(vRight);
		vRight*=delta;
		m_vEyePt-=vRight;
		m_vLookatPt-=vRight;
		apply();
    }

    void fps_camera::goUp(float delta)
    {
		Vec3f vDir = m_vUp;
		normalize(vDir);
		vDir*=delta;
		m_vEyePt+=vDir;
		m_vLookatPt+=vDir;
		apply();
    }

    void fps_camera::rotateRight(float angle)
    {
 		Quatf rot;
        Vec3f vAxis = m_vUp;

		normalize(vAxis);
        setRot(rot, AxisAnglef(angle, vAxis));

        xform<float>(m_vLookatPt, rot, m_vLookatPt-m_vEyePt);
        normalize(m_vLookatPt);
        m_vLookatPt += m_vEyePt;

		apply();
    }

    void fps_camera::rotateUp(float angle)
    {
		Quatf rot;
        Vec3f vAxis;
        Vec3f vDir = m_vLookatPt-m_vEyePt;

        //������� � �������� "������ ����������� ����� ��� ����"
        const float fSmallAngle = 0.01f; //�� ��������� ���������� ����������� ������� � ��������� ����� ��� �� ���� ����
        normalize(vDir);
        normalize(m_vUp);
        float fCurrentAngle = Math::aCos(dot(vDir,m_vUp));
        if (fCurrentAngle + angle <= fSmallAngle)
            angle = -fCurrentAngle + fSmallAngle;
        if (fCurrentAngle + angle >= Math::PI - fSmallAngle)
            angle = Math::PI - fCurrentAngle - fSmallAngle;

        cross(vAxis,m_vUp,vDir);
		normalize(vAxis);

        if (length(vAxis) < 0.1f) return; //����! ����������� ������� ������� � ������������ �����

        setRot(rot, AxisAnglef(angle, vAxis));

        xform<float>(m_vLookatPt, rot, m_vLookatPt-m_vEyePt);
        normalize(m_vLookatPt);
        m_vLookatPt += m_vEyePt;

		apply();
    }

    void fps_camera::activate()
    {
        apply();
    }

    void fps_camera::apply()
    {
        if (m_pCamera)
        {
            try{
                m_pCamera->lookAt(m_vEyePt,m_vLookatPt,m_vUp);
                m_pCamera->activate();
            }
            catch(...){}
        }
    }

} //namespace math