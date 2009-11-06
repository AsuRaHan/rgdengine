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

    typedef TCatmulRomSpline<math::vec2f> Vec2fCatmulRomSpline;
    typedef TCatmulRomSpline<math::vec3f> Vec3fCatmulRomSpline;
    typedef TCatmulRomSpline<math::vec4f> Vec4fCatmulRomSpline;

    typedef TCatmulRomSpline<math::quatf> QuatfCatmulRomSpline;

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

    //��� ���� vec3f
    struct Vec3fDistance
    {
        float operator()(const vec3f &k1, const vec3f &k2)
        {
            return length<float,3>(k2-k1);
        }
    };

    //������� �������-���� � ��������������� ������� �������
    typedef TCatmulRomDistSpline<float, FloatDistance> FloatCatmulRomDistSpline;
    typedef TCatmulRomDistSpline<vec3f, Vec3fDistance> Vec3fCatmulRomDistSpline;

} //namespace math