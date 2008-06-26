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
		    Vec3f m_vUp;
		    Vec3f m_vEyePt;
		    Vec3f m_vLookatPt;
            float m_fSpeed;
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
        Vec3fCatmulRomSpline     m_splineUp;
        Vec3fCatmulRomSpline     m_splineEyePt;
        Vec3fCatmulRomSpline     m_splineLookatPt;
        FloatCatmulRomSpline     m_splineSpeed;
        FloatLinearInterpolatorf m_time2parameter;

        CTrack(const CTrack&);
        CTrack& operator=(const CTrack&);
    };
}