#pragma once

#include <rgde/math/types3d.h>

namespace render
{
	class fader
	{
	public:
		enum Mode
		{
			Fade,
			Unfade,
			FadeUnfade,
			UnfadeFade
		};

		enum State
		{
			Fading,
			Unfading,
			Disabled
		};

		fader();
		fader(const std::string& file_name);

		void               setColor(const math::Color& color);
		const math::Color& get_color() const {return m_color;}

		void  setFadingTime(float fFadingTime);
		float getFadingTime() const {return m_fFadingTime;}

		void  setUnfadingTime(float fUnfadingTime);
		float getUnfadingTime() const {return m_fUnfadingTime;}

		void activate(Mode mode);

		State getState() const {return m_state;}

		void update(float dt);

		void load_from_xml(const std::string& file_name);

	private:
		void init();
		void disable();
		void render();		

	private:
		Mode		m_mode;
		State		m_state;
		float       m_fTimeElapsed;
		float       m_fFadingTime;
		float       m_fUnfadingTime;
		math::Color m_color;
	};
}