#pragma once

namespace rgde
{
	namespace render
	{
		namespace primitives_2d
		{
			struct line_desc
			{
				line_desc();
			};

			struct sprite_desc
			{
				sprite_desc();

				math::vec2f pos;	  // ������� �������
				math::vec2f size;     // ������� �������
				math::rect tex_coord; // ���������� ���������� �������

   				float spin;           // ���� �������� �������
 
				math::color color;

				texture_ptr texture;  // �������� �������	
			};

			// �������� ������� 2d-���������
			struct prim_vertex		
			{
				math::vec4f	pos;	
				ulong color;
				math::vec2f	tex;			
			};
		}
	}
}