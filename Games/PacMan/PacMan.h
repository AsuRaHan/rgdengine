/**--------------------------------------------------------------------------------------

									RGDE Engine

----------------------------------------------------------------------------------------
\author Andrew "Zlobnik" Chouprina, 2005
mail:		dxprg@mail.ru

Created:	15 june 2005
---------------------------------------------------------------------------------------*/
#pragma once

#include "Base.h"



namespace test_PacMan
{

	class CGhost;

	//-----------------------------------------------------------------------------------
	// ����� �������
	class CPacMan : public CBaseObject
	{
		friend struct SPacManHelper;

	public:
		enum eDirection { eUp, eRight, eDown, eLeft	};

		CPacMan(); 

		void update (float dt);

		void eatBonus (CBaseBonus* pBonus);
		void eatGhost (CGhost* pGhost);


	private:
		unsigned	m_nLives;						// ����� ������
		unsigned	m_nScores;						// ����� ��������� �����
		eDirection	m_eDirection;					// ����������� ������� �������
		float		m_fMovingDelta;					// ���������� � ������� ������� ��� ��������


		// ����������, ��������� � �������
		bool		m_isPillActive;					// ��������� �� ������
		unsigned	m_nEatenPerPill;				/* ����� ��������, ��������� �� ����� �������� ������
													(������ �� ����) */
		float		m_fPillTimeLeft;				// �����, ������� ��� ����� ����������� ������
	};

}