//splines.h
#pragma once

//������� �������-���� � ��������������� �� ���������
#include "catmulrom.h"
#include "catmulrom_dist.h"

namespace math
{

    //������� �������-���� � ��������������� �� ���������
    typedef TCatmulRomSpline<double>      DoubleCatmulRomSpline;
    typedef TCatmulRomSpline<float>       FloatCatmulRomSpline;
    typedef TCatmulRomSpline<int>         IntCatmulRomSpline;

    typedef TCatmulRomSpline<math::Vec2f> Vec2fCatmulRomSpline;
    typedef TCatmulRomSpline<math::Vec3f> Vec3fCatmulRomSpline;
    typedef TCatmulRomSpline<math::Vec4f> Vec4fCatmulRomSpline;

    typedef TCatmulRomSpline<math::Quatf> QuatfCatmulRomSpline;

    //�������� ��� ���������� ���������� ����� ���������� ������
    //������ ������� (��� ������������������ ����� ������)

    //��� ���� float
    struct FloatDistance
    {
        float operator()(const float &k1, const float &k2)
        {
            return fabs(k2-k1);
        }
    };

    //��� ���� Vec3f
    struct Vec3fDistance
    {
        float operator()(const Vec3f &k1, const Vec3f &k2)
        {
            return length<float,3>(k2-k1);
        }
    };

    //������� �������-���� � ��������������� ������� �������
    typedef TCatmulRomDistSpline<float, FloatDistance> FloatCatmulRomDistSpline;
    typedef TCatmulRomDistSpline<Vec3f, Vec3fDistance> Vec3fCatmulRomDistSpline;

} //namespace math