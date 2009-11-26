#pragma once

//#include <rgde/base/singelton.h>

#include <rgde/math/types3d.h>

#include <rgde/render/render_device.h>
#include <rgde/render/manager.h>
#include <rgde/render/geometry.h>

namespace render
{
	typedef boost::shared_ptr<class texture> texture_ptr;
	typedef boost::shared_ptr<class effect> effect_ptr;

	struct sprite
	{
		math::Rect rect;				///> sprites UV rect
		math::vec2f pos;				///> sprite position (in screen coords)
		math::vec2f size;				///> sprite size (in screen coords)
		float spin;						///< sprite rotation
		unsigned long priority;			///> drawing priority
		render::texture_ptr texture;	///> texture pointer
		math::Color color;				///> color

		sprite();
		sprite( const math::vec2f& pos_, const math::vec2f& size_, 
			const math::Color& color_ = 0xffffffff,render::texture_ptr pTexture_ = render::texture_ptr(), 
			float spin_ = 0, const math::Rect& rect_ = math::Rect(0, 0, 1, 1),			
			unsigned long uPriority_ = 0 );
	};

	class sprite_manager : public device_object, public rendererable
	{
	public:
		typedef std::vector<sprite> sprites_vector;
		typedef sprites_vector::iterator sprites_iter;

		sprite_manager(int priority = 0);
		~sprite_manager();
	
		void set_blending(bool bAditive) { m_aditive = bAditive; }

		inline sprites_vector& get_sprites() { return m_sprites; }
		inline unsigned get_num_rendered() { return m_sprites_rendered; }

		inline math::vec2f& get_origin() { return m_origin; }
		inline void			set_origin(math::vec2f& vNewOrigin) { m_origin = vNewOrigin; }

		virtual void add_sprite(const sprite& s);

		void update();

	protected:
		void render();		
		
		virtual void onLostDevice();
		virtual void onResetDevice();

	protected:
		bool m_aditive;

		sprites_vector m_sprites;						// �������
		unsigned m_sprites_rendered;				/// ����� ������������ � ��������� ��� ��������

		effect_ptr  m_effect;

		typedef indexed_geometry<vertex::PositionTransformedColoredTextured, false> geometry;
		geometry m_geometry;						/// ���������

		unsigned m_reserved_size;					/// ����� ��������, ��� ������� ��������������� ������

		bool m_sorted;								/// ������������� �� ������� � ������� �� ����������
		bool m_updated;							/// ���� �� ������� ��������� / �������
		
		const math::vec2f m_screen_size;			// ���������� ������, ��� �������� �������� �������� ���������� ����������
		math::vec2f m_scale;						// ����������� ��������������� ���������� �������������� � ������� ����� �� �������� �������� ����������
		math::vec2f m_origin;

		effect::technique *m_additive_tech;
		effect::technique *m_modulate_tech;
		effect::parameter *m_texture_param;

		/// ��� ���������� ������������ ������ ��� �������� ���������� ��������
		std::vector<unsigned> m_equal_priorities_num;	/// ����� �������� � ������� � ����������� ������������
	};

	typedef base::singelton<sprite_manager> TheSpriteManager;
}