#pragma once

#include <rgde/render/effect.h>
#include <rgde/render/geometry.h>

namespace particles
{
	class renderer
	{
	public:
		/// ��������� � ����������� �� ������� 
		struct SParticle
		{
			math::vec3f		pos;			///> �������
			math::vec2f		size;			///> ������
			float			spin;			///> �������
			unsigned long	color;			///> ����
			unsigned int    nTile; //Temporary
		};

		/// ��� ������� ������
		typedef std::vector< SParticle > ParticleArray;
		typedef ParticleArray::iterator ParticleArrayIter;

		renderer();
		virtual ~renderer();

		void update();
		void render(render::texture_ptr texture, math::frame& transform);

		inline ParticleArray& getParticles() { return m_vParticleArray; }

		void setTextureTiling(int nRows, int nColumnsTotal, int nRowsTotal);

	protected:
		ParticleArray		m_vParticleArray;///> ������ ������
		unsigned long		m_reserved_size; ///> ����� ������, ��� �������� ��������������� ������

	private:
		render::effect_ptr		m_effect;

		typedef render::effect::parameter* EffectParam;
		EffectParam m_paramUpVec;
		EffectParam m_paramRightVec;
		EffectParam m_paramParticleTexture;
		EffectParam m_paramTransformMatrix;

		render::effect::technique* m_pRenderTechnique;

		typedef render::indexed_geometry<vertex::PositionColoredTextured2, false> geometry;
		geometry			m_geometry;

		int m_nRows;
		float m_fInvRows;
		float m_fInvTotalColumns;
		float m_fInvTotalRows;
	};

	typedef boost::shared_ptr<renderer> renderer_ptr;
}