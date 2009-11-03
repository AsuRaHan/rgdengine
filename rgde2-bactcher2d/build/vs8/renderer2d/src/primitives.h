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

			// ���������� ������� 2d-���������
			vertex_element prim_vertex_desc[] = 
			{
				{0, 0,  vertex_element::float4, vertex_element::default_method, vertex_element::positiont, 0},
				{0, 16, vertex_element::color4ub, vertex_element::default_method, vertex_element::color, 0},
				{0, 20, vertex_element::float2,	vertex_element::default_method, vertex_element::texcoord, 0},
				vertex_element::end_element
			};
		}
	}
}