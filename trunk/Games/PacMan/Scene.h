/**--------------------------------------------------------------------------------------

									RGDE Engine

----------------------------------------------------------------------------------------
\author Andrew "Zlobnik" Chouprina, 2005
mail:		dxprg@mail.ru

Created:	15 june 2005
---------------------------------------------------------------------------------------*/
#pragma once

#include "Base.h"
#include "TypeInfo.h"

#include "render/renderManager.h"
#include "game/DynamicObject.h"



namespace test_PacMan
{

	//-----------------------------------------------------------------------------------
	// ����� �����
	class CScene : public render::IRendererable//, public game::IDynamicObject
	{
	public:
		CScene();

		void createLevel();
		void update(float dt);
		void render();

		CBaseObject* create (CBaseObject::eType type, const math::Vec2f& pos);

		bool isMoveable (const math::Vec2f& pos);

	private:
		typedef std::list<CBaseObject> TObjects;
		typedef TObjects::iterator TObjectsIter;
		TObjects m_lObjects;						// ��� ������� ������

		/* �����, ����� ������� ���������� ������������ ������������� ������ � ������� ����.
		������������� ������ �������� ������ � ������ ������ */
		float		m_fIntroMusicTime;
		float		m_fPacManRespawnTime;			// ����� ����������� �������
		float		m_fPacManDeathTime;				// �����, �� ������� ������ ��������
		math::Vec2f m_vPacManEmitterPos;			// ������� ��������� �������

		math::Vec2f m_vGhostEmitterPos;				// ������� ��������� ���������
		float		m_fGhostEmitterRate;			// ������� ��������� ���������
	};

	extern CScene g_Scene;							// �����

}