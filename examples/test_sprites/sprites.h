#pragma once
#include <rgde/engine.h>

namespace rgde
{
	namespace exapmles
	{
		namespace sprites
		{
			class SpriteExample : public game::IDynamicObject
			{
			public:
				SpriteExample();

			protected:
				void onEsc ();
				void update (float dt);

			protected:
				render::SpriteManager			m_sprite_renderer;
				render::SpriteManager::SpritesVector m_sprites;
				input::KeyDown                  m_cEsc;
				// ����� ����������� ��������
				unsigned						m_priorities;
				// ����� �������� � ���������� �����������
				unsigned						m_nSpritesPerPriority;
				// ����� �� �������� ���������� ���
				bool							m_bDebugLog;
				// ����� �� ����������� ������� ����� �����
				bool							m_bSortSpritesBeforeLog;
				// ������� �������� ��������
				math::Vec2f						m_sprites_seed;
				::render::PFont					m_font;
				math::PCamera					m_camera;
			};
		}
	}
}
