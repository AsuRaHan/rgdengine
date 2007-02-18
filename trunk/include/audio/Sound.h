#pragma once

#include "audio.h"

class WaveFile;

// Sound represents any .wav file audio
class Sound : public Audio
{
    public:
        Sound(const char* szWaveFile);
        virtual ~Sound();

		WaveFile* GetWaveFile() { return m_pWaveFile; }

		virtual bool FillBuffer(IDirectSoundBuffer* pDSB,
								DWORD startIndex,
								DWORD amount,
								DWORD* pAmtRead = NULL);

		virtual void Reset();

    protected:
        WaveFile* m_pWaveFile;
		DWORD m_pos;
};