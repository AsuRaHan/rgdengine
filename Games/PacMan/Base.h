/**--------------------------------------------------------------------------------------

									RGDE Engine

----------------------------------------------------------------------------------------
\author Andrew "Zlobnik" Chouprina, 2005
mail:		dxprg@mail.ru

Created:	15 june 2005
---------------------------------------------------------------------------------------*/
#pragma once

#include "render/renderSprites.h"
#include "render/renderTexture.h"



namespace test_PacMan
{
	class CTypeInfo;

	//-----------------------------------------------------------------------------------
	// ����� �������� �������� �������
	class CBaseObject
	{
	public:
		// ������������ ������� �����
		enum eBaseType
		{
			eBaseTypeNotSet,
			ePacManBaseType,
			eBonus,
			eEnemy,
			eObstacle
		};

		// ������������ �����
		enum eType
		{
			eTypeNotSet,
			ePacMan,
			eGhost,
			eDot,
			ePowerPill,
			eWall
		};

		CBaseObject (const std::string& strTexName);

		virtual void render() {}
		virtual void update (float dt) {}


		inline eType getType() { return m_eType; }
		inline eBaseType getBaseType() { return m_eBaseType; }

		inline static math::Vec2f GetSize() { return m_vSize; }

		inline void setPos (const math::Vec2f& pos) { m_vPos = pos; m_pSprite->pos = pos; }
		inline math::Vec2f& getPos() { return m_vPos; }


	protected:
		math::Vec2f		m_vPos;						// �������
		static math::Vec2f	m_vSize;				// ������ (� ���� �������� ��������)
		eBaseType		m_eBaseType;				// ������� ��� �������
		eType			m_eType;					// ��� �������
		CTypeInfo*		m_pTypeInfo;				// ���� �� ���� �������� ������� ����

		// ���� ��� �������
		render::SSprite*	m_pSprite;				// ������
		render::CTexture*	m_pTexture;				// ��������
	};


	//-----------------------------------------------------------------------------------
	// ����� �������� ������
	class CBaseBonus : public CBaseObject
	{
	protected:
		unsigned	m_nScores;						// ����� ����� �� �������� ������
	};
}