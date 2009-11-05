#include "precompiled.h"

#include <rgde/render/lines2d.h>
#include <rgde/render/render_device.h>

#include "../base/exception.h"

namespace render
{
	//-----------------------------------------------------------------------------------
	lines2d::lines2d(unsigned long priority)
		: render::rendererable(1111),
		  m_geometry(true)
	{
		base::lmsg << "lines2d::lines2d()";
		m_vertices = &(m_geometry.lock());
		m_priority = priority;
		m_effect = effect::create("Line3dManager.fx");
		m_renderInfo.render_func = boost::bind(&lines2d::render, this);
	}
	//-----------------------------------------------------------------------------------
	void lines2d::render()
	{
		if (m_vertices->size() == 0) return;
		m_geometry.unlock();
		render::effect::technique *pTechnique	= m_effect->find_technique("Lines2d");
		pTechnique->begin();
		for (unsigned iPass = 0; iPass < pTechnique->get_passes().size(); ++iPass)
		{
			effect::technique::pass *pPass	= pTechnique->get_passes()[iPass];
			pPass->begin();
			m_geometry.render(PrimTypeLineList);
			pPass->end();
		}
		pTechnique->end();

		// ����� ����� ��������� ����� ������� ��� �����
		m_vertices = &(m_geometry.lock());
		m_vertices->resize(0);
	}
	//-----------------------------------------------------------------------------------
	void lines2d::add_line(const math::vec2f &point1, const math::vec2f point2, math::Color color)
	{
		math::vec2f screenSize(800, 600); //virtual screen size
		math::vec2f vFrontBufferSize= render::render_device::get().getBackBufferSize();
		math::vec2f m_vScale		= vFrontBufferSize / screenSize;
		m_vertices->push_back(Point(point1 * m_vScale, color));
		m_vertices->push_back(Point(point2 * m_vScale, color));
	}
} //~ namespace utility