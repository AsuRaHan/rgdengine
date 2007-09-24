#pragma once

//#include <rgde/base/singelton.h>

#include <rgde/math/mathTypes3d.h>

#include <rgde/render/renderDevice.h>
#include <rgde/render/renderManager.h>
#include <rgde/render/renderGeometry.h>

namespace render
{
	typedef boost::shared_ptr<class ITexture> PTexture;
	typedef boost::shared_ptr<class IEffect> PEffect;

	struct SSprite
	{
		math::Rect rect;					///> ������������� ���������� ��������� �������
		math::Vec2f pos;					///> ������� ������� (� �������� �����������)
		math::Vec2f size;					///> ������ ������� (� �������� �����������)
		float spin;							///< �������
		unsigned long uPriority;			///> ��������� ���������
		render::PTexture pTexture;			///> ����� ��������
		math::Color color;					///> ����

		SSprite();
		SSprite( const math::Vec2f& pos_, const math::Vec2f& size_, 
			const math::Color& color_ = 0xffffffff,render::PTexture pTexture_ = render::PTexture(), 
			float spin_ = 0, const math::Rect& rect_ = math::Rect(0, 0, 1, 1),			
			unsigned long uPriority_ = 0 );
	};

	class CSpriteManager : public IDeviceObject, public IRendererable
	{
	public:
		typedef std::vector<SSprite> TSprites;
		typedef TSprites::iterator TSpritesIter;

		CSpriteManager(int priority = 0);
		~CSpriteManager();
	
		void setAditiveBlending(bool bAditive) { m_bAditive = bAditive; }

		inline TSprites& getSprites() { return m_vSprites; }
		inline unsigned getNumSpritesRendered() { return m_nSpritesRendered; }

		inline math::Vec2f& getOrigin() { return m_vOrigin; }
		inline void			setOrigin(math::Vec2f& vNewOrigin) { m_vOrigin = vNewOrigin; }

		virtual void addSprite(const SSprite& pSprite);

	protected:
		void render();
		void update();
		
		virtual void onLostDevice();
		virtual void onResetDevice();

	protected:
		bool m_bAditive;

		TSprites m_vSprites;						// �������
		unsigned m_nSpritesRendered;				/// ����� ������������ � ��������� ��� ��������

		PEffect  m_pEffect;

		typedef TIndexedGeometry<vertex::PositionTransformedColoredTextured, false> Geometry;
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

	typedef base::TSingelton<CSpriteManager> TheSpriteManager;
}