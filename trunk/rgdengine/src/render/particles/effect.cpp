#include "precompiled.h"

#include <rgde/render/particles/main.h>
#include <rgde/render/particles/effect.h>

// ���� �������
#include <rgde/render/particles/static_emitter.h>
#include <rgde/render/particles/tank.h>

// ����������� ��������
#include <rgde/render/particles/box_emitter.h>
#include <rgde/render/particles/spherical_emitter.h>


namespace particles
{
	//-----------------------------------------------------------------------------------
	Effect::Effect() : render::rendererable(9), m_fOldTime(0), m_bIsFading(false), 
						 core::XmlClass("ParticleEffect")
	{	
		m_renderInfo.pRenderFunc		= boost::bind( &Effect::render, this );
		m_renderInfo.pDebugRenderFunc	= boost::bind(&Effect::debugDraw, this);
		
		// public properties:
		//REGISTER_PROPERTY(Transform, math::Frame)
	}
	//-----------------------------------------------------------------------------------
	Effect::~Effect()
	{
		for (tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it)
			delete( *it );
		m_Emitters.clear();
	}
	//-----------------------------------------------------------------------------------
	void Effect::reset()
	{
		m_bIsFading = false;
		setEmittersToFade(m_bIsFading);

		for (tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it)
			(*it)->reset();
	}
	//-----------------------------------------------------------------------------------
	void Effect::render()
	{
		for (tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it)
			(*it)->render();
	}
	//-----------------------------------------------------------------------------------
	void Effect::setEmittersToFade(bool b)
	{
		for(tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it)
			(*it)->setFade(b);
	}
	//-----------------------------------------------------------------------------------
	void Effect::update(float fDeltaTime)
	{
		static float dt = 0.02f;

		{ // �������� ������ ������ 25 ��� � �������
			dt += fDeltaTime;
			if (dt < 0.02f) return;
		}
		
		for (tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it)
			(*it)->update(dt);

		dt = 0;
	}

	//-----------------------------------------------------------------------------------
	void Effect::addEmitter(Emitter* em)
	{
		assert(0 != em);
		m_Emitters.push_back(em);
		m_Transform.addChild(&em->getTransform());
	}
	
	//-----------------------------------------------------------------------------------
	void Effect::deleteEmitter(Emitter* em)
	{
		assert(0 != em);
		m_Transform.removeChild(&em->getTransform());		
		m_Emitters.remove(em);
	}

	//-----------------------------------------------------------------------------------
	void Effect::debugDraw()
	{
		m_Transform.debugDraw();
		for( tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); ++it )
			(*it)->debugDraw();
	}
	//-----------------------------------------------------------------------------------
	void Effect::toStream(io::IWriteStream& wf)
	{
		wf << ms_nVersion;
		wf << m_Transform;

		// ��������� ����������� �������
		wf << (unsigned)m_Emitters.size();
		for( tEmittersIter it = m_Emitters.begin(); it != m_Emitters.end(); it++ )
			wf << *(*it);
	}
	//----------------------------------------------------------------------------------
	render::SRenderableInfo&	Effect::getRenderableInfo()
	{
		return m_renderInfo;		
	}
	//-----------------------------------------------------------------------------------
	void Effect::fromStream(io::IReadStream& rf)
	{
		unsigned version;
		rf >> version;
		if (version != ms_nVersion)
			throw std::exception("pfx::Effect::fromStream(...): Unknown version !");
		
		rf >> m_Transform;

		unsigned size;
		rf >> size;
		for(unsigned i = 0; i < size; i++)
		{
			unsigned em_type = 0;
			rf >> em_type;
			Emitter::Type type = static_cast<Emitter::Type> (em_type);
		
			Emitter* em;
			switch(type)
			{
				case Emitter::Maya:		em = new IMayaEmitter;		break;
				case Emitter::Spherical:	em = new SphericalEmitter;	break;
				case Emitter::Box:			em = new BoxEmitter;		break;
			}
			rf >> (*em);
			addEmitter(em);
		}
	}
}