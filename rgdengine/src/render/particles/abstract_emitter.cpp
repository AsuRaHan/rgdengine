#include "precompiled.h"

#include <rgde/render/particles/main.h>
#include <rgde/render/particles/abstract_emitter.h>
#include <rgde/render/particles/processor.h>


namespace particles{
	//-----------------------------------------------------------------------------------
	void base_emitter::get_particle(particle& p) 
	{
		p = particle();

		p.mass = m_PMass.get_value(m_normalized_time)
			+ (m_Rand() * 2.0f - 1.0f) * m_PMassSpread.get_value(m_normalized_time);

		p.rotation = m_Rand() * m_PRotationSpread.get_value(m_normalized_time);
	}
	//-----------------------------------------------------------------------------------
	void base_emitter::addProcessor(processor* pp)
	{
		if (0 == pp)
			throw std::exception("base_emitter::addProcessor(): zero pointer!");

		m_lProcessors.push_back(pp);
		pp->set_emitter(this);
	}
	//-----------------------------------------------------------------------------------
	void base_emitter::reset()
	{
		//m_vCurDisplacement = math::vec3f();
		//m_vCurSpeed = math::vec3f();
		//m_vOldPos = math::vec3f();

		m_fCurrentTime = 0;
		m_bIsEnded = false;
		m_normalized_time = 0;
		m_is_visible = true;

		for(processors_iter pi = m_lProcessors.begin(); pi != m_lProcessors.end(); ++pi)
			(*pi)->reset();
	}
	//////////////////////////////////////////////////////////////////////////
	void base_emitter::set_fade(bool b)
	{
		for (processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it)
			(*it)->set_fade(b);
	}
	//////////////////////////////////////////////////////////////////////////
	void base_emitter::update(float dt)
	{
		//if (m_bIsJustCreated && dt > 0.02f)
		//	dt = 0.02f;

		m_fCurrentTime += dt;

		// ���� ����� �� �������� ��������� - ���� ���������
		if (!(m_fCurrentTime < m_fCycleTime))
		{
			if (!m_bIsCycling){
				m_bIsEnded = true;
				m_is_visible = false;
				return;
			}
			else 
			{
				m_bIsEnded = false;
			}

			int i = (int)(m_fCurrentTime / m_fCycleTime);
			m_fCurrentTime = m_fCurrentTime - m_fCycleTime * i;
		}
		
		m_normalized_time = m_fCurrentTime / m_fCycleTime;
		{
			//math::matrix44f m = get_local_tm();

			//if (!m_bIsJustCreated)
			//{
			//	math::vec3f new_pos;
			//	math::setTrans(new_pos, m);
			//	m_vCurDisplacement = new_pos - m_vOldPos;
			//	m_vCurSpeed = m_vCurDisplacement / (dt * 20.0f);
			//	m_vOldPos = new_pos;
			//}
		}
		
		math::matrix44f m = get_full_tm();

		math::invert( m );
		m_vPAcceleration = m_PAcceleration.get_value(m_normalized_time);
		//m_vAccelerationPrecomputed = m.transformVector(m_vPAcceleration);
		math::xform( m_vAccelerationPrecomputed, m, m_vPAcceleration );
		m_vGlobalVel = m_GlobalVelocity.get_value(m_normalized_time);
		//m_vGlobalVelPrecomputed = m.transformVector(m_vGlobalVel);
		math::xform( m_vGlobalVelPrecomputed, m, m_vGlobalVel );
		//m_vCurSpeedTransformed = m.transformVector(m_vCurSpeed);
		math::xform( m_vCurSpeedTransformed, m, m_vCurSpeed );

		for (processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it)
			(*it)->update(dt);

		//m_bIsJustCreated = false;
	}

	void base_emitter::render()
	{
		if (m_is_visible)
		{
			// 1-�� ���������� �� ���������� ��������
			for (processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it)
				if (!((*it)->getIntenseMode()))(*it)->render();

			// 2-�� ���������� ���������� ��������
			for (processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it)
				if ((*it)->getIntenseMode())(*it)->render();
		}
	}


	base_emitter::base_emitter(type type) 
		: m_type(type)
		, m_fCurrentTime(0)
		, m_time_shift(0)
		, m_fCycleTime(5)
		, m_bIsCycling(true)
		, m_is_visible(true)
		, m_normalized_time(0)
	{
		m_PMass.add_key(1, 1.0f);
	}

	base_emitter::~base_emitter()
	{
		for( processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); it++ )
			delete(*it);
		m_lProcessors.clear();
	}
	
	void base_emitter::deleteProcessor(processor* p)
	{
		m_lProcessors.remove(p);
	}

	void base_emitter::to_stream(io::write_stream& wf) const
	{
		math::frame::to_stream (wf);

		wf	/*<< (int)m_type*/
			<< m_fCycleTime
			<< m_bIsCycling
			<< m_is_visible
			<< m_time_shift
			<< m_name
			<< (m_PMass)
			<< (m_PMassSpread)
			<< (m_PAcceleration)
			<< (m_GlobalVelocity)
			<< (m_velocity)
			<< (m_PVelSpread)
			<< (m_PRotationSpread);

		// ��������� ���������� ������
		wf << (unsigned)m_lProcessors.size();
		for( processors_list::const_iterator it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it)
			wf << *(*it);
	}

	void base_emitter::from_stream(io::read_stream& rf)
	{
		math::frame::from_stream (rf);

		//{
		//	type t;
		//	rf	>> (int)t;
		//	assert(m_type == t);
		//}

		rf	>> m_fCycleTime
			>> m_bIsCycling
			>> m_is_visible
			>> m_time_shift
			>> m_name
			>> (m_PMass)
			>> (m_PMassSpread)
			>> (m_PAcceleration)
			>> (m_GlobalVelocity)
			>> (m_velocity)
			>> (m_PVelSpread)
			>> (m_PRotationSpread);

		// loading processors
		unsigned int num_of_processors;
		rf >> num_of_processors;
		for( unsigned i = 0; i < num_of_processors; ++i )
		{
			processor* proc = new processor();
			rf >> (*proc);
			addProcessor(proc);
			proc->load();
		}
	}

	void base_emitter::debug_draw()
	{
		math::frame::debug_draw();

		for( processors_iter it = m_lProcessors.begin(); it != m_lProcessors.end(); ++it )
			(*it)->debug_draw();
	}
}