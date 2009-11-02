#pragma once
#include <rgde/engine.h>

namespace rgde
{
	namespace exapmles
	{
		namespace sprites
		{
			class sprite_example : public game::dynamic_object
			{
			public:
				sprite_example();

			protected:
				void onEsc ();
				void update (float dt);

			protected:
				render::sprite_manager			m_sprite_renderer;
				render::sprite_manager::SpritesVector m_sprites;
				input::key_down                  m_cEsc;
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
				::render::font_ptr					m_font;
				math::camera_ptr					m_camera;
			};
		}
	}
}
