/**--------------------------------------------------------------------------------------

									RGDE Engine

-----------------------------------------------------------------------------------------
\author Denis V. Ovod, 2003

\author Andrew "Zlobnik" Chouprina, 2005
mail:	dxprg@mail.ru


Created:			17:9:2003 (Denis V. Ovod)
Modified for RGDE:	march-april 2005 (Zlobnik)
---------------------------------------------------------------------------------------*/
#pragma once

#include "render/particles/particlesAbstractEmitter.h"


namespace particles{

	class  ISphericalEmitter : public IAbstractEmitter
	{
	public: 
		ISphericalEmitter();
		virtual ~ISphericalEmitter();

		void		 debugDraw();
		virtual void getParticle(Particle& p);
	
	protected:
		virtual void toStream(io::IWriteStream& wf) const;
		virtual void fromStream(io::IReadStream& rf);

	// ����������
	public:
		inline math::FloatInterp& getRadiusInterp()			{ return m_Radius; }
		inline math::FloatInterp& getRadiusSpreadInterp()	{ return m_RadiusSpread; }
		inline math::FloatInterp& getAngleInterp()			{ return m_Angle; }


	protected:
		math::FloatInterp m_Radius;				// ������
		math::FloatInterp m_RadiusSpread;		// ������� �������
		math::FloatInterp m_Angle;				// ���� 
	};
}