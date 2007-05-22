/**--------------------------------------------------------------------------------------

									RGDE Engine

	-----------------------------------------------------------------------------
\author Denis V. Ovod, 2003

\author Andrew "Zlobnik" Chouprina, 2005
mail:	dxprg@mail.ru


Created:			1:9:2003 (Denis V. Ovod)
Modified for RGDE:	march-april 2005 (Zlobnik)
---------------------------------------------------------------------------------------*/
#pragma once

#include <rgde/render/particles/particlesEmitter.h>
#include <rgde/render/particles/particlesMayaStructs.h>
#include <rgde/render/particles/particlesParticleTank.h>


namespace particles{

	class  IMayaEmitter : public IEmitter
	{
		friend class IEffect;

		static const unsigned ms_nVersion = 1002;
	public:
		typedef std::vector<PPTank> PTanks;
		typedef PTanks::iterator PTanksIter;

		typedef std::map<std::string, PTanks> PFrames;
		typedef PFrames::iterator PFramesIter;

		static void ClearCachedData(); 

		IMayaEmitter() : IEmitter(IEmitter::Maya) {};
		IMayaEmitter( const std::string& sequence_name, const std::string texture_name);
		virtual ~IMayaEmitter();

		void render();
		void update(float dt);
		void debugDraw();

		void reset()
		{
			m_fLastFrame = 0;
			m_fLastTime = 0;
			m_bVisible = true;
			m_bIsFading = false;
		}

		inline bool isFading()		const	{return m_bIsFading;}
		inline void setFade(bool b)			{m_bIsFading = b;}

		inline int  getTimeShift()	const	{return m_fTimeShift;}
		inline void setTimeShift(int t)		{m_fTimeShift = t;}		

		inline bool isVisible()		const	{return m_bVisible;}
		inline void	setVisible(bool b)		{m_bVisible = b;}
		
		inline bool	isCycling()		const	{return m_bCycling;}
		inline void	setCycling(bool b)		{m_bCycling = b;}
		
		void		setIntense(bool intense);
		inline bool	getIntense()	const	{return m_bIntense;}

		inline std::string getTextureName() const {return m_TexName;}
		void setTexture(std::string tex);

	protected:
		void loadTexture();
		void loadFrames(std::string file_name);
		void render(unsigned int frame_num);

		virtual void toStream(io::IWriteStream& wf) const;
		virtual void fromStream(io::IReadStream& rf);

	protected:
		render::PTexture	m_pTexture;
		PTanks*				m_Frames;
		
		static PFrames ms_PFrames;
		static std::map<std::string, MayaStructs::SFrameSequence> m_FrSeq;

		// state flags
		bool		m_bIsSeqLoaded;
		bool		m_bIsTexLoaded;

		bool		m_bVisible;						// ����� �� ������
		bool		m_bCycling;						// �������� �� �� 

		float		m_fScale;
		
		std::string m_Name;							// ��� ����� � �������
		std::string m_TexName;
		
		// ��� ������ � ������������� ���������
		bool			m_bIsAnimTextureUsed;			
		unsigned char	m_ucCol;					// ���-�� �������
		unsigned char	m_ucRow;					// ���-�� �����
		unsigned char	m_ucTexFrames;				// ���-�� ������
		unsigned char	m_ucTcol;					// ���-�� �������
		char			m_cTexFps;
		unsigned char	m_ucTrow;					// ���-�� �����

		float			m_fLastTime;				// ����� ����� ��� ��������� ��������� ����
		float			m_fLastFrame;				// ��������� ������������ ����
		int				m_fTimeShift;				// �������� � ������ �� ���������� ����� ������������
		bool			m_bIntense;
		bool			m_bIsFading;
	};
}