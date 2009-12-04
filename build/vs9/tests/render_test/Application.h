#pragma once

#include "ArcBall.h"
#include "camera.h"
#include "game.h"
#include "sprite.h"

namespace rgde
{
	struct size
	{
		float w, h;
	};


	class application : public core::windows::window
	{
	public:
		application(int x, int y, int w, int h, const std::wstring& title);
		~application();

		void run();

		const size& get_size() const {return m_size;} 

		render::device& get_render_device()
		{
			return m_device;
		}

		xml::document& get_config() {return m_config;}

		audio::system& get_audio_system() {return  m_sound_system;}

	protected:
		virtual core::windows::result wnd_proc(ushort message, uint wparam, long lparam );
		void resize_scene(unsigned int width, unsigned int height);
		bool do_events();

		void init_game_data();
		void init_render_data();

		void update();
		void render();

	private:
		core::vfs::system m_filesystem;
		xml::document m_config;
		render::device m_device;
		audio::system m_sound_system;
		game::system m_game;
		
		bool m_active;
			
		size m_size;

		render::vertex_buffer_ptr m_vb;
		render::index_buffer_ptr m_ib;

		math::vec3f m_cam_pos;
		camera m_camera;		

		int old_x;
		int old_y;

		int clicked_x;
		int clicked_y;

		double m_elapsed;
		boost::timer m_timer;

		math::color m_back_color;	
		render::canvas m_batcher2d;

		render::font_ptr m_font;

		ArcBall m_arc_ball;
	};
}