/**--------------------------------------------------------------------------------------

									RGDE Engine

	-----------------------------------------------------------------------------
\author Denis V. Ovod, 2003

\author Andrew "Zlobnik" Chouprina, 2005
mail:	dxprg@mail.ru


Created:			17:9:2003 (Denis V. Ovod)
Modified for RGDE:	march-april 2005 (Zlobnik)
---------------------------------------------------------------------------------------*/
#pragma once

#include <rgde/render/particles/particle.h>
#include <rgde/math/random.h>
#include <rgde/render/particles/tank.h>


namespace particles{

	class base_emitter;
	class renderer;


	class  processor : public io::serialized_object
	{
		// need to manually increment after each file format change (for code simplisity)
		static const unsigned file_version = 1004;
	public:		
		processor(base_emitter* em = 0);
		virtual ~processor();

		void load();

		void render();
		void update(float dt);
		virtual void debug_draw();
		void reset();

		inline void set_emitter(base_emitter* em) { m_parent_emitter = em; }

		const math::matrix44f& local_trasform();

		void texture(render::texture_ptr texture);

		// interpolators
		inline math::interpolatorf& rate()							{ return m_rate; }
		inline math::interpolatorf& resistance()					{ return m_resistance; }
		inline math::interpolatorf& spin()							{ return m_spin; }
		inline math::interpolatorf& spin_spread()					{ return m_spin_spread; }
		inline math::interpolatorf& particle_life()					{ return m_life; }
		inline math::interpolatorf& particle_life_spread()			{ return m_life_spread; }
		inline math::interpolatorf& particle_size()					{ return m_size; }
		inline math::interpolator_col& particle_color()				{ return m_color_alpha; }
		inline math::interpolator_v3f& particle_force()				{ return m_acting_force; }
		inline math::interpolator_v3f& particle_velocity()			{ return m_velocity; }
		inline math::interpolator_v3f& particle_initial_vel_spread(){ return m_initial_vel_spread; }
		inline math::interpolatorf& particle_vel_spread_amplifier()	{ return m_vel_spread_amp; }

		// getters/setters
		inline bool is_fading() const { return m_is_fading; }
		inline void fade(bool b) { m_is_fading = b; }

		inline unsigned particles_limit() const { return m_max_particles; }
		inline void particles_limit (unsigned num) 
		{ 
			m_max_particles = num; 
			m_particles.resize(m_max_particles);
		}

		inline int seed() const { return m_max_particles; }
		inline void seed(int seed) { m_rnd_seed = seed; }

		inline bool visible() const { return m_visible; }
		inline void visible(bool v) { m_visible = v; }

		inline bool additive_blend() const { return m_additive_blend; }
		inline void additive_blend(bool f) { m_additive_blend = f; }

		inline bool sparks_mode() { return m_is_sparks; }
		inline void sparks_mode(bool sm) { m_is_sparks = sm; }

	protected:
		inline void assign_children();
		inline void init_particle(particle& p);

		void first_time_init();
		void update_particle(particle& p);
		void update_particle();
		void add_new_particles(int num2add);

		virtual void to_stream(io::write_stream& wf) const;
		virtual void from_stream(io::read_stream& rf);

	protected:
		renderer m_tank;
		render::texture_ptr m_texture;

		//////////////////////////////////////////////////////////////////////////
		// ��� ������ � ������������� ���������
		//////////////////////////////////////////////////////////////////////////
		// ���� ������������ ������������� ���� ����������� �������� 
		// ���������� ��� �������������
		bool m_is_anim_texture_used;
		// ���-�� ����������� �������
		unsigned char m_ucCol;
		// ���-�� ����������� �����
		unsigned char m_ucRow;
		// ���-�� �������
		unsigned char m_ucTcol;
		// ���-�� �����
		unsigned char m_ucTrow;
		// ���-�� ������ 
		unsigned char m_ucTexFrames;
		// �������� �� ������������ ���������� ��������
		// ���� ��� - �� �������� ��������� �� ����� ����� ��������
		bool m_is_anim_texture_cycled;
		// �������� ��������������� ���������� ��������
		// � ������ � �������, ����� ����������� �� "��������" �������
		unsigned m_texture_fps;
		// animation m_Texture frame random shift 
		unsigned m_rnd_frame;
		// is play animation, if not - will randomize m_Texture
		bool m_is_play_tex_anim;
		//////////////////////////////////////////////////////////////////////////

		base_emitter* m_parent_emitter;

		math::unit_rand_2k  rnd;

		int m_rnd_seed;

		math::interpolatorf m_rate;						// ����� ���������� ������ � ������� �������
		math::interpolatorf m_resistance;				// ������ (����������)
		math::interpolatorf m_spin;						// ��������
		math::interpolatorf m_spin_spread;
		math::interpolatorf m_life;						// ����� ����� (Time to live, TTL)
		math::interpolatorf m_life_spread;
		math::interpolatorf m_size;						// ������ 
		math::interpolator_col m_color_alpha;				// ���� � �����, 2 � 1
		math::interpolator_v3f m_acting_force;
		math::interpolator_v3f m_velocity;					// �������� (XYZ)
		math::interpolator_v3f m_initial_vel_spread;
		math::interpolatorf m_vel_spread_amp;		// ��������� ���������� ������� ��������

		bool m_is_fading;								// �������� �� ��������� (���������� ��������� �� �������� ����� ������)

		bool m_additive_blend;								// ������ ����� ���������
		math::vec3f m_scaling;								// ��������������� ������������� �������
		int m_max_particles;							// ������������ ����� ������ � ����������

		float m_ngkx;
		
		bool m_is_sparks;

		particles_t m_particles;

		bool m_modifiers_loaded;
		bool m_visible;
		bool m_ptank_inited;

		float m_normalized_time;		// ������������� �� 0 �� 1
		float m_rate_accum;				// �������� ������� ����� �� rate �� ����� � �����
		float m_dt;
	};
}