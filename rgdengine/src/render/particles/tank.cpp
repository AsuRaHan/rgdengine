#include "precompiled.h"

#include <rgde/render/particles/main.h>
#include <rgde/render/particles/tank.h>


namespace particles
{
	//-----------------------------------------------------------------------------------
	renderer::renderer() : m_reserved_size(0)
	{
		m_effect = render::effect::create( "particles.fx" );

		render::effect::params_map& params = m_effect->get_params();

		m_paramUpVec			= params["m_vUp"];
		m_paramRightVec			= params["m_vRight"];
		m_paramParticleTexture	= params["ParticlesTexture"];
		m_paramTransformMatrix	= params["m_mLVP"];

		m_pRenderTechnique = m_effect->find_technique("PartilesRenderModulate");

		texture_tiling(1, 1, 1);
	}

	//-----------------------------------------------------------------------------------
	renderer::~renderer()
	{
	}
	//-----------------------------------------------------------------------------------
	void renderer::render(render::texture_ptr texture, math::frame_ptr frame)
	{
		if( (m_reserved_size == 0) )
			return;

		const math::matrix44f& mLocal	= frame->world_trasform();
		math::camera_ptr camera		= render::render_device::get().camera();
		const math::matrix44f& mProj	= camera->proj_matrix();
		const math::matrix44f& mView	= camera->view_matrix();
		
		math::matrix44f mSystem = mView * mLocal;
		math::matrix44f mLVP = mProj * mSystem;

		bool useGlobalUp = false;

		//math::vec4f right(mSystem.mData[0], mSystem.mData[4], mSystem.mData[8], 0.0f);
		//math::vec4f up(mSystem.mData[1], mSystem.mData[5], mSystem.mData[9], 0);

		math::vec4f right(mView.mData[0], mView.mData[4], mView.mData[8], 0.0f);
		math::vec4f up(mView.mData[1], mView.mData[5], mView.mData[9], 0);

		//math::vec4f right(mSystem.mData[0], mSystem.mData[8], mSystem.mData[4], 0.0f);
		//math::vec4f up(mSystem.mData[1], mSystem.mData[9], mSystem.mData[5], 0);

		//math::normalize(right);
		//math::normalize(up);
	

		if (useGlobalUp)
		{
			right[1] = 0;
			math::normalize(right);
			up = math::vec4f(0, 1, 0, 0);
		}

		m_paramParticleTexture->set(texture);
		m_paramTransformMatrix->set(mLVP);
		m_paramRightVec->set(right);
		m_paramUpVec->set(up);
		
		std::vector<render::effect::technique::pass*>& passes = m_pRenderTechnique->get_passes();

		m_effect->commit_changes();
		m_pRenderTechnique->begin();

		for(size_t pass = 0; pass < passes.size(); ++pass)
		{
			passes[pass]->begin();
			m_geometry.render( render::TriangleList, 2*(unsigned)m_particles.size() );
			passes[pass]->end();
		}

		m_pRenderTechnique->end();
	}
	//-----------------------------------------------------------------------------------
	void renderer::update()
	{
		unsigned int nParticles = (unsigned int)m_particles.size();

		if( nParticles == 0 ) return;

		if( (nParticles > m_reserved_size) )
		{
			m_reserved_size = nParticles;

			geometry::indexies& indexies = m_geometry.lock_ib();
			if( indexies.size() < nParticles*6 )
				indexies.resize(nParticles*6);
			for(unsigned i = 0; i < nParticles; ++i)
			{
				indexies[i * 6 + 0] = i * 4 + 0;
				indexies[i * 6 + 1] = i * 4 + 1;
				indexies[i * 6 + 2] = i * 4 + 2;
				indexies[i * 6 + 3] = i * 4 + 3;
				indexies[i * 6 + 4] = i * 4 + 2;
				indexies[i * 6 + 5] = i * 4 + 1;
			}
			m_geometry.unlock_ib();
		}

		geometry::vertexies& vertexies = m_geometry.lock_vb();
		if( vertexies.size() < nParticles*4 )
			vertexies.resize(nParticles*4);

		unsigned int j = 0;
		for( unsigned int i = 0; i < nParticles; ++i )
		{
			particle_t & p = m_particles[i];
			float sizex = p.size[0]*0.5f;
			float sizey = p.size[1]*0.5f;
			float& spin = p.spin;

			float xsin = sizex*::sin(spin);
			float xcos = sizex*::cos(spin);
			float ysin = sizey*::sin(spin);
			float ycos = sizey*::cos(spin);

			float fTileY = (float)(p.tile%m_rows),
				  fTileX = ((float)p.tile - fTileY)*m_fInvRows;


			vertexies[j].position = p.pos;
			vertexies[j].tex1 = math::vec2f( -xcos - ysin, -xsin + ycos );
			vertexies[j].tex0 = math::vec2f(fTileX*m_fInvTotalColumns, fTileY*m_fInvTotalRows);
			vertexies[j].color = p.color;
			++j;

			vertexies[j].position = p.pos;
			vertexies[j].tex1 = math::vec2f( xcos - ysin, xsin + ycos );
			vertexies[j].tex0 = math::vec2f((fTileX + 1.0f)*m_fInvTotalColumns, fTileY*m_fInvTotalRows);
			vertexies[j].color = p.color;
			++j;

			vertexies[j].position = p.pos;
			vertexies[j].tex1 = math::vec2f( -xcos + ysin, -xsin - ycos );
			vertexies[j].tex0 = math::vec2f(fTileX*m_fInvTotalColumns, (fTileY + 1.0f)*m_fInvTotalRows);
			vertexies[j].color = p.color;
			++j;

			vertexies[j].position = p.pos;
			vertexies[j].tex1 = math::vec2f( xcos + ysin, xsin - ycos );
			vertexies[j].tex0 = math::vec2f((fTileX + 1.0f)*m_fInvTotalColumns, (fTileY + 1.0f)*m_fInvTotalRows);
			vertexies[j].color = p.color;
			++j;
		}
		m_geometry.unlock_vb();
	}

	void renderer::texture_tiling(int rows, int columns_total, int rows_total)
	{
		m_rows = rows;
		m_fInvRows = 1.0f/(float)rows;
		m_fInvTotalColumns = 1.0f/(float)columns_total;
		m_fInvTotalRows = 1.0f/(float)rows_total;
	}

}