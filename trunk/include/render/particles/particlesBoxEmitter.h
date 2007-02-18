/**--------------------------------------------------------------------------------------

									RGDE Engine

	-----------------------------------------------------------------------------
\author Denis V. Ovod, 2004

\author Andrew "Zlobnik" Chouprina, 2005
mail:	dxprg@mail.ru


Created:			2004 (Denis V. Ovod)
Modified for RGDE:	march-april 2005 (Zlobnik)
---------------------------------------------------------------------------------------*/
#pragma once

#include "render/particles/particlesAbstractEmitter.h"



namespace particles
{
	class  IBoxEmitter : public IAbstractEmitter
	{
	public:
		IBoxEmitter();
		virtual ~IBoxEmitter();

		virtual void getParticle(Particle& p);
		void		 debugDraw();

	protected:
		virtual void toStream(io::IWriteStream& wf) const;
		virtual void fromStream(io::IReadStream& rf);

	// ����������
	public:
		inline math::Vec3Interp& getBoxSizeInterp()			{ return m_BoxSize; }
		inline math::Vec3Interp& getBoxSizeSpreadInterp()	{ return m_BoxSizeSpread; }
		inline math::Vec3Interp& getDirectionInterp()		{ return m_Direction; }
		inline math::Vec3Interp& getDirectionSpreadInterp()	{ return m_DirectionSpread; }


	protected:
		math::Vec3Interp m_BoxSize;
		math::Vec3Interp m_BoxSizeSpread;
		math::Vec3Interp m_Direction;
		math::Vec3Interp m_DirectionSpread;
	};
}