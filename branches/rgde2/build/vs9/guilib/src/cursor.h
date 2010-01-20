#pragma once

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

namespace gui
{
	class Imageset;
	typedef boost::shared_ptr<Imageset> ImagesetPtr;

	class Image;
	class Renderer;

	class GUILIB_API Cursor
	{
	public:
		Cursor(Renderer& r);
		~Cursor();

		void setImageset(ImagesetPtr set) { m_cursors = set; }
		void setType(const std::string& curname);
		std::string getType(void) const;
		void render();

		void setPosition(Point pt);
		Point getPosition() const;

	protected:
		Cursor& operator=(const Cursor&) { return *this; }
		ImagesetPtr		m_cursors;	
		Point			m_cursorPos;
		Point			m_renderPos;
		const Image*	m_currentCursor;
		Renderer&		m_render;
	};
}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif
