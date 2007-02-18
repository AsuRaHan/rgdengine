#pragma once
#include <engine.h>

class CSpriteTest : public game::IDynamicObject
{
public:
	CSpriteTest();

protected:
	void onEsc (const input::CButtonEvent&);
	void update (float dt);

protected:
	render::CSpriteManager				m_sprite_renderer;
	render::CSpriteManager::TSprites	m_vSprites;
	input::CButtonCommand				m_cEsc;
	unsigned							m_nPriorities;				// ����� ����������� ��������
	unsigned							m_nSpritesPerPriority;		// ����� �������� � ���������� �����������
	bool								m_bDebugLog;				// ����� �� �������� ���������� ���
	bool								m_bSortSpritesBeforeLog;	// ����� �� ����������� ������� ����� �����
	math::Vec2f							m_vSpritesSeed;				// ������� �������� ��������
	::render::PFont						m_spFont;
	math::PCamera						m_camera;
};