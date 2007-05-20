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

#include "render/particles/particlesParticle.h"
#include "math/mathRandom.h"


namespace particles{

	class IAbstractEmitter;
	class CPTank;


	class  IParticlesProcessor : public io::ISerializedObject, public core::XmlClass
	{
		// ������ ���� ����������� �� 1 ����� ������ ������������ ������� ������� ������
		static const unsigned ms_nVersion = 1004;//1003; // old - 1002

	public:
		inline void setEmitter(IAbstractEmitter* em) { m_pParentEmitter = em; }
		
		IParticlesProcessor(IAbstractEmitter* em = 0);   // �����������
		virtual ~IParticlesProcessor();

		void load();

		void render();								// ���������
		void update(float dt);						// ������
		virtual void debugDraw();					// ���������� ����������� ����������� ����������
		void reset();								// ReStart ��������� - �������� ��� ����� �� 0

	protected:
		void loadTexture();
		void initPTank();
		inline void assignChilds();					// ������������������� ����� �������� ��������� �� ������ (�����, ������..)
		inline void createParticle(Particle& p);	// �������� ����� ������� �� ��������

		virtual void geomRender();
		void fistTimeInit();
		void updateParticle(Particle& p);			// ������������� ����� ���� ���������
		void formTank();							// ���������� � agl::Particles ����� ���� ���������
		void addNewParticles(int num2add);

	protected:
		virtual void toStream(io::IWriteStream& wf) const;
		virtual void fromStream(io::IReadStream& rf);

	// ����������
	public:
		// ���������� ���������
		const math::Matrix44f& getLTM();

		// ���������� ������� �������
		void setTextureName(const std::string& texName);

		// ���������� ��������������
		inline math::FloatInterp& particleRate()				{ return m_PRate; }
		inline math::FloatInterp& particleResistance()			{ return m_PResistance; }
		inline math::FloatInterp& particleSpin()				{ return m_PSpin; }
		inline math::FloatInterp& particleSpinSpread()			{ return m_PSpinSpread; }
		inline math::FloatInterp& particleLife()				{ return m_PLife; }
		inline math::FloatInterp& particleLifeSpread()			{ return m_PLifeSpread; }
		inline math::FloatInterp& particleSize()				{ return m_PSize; }
		inline math::ColorInterp& particleColorAlpha()			{ return m_PColorAlpha; }
		inline math::Vec3Interp& particleActingForce()			{ return m_PActingForce; }
		inline math::Vec3Interp& particleVelocity()				{ return m_PVelocity; }
		inline math::Vec3Interp& particleInitialVelSpread()		{ return m_PInitialVelSpread; }
		inline math::FloatInterp& particleVelSpreadAmplifier()	{ return m_PVelSpreadAmplifier; }

		// ���������� ��������� / ������� �������
		inline bool isGlobal() const { return m_bIsGlobal; }
		inline void setGlobal(bool b) { m_bIsGlobal = b; }

		inline bool isFading() const { return m_bIsFading; }
		inline void setFade(bool b) { m_bIsFading = b; }

		inline unsigned getMaxParticles() const { return m_nMaxParticles; }
		inline void setMaxParticles (unsigned num) { 
			m_nMaxParticles = num; 
			m_Particles.resize(m_nMaxParticles);
		}

		inline int getSeed() const { return m_nMaxParticles; }
		inline void setSeed(int seed) { m_iRndSeed = seed; }

		inline bool isVisible() const { return m_bIsVisible; }
		inline void setVisible(bool visible) { m_bIsVisible = visible; }

		inline bool getIntenseMode() const { return m_bIntense; }
		inline void setIntenseMode(bool intense) { m_bIntense = intense; }

		inline bool getSparkMode() { return m_bIsSparks; }
		inline void setSparkMode(bool sm) { m_bIsSparks = sm; }


	protected:
		CPTank* m_spTank;
		render::PTexture m_pTexture;

		//////////////////////////////////////////////////////////////////////////
		// ��� ������ � ������������� ���������
		//////////////////////////////////////////////////////////////////////////
		// ���� ������������ ������������� ���� ����������� �������� 
		// ���������� ��� �������������
		bool m_bIsAnimTextureUsed;
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
		bool m_bIsTexAnimCycled;
		// �������� ��������������� ���������� ��������
		// � ������ � �������, ����� ����������� �� "��������" �������
		unsigned m_cTexFps;
		// animation m_Texture frame random shift 
		unsigned m_nRndFrame;
		// is play animation, if not - will randomize m_Texture
		bool m_bIsPlayTexAnimation;
		//////////////////////////////////////////////////////////////////////////

		IAbstractEmitter* m_pParentEmitter;

		math::UnitRandom2k  rnd;

		int m_iRndSeed;

		math::FloatInterp m_PRate;						// ����� ���������� ������ � ������� �������
		math::FloatInterp m_PResistance;				// ������ (����������)
		math::FloatInterp m_PSpin;						// ��������
		math::FloatInterp m_PSpinSpread;
		math::FloatInterp m_PLife;						// ����� ����� (Time to live, TTL)
		math::FloatInterp m_PLifeSpread;
		math::FloatInterp m_PSize;						// ������ 
		math::ColorInterp m_PColorAlpha;				// ���� � �����, 2 � 1
		math::Vec3Interp m_PActingForce;
		math::Vec3Interp m_PVelocity;					// �������� (XYZ)
		math::Vec3Interp m_PInitialVelSpread;
		math::FloatInterp m_PVelSpreadAmplifier;		// ��������� ���������� ������� ��������

		//std::string name; // ��� �������� �������������
		std::string m_TexName;

		bool m_bIsFading;								// �������� �� ��������� (���������� ��������� �� �������� ����� ������)
		bool m_bIsGlobal;								// �������� �� ��������� ���������� (�.�. �� ������� ������������ �������������)

		bool m_bIntense;								// ������ ����� ���������
		math::Vec3f m_fScaling;								// ��������������� ������������� �������
		int m_nMaxParticles;							// ������������ ����� ������ � ����������

		float m_ngkx;
		
		bool m_bIsSparks;
		bool m_bIsGeometric;
		//std::string m_DffName;
		//agl::PAtomic m_spGeom;

		TParticles m_Particles;

		bool m_bModifiersLoaded;
		bool m_bIsVisible;
		bool m_bIsTexLoaded;
		bool m_bIsPtankInited;

		float m_fNormalizedTime;		// ������������� �� 0 �� 1
		float m_fRateAccum;				// �������� ������� ����� �� rate �� ����� � �����
		float m_dt;
	};

}