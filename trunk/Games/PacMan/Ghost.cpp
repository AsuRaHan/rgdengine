/**--------------------------------------------------------------------------------------

									RGDE Engine

----------------------------------------------------------------------------------------
\author Andrew "Zlobnik" Chouprina, 2005
mail:		dxprg@mail.ru

Created:	15 june 2005
---------------------------------------------------------------------------------------*/
#include "precomp.h"
#include "Ghost.h"



namespace test_PacMan
{

	//-----------------------------------------------------------------------------------
	CGhost::CGhost()
	{
		m_eBaseType = eEnemy;
		m_eType = eGhost;
	}

	//-----------------------------------------------------------------------------------
	CGhost::update (float dt)
	{
		// TODO: ��������
		if (m_bReachedTargetPos)
			math::Vec2f vTargetPos = /*TODO: ����� ����� ������� �������*/;

		// TODO: ��������
		m_vPos += m_vMovingDelta;

		if (g_Scene.getObject (ePacManBaseType, m_vPos))
			// TODO: ����� onPacManEaten
	}

}