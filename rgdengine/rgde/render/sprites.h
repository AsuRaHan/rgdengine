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
		math::Rect rect;					///> ������������� ���������� ��������� �������
		math::vec2f pos;					///> ������� ������� (� �������� �����������)
		math::vec2f size;					///> ������ ������� (� �������� �����������)
		float spin;							///< �������
		unsigned long priority;			///> ��������� ���������
		render::texture_ptr texture;			///> ����� ��������
		math::Color color;					///> ����

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
		typedef sprites_vector::iterator SpritesIter;

		sprite_manager(int priority = 0);
		~sprite_manager();
	
		void setAditiveBlending(bool bAditive) { m_bAditive = bAditive; }

		inline sprites_vector& getSprites() { return m_sprites; }
		inline unsigned getNumSpritesRendered() { return m_nSpritesRendered; }

		inline math::vec2f& getOrigin() { return m_vOrigin; }
		inline void			setOrigin(math::vec2f& vNewOrigin) { m_vOrigin = vNewOrigin; }

		virtual void add_sprite(const sprite& pSprite);

	protected:
		void render();
		void update();
		
		virtual void onLostDevice();
		virtual void onResetDevice();

	protected:
		bool m_bAditive;

		sprites_vector m_sprites;						// �������
		unsigned m_nSpritesRendered;				/// ����� ������������ � ��������� ��� ��������

		effect_ptr  m_effect;

		typedef indexed_geometry<vertex::PositionTransformedColoredTextured, false> geometry;
		geometry m_geometry;						/// ���������

		unsigned m_nReservedSize;					/// ����� ��������, ��� ������� ��������������� ������

		bool m_bSorted;								/// ������������� �� ������� � ������� �� ����������
		bool m_bUpdated;							/// ���� �� ������� ��������� / �������
		
		const math::vec2f m_cvScreenSize;			// ���������� ������, ��� �������� �������� �������� ���������� ����������
		math::vec2f m_vScale;						// ����������� ��������������� ���������� �������������� � ������� ����� �� �������� �������� ����������
		math::vec2f m_vOrigin;

		/// ��� ���������� ������������ ������ ��� �������� ���������� ��������
		std::vector<unsigned> m_vEqualPrioritiesN;	/// ����� �������� � ������� � ����������� ������������
	};

	typedef base::singelton<sprite_manager> TheSpriteManager;
}