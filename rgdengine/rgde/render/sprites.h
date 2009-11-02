#pragma once

//#include <rgde/base/singelton.h>

#include <rgde/math/types3d.h>

#include <rgde/render/device.h>
#include <rgde/render/manager.h>
#include <rgde/render/geometry.h>

namespace render
{
	typedef boost::shared_ptr<class texture> texture_ptr;
	typedef boost::shared_ptr<class effect> effect_ptr;

	struct sprite
	{
		math::Rect rect;					///> ������������� ���������� ��������� �������
		math::Vec2f pos;					///> ������� ������� (� �������� �����������)
		math::Vec2f size;					///> ������ ������� (� �������� �����������)
		float spin;							///< �������
		unsigned long uPriority;			///> ��������� ���������
		render::texture_ptr texture;			///> ����� ��������
		math::Color color;					///> ����

		sprite();
		sprite( const math::Vec2f& pos_, const math::Vec2f& size_, 
			const math::Color& color_ = 0xffffffff,render::texture_ptr pTexture_ = render::texture_ptr(), 
			float spin_ = 0, const math::Rect& rect_ = math::Rect(0, 0, 1, 1),			
			unsigned long uPriority_ = 0 );
	};

	class SpriteManager : public device_object, public rendererable
	{
	public:
		typedef std::vector<sprite> SpritesVector;
		typedef SpritesVector::iterator SpritesIter;

		SpriteManager(int priority = 0);
		~SpriteManager();
	
		void setAditiveBlending(bool bAditive) { m_bAditive = bAditive; }

		inline SpritesVector& getSprites() { return m_sprites; }
		inline unsigned getNumSpritesRendered() { return m_nSpritesRendered; }

		inline math::Vec2f& getOrigin() { return m_vOrigin; }
		inline void			setOrigin(math::Vec2f& vNewOrigin) { m_vOrigin = vNewOrigin; }

		virtual void addSprite(const sprite& pSprite);

	protected:
		void render();
		void update();
		
		virtual void onLostDevice();
		virtual void onResetDevice();

	protected:
		bool m_bAditive;

		SpritesVector m_sprites;						// �������
		unsigned m_nSpritesRendered;				/// ����� ������������ � ��������� ��� ��������

		effect_ptr  m_effect;

		typedef indexed_geometry<vertex::PositionTransformedColoredTextured, false> Geometry;
		Geometry m_Geometry;						/// ���������

		unsigned m_nReservedSize;					/// ����� ��������, ��� ������� ��������������� ������

		bool m_bSorted;								/// ������������� �� ������� � ������� �� ����������
		bool m_bUpdated;							/// ���� �� ������� ��������� / �������
		
		const math::Vec2f m_cvScreenSize;			// ���������� ������, ��� �������� �������� �������� ���������� ����������
		math::Vec2f m_vScale;						// ����������� ��������������� ���������� �������������� � ������� ����� �� �������� �������� ����������
		math::Vec2f m_vOrigin;

		/// ��� ���������� ������������ ������ ��� �������� ���������� ��������
		std::vector<unsigned> m_vEqualPrioritiesN;	/// ����� �������� � ������� � ����������� ������������
	};

	typedef base::singelton<SpriteManager> TheSpriteManager;
}