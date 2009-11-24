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


namespace particles{

	class base_emitter;
	class renderer;


	class  processor : public io::serialized_object
					 , public core::meta_class
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

		const math::matrix44f& get_local_tm();

		void set_texture_name(const std::string& texture_name);

		// interpolators
		inline math::interpolatorf& particleRate()				{ return m_rate; }
		inline math::interpolatorf& particleResistance()			{ return m_resistance; }
		inline math::interpolatorf& particleSpin()				{ return m_spin; }
		inline math::interpolatorf& particleSpinSpread()			{ return m_spin_spread; }
		inline math::interpolatorf& particleLife()				{ return m_life; }
		inline math::interpolatorf& particleLifeSpread()			{ return m_life_spread; }
		inline math::interpolatorf& particleSize()				{ return m_size; }
		inline math::interpolator_col& particleColorAlpha()			{ return m_color_alpha; }
		inline math::interpolator_v3f& particleActingForce()			{ return m_acting_force; }
		inline math::interpolator_v3f& particleVelocity()				{ return m_velocity; }
		inline math::interpolator_v3f& particleInitialVelSpread()		{ return m_initial_vel_spread; }
		inline math::interpolatorf& particleVelSpreadAmplifier()	{ return m_vel_spread_amp; }

		// getters/setters
		inline bool isGlobal() const { return m_is_global; }
		inline void setGlobal(bool b) { m_is_global = b; }

		inline bool is_fading() const { return m_is_fading; }
		inline void set_fade(bool b) { m_is_fading = b; }

		inline unsigned getMaxParticles() const { return m_max_particles; }
		inline void setMaxParticles (unsigned num) { 
			m_max_particles = num; 
			m_particles.resize(m_max_particles);
		}

		inline int getSeed() const { return m_max_particles; }
		inline void set_seed(int seed) { m_rnd_seed = seed; }

		inline bool is_visible() const { return m_is_visible; }
		inline void setVisible(bool visible) { m_is_visible = visible; }

		inline bool getIntenseMode() const { return m_intense; }
		inline void setIntenseMode(bool intense) { m_intense = intense; }

		inline bool getSparkMode() { return m_is_sparks; }
		inline void setSparkMode(bool sm) { m_is_sparks = sm; }

	protected:
		void loadTexture();
		void initPTank();
		inline void assignChilds();
		inline void createParticle(particle& p);

		virtual void geomRender();
		void first_time_init();
		void updateParticle(particle& p);
		void formTank();
		void addNewParticles(int num2add);

		virtual void to_stream(io::write_stream& wf) const;
		virtual void from_stream(io::read_stream& rf);

	protected:
		renderer* m_tank;
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

		std::string m_texture_name;

		bool m_is_fading;								// �������� �� ��������� (���������� ��������� �� �������� ����� ������)
		bool m_is_global;								// �������� �� ��������� ���������� (�.�. �� ������� ������������ �������������)

		bool m_intense;								// ������ ����� ���������
		math::vec3f m_scaling;								// ��������������� ������������� �������
		int m_max_particles;							// ������������ ����� ������ � ����������

		float m_ngkx;
		
		bool m_is_sparks;
		bool m_is_geometric;

		particles_vector m_particles;

		bool m_modifiers_loaded;
		bool m_is_visible;
		bool m_is_texture_loaded;
		bool m_ptank_inited;

		float m_normalized_time;		// ������������� �� 0 �� 1
		float m_rate_accum;				// �������� ������� ����� �� rate �� ����� � �����
		float m_dt;
	};

}