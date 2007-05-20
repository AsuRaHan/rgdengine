#pragma once

#include <vector>

#include "io/io.h"

//////////////////////////////////////////////////////////////////////////
namespace particles{
namespace MayaStructs{
//////////////////////////////////////////////////////////////////////////
struct SMayaParticle
{
	float x,y,z;
	float r,g,b,a;
	float scale;
	float spin;

	// ����� �������� (��� ����� � ������������� ������������������)
	int  tex_num;

	void ReScale(float _scale)
	{
		x *= _scale;
		y *= _scale;
		z *= _scale;
		scale *= _scale;
	}

	void Save(io::IWriteStream& out, float _scale = 1.0f)
	{
		out << x * _scale << y * _scale << z * _scale
			<< r << g << b << a 
			<< scale * _scale
			<< spin
			<< tex_num;
	}

	void Load(io::IReadStream& in)
	{
		in	>> x >> y >> z
			>> r >> g >> b >> a 
			>> scale
			>> spin
			>> tex_num;
	}

};
//////////////////////////////////////////////////////////////////////////
struct SFrame
{	
	unsigned int frame_number;
	unsigned int number_of_particles;
	std::vector<SMayaParticle> particles;

	void ReScale(float scale)
	{
		for(unsigned int i = 0; i < number_of_particles; ++i)
			particles[i].ReScale(scale);
	}

	void Save(io::IWriteStream& out, float scale = 1.0f)
	{
		out << frame_number
			<< number_of_particles;

		for(unsigned int i = 0; i < number_of_particles; ++i)
			particles[i].Save(out, scale);
	}

	void Load(io::IReadStream& in)
	{
		in  >> frame_number
			>> number_of_particles;

		for(unsigned int i = 0; i < number_of_particles; ++i)
		{
			SMayaParticle p; 
			p.Load(in);
			particles.push_back(p);
		}
	}
};

struct SFrameSequence
{
	virtual ~SFrameSequence(){}
	// ������������ ���� ���� ������ ������ �������
	bool isAnimatedTex;
	// ������-�� ��� ���� �� ���� ��� ���� :)
	float time_scale;
	// ������������ ���-�� ������ � 1-� �����
	unsigned int max_particles_number;
	// ������� ���-�� ������ � 1� �����, ��� ����������� ������
	// ������� ������ � ������
	unsigned int average_particles_number;
	// ������ ���� �������	
	std::vector<SFrame> frames;

	void ReScale(float scale)
	{
		for (unsigned int i = 0; i < frames.size(); ++i)
			frames[i].ReScale(scale);
	}

	void Save(io::IWriteStream& out, float scale = 1.0f)
	{
		char ver = 1; // ������

		time_scale = 1;
		max_particles_number = 180;
		average_particles_number = 70;

		out << ver
			<< isAnimatedTex
			<< time_scale
			<< max_particles_number
			<< average_particles_number
			<< (unsigned int)frames.size();

		for (unsigned int i = 0; i < frames.size(); ++i)
			frames[i].Save(out, scale);
	}

	bool Load(io::IReadStream& in)
	{
		try{
			char ver;
			in >> ver;
			if (ver != 1) return false;

			in	>> isAnimatedTex
				>> time_scale
				>> max_particles_number
				>> average_particles_number;

			unsigned int frame_num;
			in >> frame_num;

			for (unsigned int i = 0; i < frame_num; ++i)
			{
				SFrame f; 
				f.Load(in);
				frames.push_back(f);
			}
			return true;
		}
		catch (...) {
			return false;
		}
	}
};
//////////////////////////////////////////////////////////////////////////
}	// namespace MayaStructs;
}	// namespace pfx;