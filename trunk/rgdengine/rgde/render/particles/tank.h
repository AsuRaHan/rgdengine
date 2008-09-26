#pragma once

#include <rgde/render/effect.h>
#include <rgde/render/geometry.h>

namespace particles
{
	class PTank
	{
	public:
		/// ��������� � ����������� �� ������� 
		struct SParticle
		{
			math::Vec3f		pos;			///> �������
			math::Vec2f		size;			///> ������
			float			spin;			///> �������
			unsigned long	color;			///> ����
			unsigned int    nTile; //Temporary
		};

		/// ��� ������� ������
		typedef std::vector< SParticle > ParticleArray;
		typedef ParticleArray::iterator ParticleArrayIter;

		PTank();
		virtual ~PTank();

		void update();
		void render(render::texture_ptr texture, math::Frame& transform);

		inline ParticleArray& getParticles() { return m_vParticleArray; }

		void setTextureTiling(int nRows, int nColumnsTotal, int nRowsTotal);

	protected:
		ParticleArray		m_vParticleArray;///> ������ ������
		unsigned long		m_nReservedSize; ///> ����� ������, ��� �������� ��������������� ������

	private:
		render::PEffect		m_spEffect;

		typedef render::Effect::IParameter* EffectParam;
		EffectParam m_paramUpVec;
		EffectParam m_paramRightVec;
		EffectParam m_paramParticleTexture;
		EffectParam m_paramTransformMatrix;

		render::Effect::ITechnique* m_pRenderTechnique;

		typedef render::TIndexedGeometry<vertex::PositionColoredTextured2, false> Geometry;
		Geometry			m_Geometry;

		int m_nRows;
		float m_fInvRows;
		float m_fInvTotalColumns;
		float m_fInvTotalRows;
	};

	typedef boost::shared_ptr<PTank> PPTank;
}