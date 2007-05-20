#include "precompiled.h"

#include "math/mathCamera.h"

//Neonic: octree
#include "scene/scene.h"

namespace math
{
	const Matrix44f  CBaseCamera::getViewMatrix()	const 
	{
		Matrix44f m = CFrame::getFullTransform();
		math::invert(m);
		return m;		
	}

	void CBaseCamera::setProjection(float fFovy, float fAspect, float zn, float zf)
	{
		float hfov = fFovy/2;
		float yScale = ::cos(hfov)/::sin(hfov);
		float xScale = yScale / fAspect;

		m_ProjMatrix.set(xScale,	0,			0,			0,
							0,		yScale,		0,			0, 
							0,		0,		zf/(zf-zn),		1,
							0,		0,		-zn*zf/(zf-zn), 0);

		gmtl::transpose(m_ProjMatrix);

		//Neonic: octree
		setRadius(zn);
	}

	void CBaseCamera::activate()
	{
		m_frustum.CalculateFrustum(*this);

		//Neonic: octree. ���� ��� ��������� ���������� ��������� ������ � ������,
		// �.�. ���������� �� ���������� �������.
		if(getRoot())
		{
			move(getPosition());
		}
		else
		{
			// Neonic: next code appear repeatedly in sequence, cause camera (in tree) activation not instant
			makeSphere(getPosition(),getRadius());
			// usually camera is moving (dynamic) object
			makeDynamic();
			scene::TheScene::Get().inject(this);
		}
	}
}