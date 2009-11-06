#include "precompiled.h"

#include <rgde/math/track_camera.h>

namespace math
{

    path_camera::path_camera(camera_ptr camera): m_fPosition(0)
    {
        set_camera(camera);
        base::lmsg << "path_camera::path_camera()";
    }

    path_camera_ptr path_camera::create(camera_ptr camera)
    {
        return path_camera_ptr(new path_camera(camera));
    }

    void path_camera::move_to(float position)
    {
        m_fPosition = position;
        apply();
    }

    void path_camera::move_forward(float delta)
    {
        move_to(m_fPosition+delta);
    }

    void path_camera::activate()
    {
        apply();
    }

    void path_camera::apply()
    {
        if (m_fPosition < 0)
            m_fPosition = 0;
        if (m_fPosition > m_path.getTotalTime())
            m_fPosition = m_path.getTotalTime();

        if (m_camera)
        {
            try{
                CTrack::Key key = m_path.getKey(m_fPosition);
                //todo: �������� ����������� ���������������� �������� [Dub]
                m_camera->look_at(key.m_eye_pos, key.m_lookat_pt, key.m_up);
                m_camera->activate();
            }
            catch(...){}
        }
    }

}