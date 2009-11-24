//track.h
#pragma once

#include "splines.h"

namespace math
{
    //����
    class CTrack
    {
    public:
        CTrack() {}

        //���� �����
        struct Key
        {
		    vec3f m_up;
		    vec3f m_eye_pos;
		    vec3f m_lookat_pt;
            float m_speed;
        };

        //������� ������ � ������� �����
        typedef std::list<Key> List;
        typedef List::iterator iterator;
        typedef List::const_iterator const_iterator;
        List m_values;

        //�������/�������� ��������� �� ������� ������
        void apply();
        void undo();

        //����������/�������� �����
		void load(const std::string& strTrackName);
		void save(const std::string& strTrackName);

        //��������� ����� �����
        float getTotalTime();
        Key getKey(float t);

    private:
        catm_rom_spline_v3f     m_splineUp;
        catm_rom_spline_v3f     m_splineEyePt;
        catm_rom_spline_v3f     m_splineLookatPt;
        catm_rom_splinef     m_splineSpeed;
        FloatLinearInterpolatorf m_time2parameter;

        CTrack(const CTrack&);
        CTrack& operator=(const CTrack&);
    };
}