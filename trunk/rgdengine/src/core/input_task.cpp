#include "precompiled.h"

#include <rgde/core/input_task.h>
#include <rgde/core/application.h>
#include <rgde/input/input.h> //���������� �����

#include <Windows.h>

#include "../input/inputimpl.h"

namespace core
{
    input_task::input_task(const application& app, unsigned int priority, bool exclusive) 
        : base_task(app, priority)
    {
        HWND hWnd = (HWND)application::get()->get_handle();

        input::input_impl *pImpl = new input::input_impl();
        pImpl->init(hWnd,exclusive);

        input::Input::get().init( pImpl );
    }

    input_task::~input_task ()
    {
        input::Input::destroy();
    }

    void input_task::run()
    {
        input::Input::update();
    }
}