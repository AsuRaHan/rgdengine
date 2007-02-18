#pragma once

#include "Point.h"

namespace lines_test
{

	class CTriangle
	{
	protected:
		typedef std::vector<CPoint> tPoints;
		typedef tPoints::iterator tPointsIter;

	public:
		CTriangle();

		void reset();
		void update();
		void render();

	protected:
		tPoints m_vPoints;						///> �����
		math::Color m_Color;				///> ����
		math::Vec2f m_fCColorRange;				///> ������� ��������� ����������� �����
		float m_fCColorDelta;					///> ���������� ����������� �����
	};
}