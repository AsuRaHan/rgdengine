#include "stdafx.h"

#include <engine/render/device_object.h>

namespace rgde
{
	namespace render
	{
		unsigned int device_object::ms_num_objects;

		device_object::device_object(device& dev, bool register_on_lost_reset)
			: m_is_registered(register_on_lost_reset), m_device(dev)
		{
			++ms_num_objects;
		}

		device_object::~device_object()
		{
			--ms_num_objects;
		}

		size_t device_object::get_objects_num()
		{
			return ms_num_objects;
		}

	}
}