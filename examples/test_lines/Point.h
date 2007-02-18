#pragma once

namespace lines_test
{

	class CPoint
	{
	public:
		CPoint();

		void reset();
		void update();

		inline math::Vec3f& getPos() { return m_vPos; }

	protected:
		math::Vec3f m_vPos;							///> �������
		math::Vec3f m_vVel;							///> ��������
	};
}