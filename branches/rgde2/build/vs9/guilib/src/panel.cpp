#include "StdAfx.h"
#include "image.h"
#include "imageset.h"
#include "renderer.h"
#include "panel.h"

#include "system.h"


namespace gui
{

Panel::Panel(System& sys, const std::string& name) :
	BaseWindow(sys, name),
	m_backImg(0),
	m_topImg(0),
	m_toplImg(0),
	m_toprImg(0),
	m_lImg(0),
	m_rImg(0),
	m_botImg(0),
	m_botlImg(0),
	m_botrImg(0)
{
}

Panel::~Panel(void)
{
}

void Panel::render(const Rect& finalRect, const Rect& finalClip)
{
	renderFrame(finalRect, finalClip);
}

void Panel::renderFrame(const Rect& dest, const Rect& clip)
{
	Renderer& r = m_system.getRenderer();

	Rect backgroundRect(dest);
	Rect finalRect;
    Size imageSize;

	float topOffset = 0, bottomOffset = 0, leftOffset = 0, rightOffset = 0; 
    float topWidth, bottomWidth, leftHeight, rightHeight;
    topWidth = bottomWidth = dest.getWidth();
    leftHeight = rightHeight = dest.getHeight();

    // top-left image
    if (m_toplImg)
    {
        // calculate final destination area
        imageSize = m_toplImg->getPixelRect().getSize();
        finalRect.m_left = dest.m_left;
        finalRect.m_top  = dest.m_top;
        finalRect.setSize(imageSize);
        finalRect = dest.getIntersection (finalRect);

		topOffset  += imageSize.m_width;
		leftOffset += imageSize.m_height;
		topWidth   -= topOffset;
		leftHeight -= leftOffset;


        // draw this element.
        r.draw(*m_toplImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Stretch);
    }

    // top-right image
    if (m_toprImg)
    {
        // calculate final destination area
        imageSize = m_toprImg->getPixelRect().getSize();
        finalRect.m_left = dest.m_right - imageSize.m_width;
        finalRect.m_top  = dest.m_top;
        finalRect.setSize(imageSize);
        finalRect = dest.getIntersection (finalRect);

		rightOffset += imageSize.m_height;
		topWidth    -= imageSize.m_width;
		rightHeight -= rightOffset;

        // draw this element.
        r.draw(*m_toprImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Stretch);
    }

    // bottom-left image
    if (m_botlImg)
    {
        // calculate final destination area
        imageSize = m_botlImg->getPixelRect().getSize();
        finalRect.m_left = dest.m_left;
        finalRect.m_top  = dest.m_bottom - imageSize.m_height;
        finalRect.setSize(imageSize);
        finalRect = dest.getIntersection (finalRect);

		bottomOffset += imageSize.m_width;
		bottomWidth  -= bottomOffset;
		leftHeight   -= imageSize.m_height;

        // draw this element.
        r.draw(*m_botlImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Stretch);
    }

    // bottom-right image
    if (m_botrImg)
    {
        // calculate final destination area
        imageSize = m_botrImg->getPixelRect().getSize();
        finalRect.m_left = dest.m_right - imageSize.m_width;
        finalRect.m_top  = dest.m_bottom - imageSize.m_height;
        finalRect.setSize(imageSize);
        finalRect = dest.getIntersection (finalRect);

		bottomWidth -= imageSize.m_width;
		rightHeight -= imageSize.m_height;

        // draw this element.
		r.draw(*m_botrImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Stretch);        
    }

    // top image
    if (m_topImg)
    {
        // calculate final destination area
        imageSize = m_topImg->getPixelRect().getSize();
        finalRect.m_left   = dest.m_left + topOffset;
        finalRect.m_right  = finalRect.m_left + topWidth;
        finalRect.m_top    = dest.m_top;
        finalRect.m_bottom = finalRect.m_top + imageSize.m_height;
        finalRect = dest.getIntersection (finalRect);

        // adjust background area to miss this edge
        backgroundRect.m_top += imageSize.m_height;

        // draw this element.
		r.draw(*m_topImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Tile, Image::Stretch);
    }

    // bottom image
    if (m_botImg)
    {
        // calculate final destination area
        imageSize = m_botImg->getPixelRect().getSize();
        finalRect.m_left   = dest.m_left + bottomOffset;
        finalRect.m_right  = finalRect.m_left + bottomWidth;
        finalRect.m_bottom = dest.m_bottom;
        finalRect.m_top    = finalRect.m_bottom - imageSize.m_height;
        finalRect = dest.getIntersection (finalRect);

        // adjust background area to miss this edge
        backgroundRect.m_bottom -= imageSize.m_height;

        // draw this element.
		r.draw(*m_botImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Tile, Image::Stretch);
    }

    // left image
    if (m_lImg)
    {
        // calculate final destination area
        imageSize = m_lImg->getPixelRect().getSize();
        finalRect.m_left   = dest.m_left;
        finalRect.m_right  = finalRect.m_left + imageSize.m_width;
        finalRect.m_top    = dest.m_top + leftOffset;
        finalRect.m_bottom = finalRect.m_top + leftHeight;
        finalRect = dest.getIntersection (finalRect);

        // adjust background area to miss this edge
        backgroundRect.m_left += imageSize.m_width;

        // draw this element.
		r.draw(*m_lImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Tile);
    }

    // right image
    if (m_rImg)
    {
        // calculate final destination area
        imageSize = m_rImg->getPixelRect().getSize();
        finalRect.m_top    = dest.m_top + rightOffset;
        finalRect.m_bottom = finalRect.m_top + rightHeight;
        finalRect.m_right  = dest.m_right;
        finalRect.m_left   = finalRect.m_right - imageSize.m_width;
        finalRect = dest.getIntersection (finalRect);

        // adjust background area to miss this edge
        backgroundRect.m_right -= imageSize.m_width;

        // draw this element.
		r.draw(*m_rImg, finalRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Stretch, Image::Tile);
    }

    if (m_backImg)
    {
        // render background image.
		r.draw(*m_backImg, backgroundRect, 1.f, clip,  m_backColor, TopLeftToBottomRight, Image::Tile, Image::Tile);
    }
}

void Panel::init(xml::node& node)
{
	BaseWindow::init(node);

	xml::node frame = node("FrameImagery");
	if(!frame.empty())
	{
		m_imgset = m_system.getWindowManager().loadImageset(frame["Imageset"].value());
		if(m_imgset)
		{
			const Imageset& set = *m_imgset;
			m_backImg = set[frame("Background")["Image"].value()];
			m_topImg = set[frame("Top")["Image"].value()];
			m_toplImg = set[frame("TopLeft")["Image"].value()];
			m_toprImg = set[frame("TopRight")["Image"].value()];
			m_lImg = set[frame("Left")["Image"].value()];
			m_rImg = set[frame("Right")["Image"].value()];
			m_botImg = set[frame("Bottom")["Image"].value()];
			m_botlImg = set[frame("BottomLeft")["Image"].value()];
			m_botrImg = set[frame("BottomRight")["Image"].value()];
		}
	}
}

}