#include "precompiled.h"

#include <rgde/math/transform.h>

#include "../base/exception.h"
#include <rgde/base/lexical_cast.h>

#include <rgde/render/lines3d.h>
#include <rgde/render/render_device.h>

namespace math
{
	frame_ptr frame::create()
	{
		return frame_ptr(new frame());
	}

	matrix44f frame::make_transform(const point3f& pos, const quatf& rot, const vec3f& s)
	{
		math::matrix44f rotation;
		math::setRot(rotation, rot);		

		math::matrix44f translate;
		math::setTrans(translate, pos);

		math::matrix44f scale;
		math::setScale(scale, s);

		return translate*rotation*scale;
	}

	matrix44f frame::make_transform(const point3f& pos, const EulerAngleXYZf& rot, const vec3f& s)
	{
		math::quatf quat = math::make<quatf, EulerAngleXYZf>(rot);
		return make_transform(pos, quat, s);
	}

	frame::frame()
		: m_need_recompute(false),
		  core::meta_node<frame>("frame"),
		  m_recompute_global_matrix(true),
		  m_scale(1.0f,1.0f,1.0f)
	{
		//property_owner::addProperty(new property<math::vec3f>(m_scale, "Scale"));
		//property_owner::addProperty(new property<point3f>(m_position, "Position", "Point"));
		//property_owner::addProperty(new property<quatf>(m_rotation, "Rotation", "Quaternion"));
	}

	frame::~frame()
	{
	}

	void frame::find(const std::string& str_template, std::vector<frame_ptr>& container)
	{
		const std::string &frame_name = name();

		size_t pos = frame_name.find_first_of("_");
		if(pos != -1)
		{
			size_t nBegin = frame_name.find_first_not_of(" ");
			std::string name = frame_name.substr(nBegin, pos - nBegin);

			if(name == str_template)
				container.push_back(this);
		}

		for (math::frame::children_list::const_iterator it = children().begin(); it != children().end(); it++)
			(*it)->find(str_template, container);
	}

	void frame::position(const point3f& pos)
	{
		m_position = pos;
		m_need_recompute = true;
	}

	void frame::rotation(const quatf& quat)
	{
		m_rotation = quat;
		m_need_recompute = true;
	}

	void frame::lookat(const vec3f& eye, const vec3f& lookat, const vec3f& up_vec)
	{	
		m_position = eye;
		const math::vec3f& up = up_vec;
		math::vec3f at = lookat - eye;

		{	
			using namespace math;
			vec3f z = makeNormal<float>(at);
			vec3f x = makeNormal<float>(makeCross(up, z));
			vec3f y = makeCross<float>(z, x);

			Matrix33f mat = makeAxes<Matrix33f>(x, y, z);
			set(m_rotation, mat); 
		}

		m_need_recompute = true;
	}

	void frame::scale(const vec3f& s)
	{
		m_scale = s;
		m_need_recompute = true;
	}

	const matrix44f & frame::local_trasform() const
	{
		update_transform();
		return m_local_tm;
	}

	const matrix44f & frame::world_trasform() const
	{
        update_world_transform();
		return m_fullTransform;
	}

	void frame::debug_draw() const
	{
		const float l = 10.5f;
		math::point3f p = world_position();

		math::point3f X = p + l * world_left();
		math::point3f Y = p + l * world_up();
		math::point3f Z = p + l * world_at();

		render::lines3d& line_manager = render::render_device::get().get_lines3d();
		line_manager.add_line( p, X, math::Red );
		line_manager.add_line( p, Y, math::Green );
		line_manager.add_line( p, Z, math::Blue );
	}

	void frame::update_transform() const
	{
		if (!m_need_recompute)
			return;

		math::matrix44f rotation;
		math::setRot(rotation, m_rotation);		

		math::matrix44f translate;
		math::setTrans(translate, m_position);
		
		math::matrix44f scale;
		math::setScale(scale, m_scale);

		m_local_tm = translate * rotation * scale;

		m_need_recompute = false;
		m_recompute_global_matrix = true;
	}

	void frame::update_world_transform() const 
	{
		if (m_need_recompute)
			update_transform();

		if (!m_recompute_global_matrix)
			return;

		update_transform();

		if (parent())
			m_fullTransform = parent()->world_trasform() * m_local_tm;
		else
			m_fullTransform = m_local_tm;

		m_recompute_global_matrix = false;
	}

	void frame::on_parent_change()
	{
		m_need_recompute = true;
	}

	point3f frame::world_position() const 
	{
		update_world_transform();
		const  matrix44f &m	= m_fullTransform;
		return point3f(m.mData[12], m.mData[13], m.mData[14]);
	}

	// left(right)  up          at
	//xaxis.x     yaxis.x     zaxis.x
	//xaxis.y     yaxis.y     zaxis.y
	//xaxis.z     yaxis.z     zaxis.z
	vec3f frame::up() const 
	{
		update_transform();
		const matrix44f &m= m_local_tm;
		return vec3f(m[1][0], m[1][1], m[1][2]);
	}
	vec3f frame::at() const 
	{
		update_transform();
		const matrix44f &m= m_local_tm;
		return vec3f(m[2][0], m[2][1], m[2][2]);
	}
	vec3f frame::left() const 
	{
		update_transform();
		const matrix44f &m= m_local_tm;
		return vec3f(m[0][0], m[0][1], m[0][2]);
	}

	vec3f frame::world_up() const
	{
		update_world_transform();
		matrix44f &m = m_fullTransform;
		return vec3f(m[1][0], m[1][1], m[1][2]);
	}

	vec3f frame::world_at() const
	{
		update_world_transform();
		matrix44f &m = m_fullTransform;
		return vec3f(m[2][0], m[2][1], m[2][2]);
	}

	vec3f frame::world_left() const
	{
		update_world_transform();
		matrix44f &m = m_fullTransform;
		return vec3f(m[0][0], m[0][1], m[0][2]);
	}

	//Neonic: octree
	void frame::update( bool invalidate_transform )
	{
		for (math::frame::children_list::const_iterator it = children().begin(); it != children().end(); it++)
			(*it)->update(invalidate_transform);
	};

	//-----------------------------------------------------------------------------------
	void frame::to_stream(io::write_stream& wf) const
	{
		wf	<< m_scale
			<< m_position
			<< m_rotation;

		//// ��������� �������� �������������
		wf << (unsigned int)m_children.size();
		for( children_list::const_iterator it = m_children.begin(); it != m_children.end(); it++ )
			(*it)->to_stream( wf );
	}

	//-----------------------------------------------------------------------------------
	void frame::from_stream(io::read_stream& rf)
	{
		rf	>> m_scale
			>> m_position
			>> m_rotation;

		m_need_recompute = true;
		
		//// ������ �������� �������������
		unsigned nChildren;
		rf >> nChildren;

		for(unsigned i = 0; i < nChildren; i++)
		{
			frame_ptr child = new frame;
			child->from_stream( rf );
			add( child );
		}
	}

	std::ostream& operator<<(std::ostream& out, const math::frame& f)
	{
		return out;
	}

	std::istream& operator>>(std::istream& in, math::frame& f)
	{
		return in;
	}
}