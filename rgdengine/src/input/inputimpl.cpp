#include "precompiled.h"

#include <rgde/input/device.h>
#include <rgde/input/control.h>
#include <rgde/input/command.h>
#include "inputimpl.h"

#define KEYBOARD_BUFFER_SIZE 1024
#define    MOUSE_BUFFER_SIZE 1024

//#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")

namespace input
{
    input_impl::input_impl ():
        m_bInit     (false), //�������, ��� ������� ����� �� �����������������
        m_pDI       (NULL),  //���������� DInput
        m_pKeyboard (NULL),  //���������� ����� "����������"
        m_pMouse    (NULL),  //���������� ����� "����"
        keyboard    (NULL),
        mouse       (NULL)
    {
    }

    input_impl::~input_impl ()
    {
        if (m_bInit)
            Done();
    }
 
    /////////////////////////////////////////////////
    // �������� ������ ��� ������ � �������� ����� //
    /////////////////////////////////////////////////

    //�������� ����� ������ ��������� �����
    bool input_impl::SetMode (bool exclusive/*=false*/, bool foreground/*=true*/)
    {
        if (!m_bInit)
            return false;

        //����� ������ ����������� � ����������� �����
        doneDXInput();

        //��������� ����������� � ����������� ����� � ������ �����������
        if (!initDXInput(m_hWnd,exclusive,foreground))
        {
            //���� �� �������, �� ����������� �� ������� �����������
            initDXInput(m_hWnd,m_exclusive,m_foreground);
            return false;
        }

        return true;
    }

    //������������������� ������� �����
    bool input_impl::Init (HWND hWnd, bool exclusive/*=false*/, bool foreground/*=true*/)
    {
        if (m_bInit)
            Done();

        //�������������� DXInput
        m_bInit = initDXInput (hWnd,exclusive,foreground);
        if (!m_bInit)
            return false;

        //�������� ������ m_devices
        m_devices.push_back (new Device(types::Keyboard, 0, *this));
        m_devices.push_back (new Device(types::Mouse,    0, *this));

        //�������� ������ ���������
        keyboard = *(m_devices.begin());
        mouse    = *(++m_devices.begin());

        //keyboard
        keyboard->addButton(types::KeyEscape);
        keyboard->addButton(types::Key1);
        keyboard->addButton(types::Key2);
        keyboard->addButton(types::Key3);
        keyboard->addButton(types::Key4);
        keyboard->addButton(types::Key5);
        keyboard->addButton(types::Key6);
        keyboard->addButton(types::Key7);
        keyboard->addButton(types::Key8);
        keyboard->addButton(types::Key9);
        keyboard->addButton(types::Key0);
        keyboard->addButton(types::KeyMinus);
        keyboard->addButton(types::KeyEquals);
        keyboard->addButton(types::KeyBack);
        keyboard->addButton(types::KeyTab);
        keyboard->addButton(types::KeyQ);
        keyboard->addButton(types::KeyW);
        keyboard->addButton(types::KeyE);
        keyboard->addButton(types::KeyR);
        keyboard->addButton(types::KeyT);
        keyboard->addButton(types::KeyY);
        keyboard->addButton(types::KeyU);
        keyboard->addButton(types::KeyI);
        keyboard->addButton(types::KeyO);
        keyboard->addButton(types::KeyP);
        keyboard->addButton(types::KeyLBracket);
        keyboard->addButton(types::KeyRBracket);
        keyboard->addButton(types::KeyReturn);
        keyboard->addButton(types::KeyLControl);
        keyboard->addButton(types::KeyA);
        keyboard->addButton(types::KeyS);
        keyboard->addButton(types::KeyD);
        keyboard->addButton(types::KeyF);
        keyboard->addButton(types::KeyG);
        keyboard->addButton(types::KeyH);
        keyboard->addButton(types::KeyJ);
        keyboard->addButton(types::KeyK);
        keyboard->addButton(types::KeyL);
        keyboard->addButton(types::KeySemicolon);
        keyboard->addButton(types::KeyApostrophe);
        keyboard->addButton(types::KeyGrave);
        keyboard->addButton(types::KeyLShift);
        keyboard->addButton(types::KeyBackSlash);
        keyboard->addButton(types::KeyZ);
        keyboard->addButton(types::KeyX);
        keyboard->addButton(types::KeyC);
        keyboard->addButton(types::KeyV);
        keyboard->addButton(types::KeyB);
        keyboard->addButton(types::KeyN);
        keyboard->addButton(types::KeyM);
        keyboard->addButton(types::KeyComma);
        keyboard->addButton(types::KeyPeriod);
        keyboard->addButton(types::KeySlash);
        keyboard->addButton(types::KeyRShift);
        keyboard->addButton(types::KeyMultiply);
        keyboard->addButton(types::KeyLMenu);
        keyboard->addButton(types::KeySpace);
        keyboard->addButton(types::KeyCapital);
        keyboard->addButton(types::KeyF1);
        keyboard->addButton(types::KeyF2);
        keyboard->addButton(types::KeyF3);
        keyboard->addButton(types::KeyF4);
        keyboard->addButton(types::KeyF5);
        keyboard->addButton(types::KeyF6);
        keyboard->addButton(types::KeyF7);
        keyboard->addButton(types::KeyF8);
        keyboard->addButton(types::KeyF9);
        keyboard->addButton(types::KeyF10);
        keyboard->addButton(types::KeyNumLock);
        keyboard->addButton(types::KeyScroll);
        keyboard->addButton(types::KeyNumPad7);
        keyboard->addButton(types::KeyNumPad8);
        keyboard->addButton(types::KeyNumPad9);
        keyboard->addButton(types::KeySubtract);
        keyboard->addButton(types::KeyNumPad4);
        keyboard->addButton(types::KeyNumPad5);
        keyboard->addButton(types::KeyNumPad6);
        keyboard->addButton(types::KeyAdd);
        keyboard->addButton(types::KeyNumPad1);
        keyboard->addButton(types::KeyNumPad2);
        keyboard->addButton(types::KeyNumPad3);
        keyboard->addButton(types::KeyNumPad0);
        keyboard->addButton(types::KeyDecimal);
        keyboard->addButton(types::KeyOEM_102);
        keyboard->addButton(types::KeyF11);
        keyboard->addButton(types::KeyF12);
        keyboard->addButton(types::KeyF13);
        keyboard->addButton(types::KeyF14);
        keyboard->addButton(types::KeyF15);
        keyboard->addButton(types::KeyKana);
        keyboard->addButton(types::KeyABNT_C1);
        keyboard->addButton(types::KeyConvert);
        keyboard->addButton(types::KeyNoConvert);
        keyboard->addButton(types::KeyYen);
        keyboard->addButton(types::KeyABNT_C2);
        keyboard->addButton(types::KeyNumPadEquals);
        keyboard->addButton(types::KeyPrevTrack);
        keyboard->addButton(types::KeyAt);
        keyboard->addButton(types::KeyColon);
        keyboard->addButton(types::KeyUnderLine);
        keyboard->addButton(types::KeyKANJI);
        keyboard->addButton(types::KeyStop);
        keyboard->addButton(types::KeyAx);
        keyboard->addButton(types::KeyUnlabeled);
        keyboard->addButton(types::KeyNextTrack);
        keyboard->addButton(types::KeyNumPadEnter);
        keyboard->addButton(types::KeyRControl);
        keyboard->addButton(types::KeyMute);
        keyboard->addButton(types::KeyCalculator);
        keyboard->addButton(types::KeyPlayPause);
        keyboard->addButton(types::KeyMediaStop);
        keyboard->addButton(types::KeyVolumeDown);
        keyboard->addButton(types::KeyVolumeUp);
        keyboard->addButton(types::KeyWebHome);
        keyboard->addButton(types::KeyNumPadComma);
        keyboard->addButton(types::KeyDivide);
        keyboard->addButton(types::KeySysRQ);
        keyboard->addButton(types::KeyRMenu);
        keyboard->addButton(types::KeyPause);
        keyboard->addButton(types::KeyHome);
        keyboard->addButton(types::KeyUp);
        keyboard->addButton(types::KeyPrior);
        keyboard->addButton(types::KeyLeft);
        keyboard->addButton(types::KeyRight);
        keyboard->addButton(types::KeyEnd);
        keyboard->addButton(types::KeyDown);
        keyboard->addButton(types::KeyNext);
        keyboard->addButton(types::KeyInsert);
        keyboard->addButton(types::KeyDelete);
        keyboard->addButton(types::KeyLWin);
        keyboard->addButton(types::KeyRWin);
        keyboard->addButton(types::KeyApps);
							
        //mouse
        mouse->addButton (types::ButtonLeft);
        mouse->addButton (types::ButtonMid);
        mouse->addButton (types::ButtonRight);
        mouse->addAxis   (types::AxisX);
        mouse->addAxis   (types::AxisY);
        mouse->addAxis   (types::AxisWheel);

        return true;
    }

    //��������� ���������
    void input_impl::Load (const std::string &sXml)
    {
        if (!m_bInit)
            return;

		TiXmlDocument doc;
		doc.Parse(sXml.c_str());
		
		TiXmlNode *root = doc.FirstChild("input");
		if (root)
		{
			TiXmlNode *command = root->FirstChild("command");
			while (command)
			{
				TiXmlElement *cmd = command->ToElement();
				if (cmd)
				{
					std::string sCommandName(cmd->Attribute("name"));
					addCommand(std::wstring(sCommandName.begin(), sCommandName.end()));

					TiXmlNode *control = command->FirstChild("control");
					while (control)
					{
						TiXmlElement *ctrl = control->ToElement();
						if (ctrl)
						{
							std::string sDevice(ctrl->Attribute("device"));
							std::string sControl(ctrl->Attribute("name"));
							Device *d = getDevice(String2Device(std::wstring(sDevice.begin(), sDevice.end())));
							if (d)
							{
								Control *c = d->get_control(String2Control(std::wstring(sControl.begin(), sControl.end())));
								if (c)
									c->bind(getCommand(std::wstring(sCommandName.begin(), sCommandName.end())));
							}
						}

						control = control->NextSibling("control");
					}
				}

				command = command->NextSibling("command");
			}
		}
    }

    //������� �� ������ ��� ������� �� ��������� �����
    void input_impl::update ()
    {
        if (!m_bInit)
            return;

        static DIDEVICEOBJECTDATA kbuf [KEYBOARD_BUFFER_SIZE]; //����� ��� ������������ �������
        static DIDEVICEOBJECTDATA mbuf [   MOUSE_BUFFER_SIZE]; //����� ��� ������� �� ����
        DWORD                     kElements;                   //���-�� ������������ �������
        DWORD                     mElements;                   //���-�� ������� �� ����
        HRESULT                   hr;

        //������� ��������� �� ����������
        kElements = KEYBOARD_BUFFER_SIZE;
        hr = m_pKeyboard->GetDeviceData (sizeof(DIDEVICEOBJECTDATA), kbuf, &kElements, 0);
        if (hr != DI_OK) 
        {
            if (hr == DI_BUFFEROVERFLOW)
                ; //... keyboard buffer overflow
            else
                kElements = 0;
            hr = m_pKeyboard->Acquire();
            while (hr == DIERR_INPUTLOST) 
                hr = m_pKeyboard->Acquire();
        }

        //������� ��������� �� ����
        mElements = MOUSE_BUFFER_SIZE;
        hr = m_pMouse->GetDeviceData (sizeof(DIDEVICEOBJECTDATA), mbuf, &mElements, 0);
        if (hr != DI_OK) 
        {
            if (hr == DI_BUFFEROVERFLOW)
                ; //... mouse buffer overflow
            else
                mElements = 0;
            hr = m_pMouse->Acquire();
            while (hr == DIERR_INPUTLOST) 
                hr = m_pMouse->Acquire();
        }

        //���������� ��������� �� ��������� ����� � ������� �� �������������
        unsigned int k = 0,
            m = 0;
        while (!(k>=kElements && m>=mElements))
            if (k<kElements && m<mElements)
            {
                if (DISEQUENCE_COMPARE(kbuf[k].dwSequence,<=,mbuf[m].dwSequence))
                    kProcess(kbuf[k++]);
                else
                    mProcess(mbuf[m++]);
            }
            else
            {
                if (k<kElements)
                    kProcess(kbuf[k++]);
                else
                    mProcess(mbuf[m++]);
            }
    }

    //��������� ���������
    void input_impl::Save (std::string &sXml)
    {
        if (!m_bInit)
            return;

        TiXmlDocument doc;
        TiXmlElement *input = (TiXmlElement*)(doc.InsertEndChild(TiXmlElement("input")));

        std::list<CommandPtr>::iterator i = m_commands.begin();
        while (i != m_commands.end())
        {
            CommandPtr pCommand = *i;

            TiXmlElement *command = (TiXmlElement*)(input->InsertEndChild(TiXmlElement("command")));
            std::wstring sCommandNameW = pCommand->getName();
            std::string sCommandName(sCommandNameW.begin(), sCommandNameW.end());
            command->SetAttribute("name", sCommandName.c_str());

            std::list<Device*>::iterator j = m_devices.begin();
            while (j != m_devices.end())
            {
                Device *pDevice = *j;

                std::wstring sDeviseNameW = Device2String(pDevice->getName());
                std::string sDeviceName(sDeviseNameW.begin(), sDeviseNameW.end());

				std::map<types::EControl, Control*>::iterator k = pDevice->m_controls.begin();
                while (k != pDevice->m_controls.end())
                {
                    Control *pControl = k->second;
                    if (pControl->isbind(pCommand))
                    {
                        std::wstring sControlNameW = Control2String(pControl->getName());
                        std::string sControlName(sControlNameW.begin(), sControlNameW.end());

                        TiXmlElement *control = (TiXmlElement*)(command->InsertEndChild(TiXmlElement("control")));
                        control->SetAttribute("device", sDeviceName.c_str());
                        control->SetAttribute("name", sControlName.c_str());
                    }
                    ++k;
                }
                ++j;
            }
            ++i;
        }

        std::stringstream ss;
        ss << doc;
        sXml = ss.str();
    }

    //��������� ������ ������� �����
    void input_impl::Done ()
    {
        if (!m_bInit)
            return;

        doneDXInput ();
        m_commands.clear();

        while (!m_devices.empty())
        {
            delete *(m_devices.begin());
            m_devices.erase(m_devices.begin());
        }

        keyboard = NULL;
        mouse    = NULL;

        m_bInit = false;
    }
 
    ////////////////////////////////
    // ������ � ����������� ����� //
    ////////////////////////////////

    //�������� ����������
    Device* input_impl::getDevice (types::EDevice eDeviceName, int indx/*=0*/)
    {
        if (!m_bInit)
            return 0;

        std::list<Device*>::iterator i = m_devices.begin();
        while (i != m_devices.end())
        {
            if ((*i)->getName() == eDeviceName && (*i)->getIndx() == indx)
                return *i;
            ++i;
        }

        return 0;
    }

    Device* input_impl::getDevice (const std::wstring &sDeviceName, int indx/*=0*/)
    {
        return getDevice(String2Device(sDeviceName), indx);
    }

    //���� �� ����� ����������
    bool input_impl::isDevicePresent (types::EDevice eDeviceName, int indx/*=0*/) const
    {
        if (!m_bInit)
            return false;

        std::list<Device*>::const_iterator i = m_devices.begin();
        while (i != m_devices.end())
        {
            if ((*i)->getName() == eDeviceName && (*i)->getIndx() == indx)
                return true;
            ++i;
        }

        return false;
    }

    bool input_impl::isDevicePresent (const std::wstring &sDeviceName, int indx/*=0*/) const
    {
        return isDevicePresent(String2Device(sDeviceName), indx);
    }
 
    /////////////////////////////////////
    // ������ � �������� ������� ����� //
    /////////////////////////////////////

    //�������� �������
    CommandPtr input_impl::addCommand (const std::wstring &command_name)
    {
        if (m_bInit && !isCommandPresent(command_name))
        {
            CommandPtr command(new Command(command_name, *this));
            m_commands.push_back(command);
			return command;
        }

		return CommandPtr();
    }

    //�������� �������
    CommandPtr input_impl::getCommand (const std::wstring &sCommandName)
    {
        if (!m_bInit)
            return CommandPtr();

        std::list<CommandPtr>::iterator i = m_commands.begin();
        while (i != m_commands.end())
        {
            if ((*i)->getName() == sCommandName)
                return (*i);
            ++i;
        }

        return CommandPtr();
    }

    //���� �� ����� �������
    bool input_impl::isCommandPresent (const std::wstring &sCommandName) const
    {
        if (!m_bInit)
            return false;

        std::list<CommandPtr>::const_iterator i = m_commands.begin();
        while (i != m_commands.end())
        {
            if ((*i)->getName() == sCommandName)
                return true;
            ++i;
        }

        return false;
    }

    //�������� ������� ��� ���� ���������
    void input_impl::detachCommand (CommandPtr pCommand)
    {
        if (!m_bInit)
            return;

        std::list<Device*>::iterator i = m_devices.begin();

        while (i != m_devices.end())
        {
            (*i)->detachCommand(pCommand);
            ++i;
        }
    }

    //������������� DXInput
    bool input_impl::initDXInput (HWND hWnd, bool exclusive, bool foreground)
    {
        //�������� ���� �������� ������
        {
            HWND cur = hWnd;
            for(;;)
            {
                HWND temp_hwnd = GetParent(cur);
                if (temp_hwnd == NULL) 
                {
                    hWnd = cur;
                    break;
                }
                cur = temp_hwnd;
            }
        }

        DWORD test = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;

        DWORD flags = 0;
        flags |= exclusive  ? DISCL_EXCLUSIVE  : DISCL_NONEXCLUSIVE;
        flags |= foreground ? DISCL_FOREGROUND : DISCL_BACKGROUND;

        HRESULT     hr;     //��������� ������/������
        DIPROPDWORD dipdw;  //��� ������� ��������������� ����� ���������� � ����

        m_pDI       = NULL; //���������� DInput
        m_pKeyboard = NULL; //���������� ����� "����������"
        m_pMouse    = NULL; //���������� ����� "����"

        ///////////////////////////
        // ������� ������ DInput //
        ///////////////////////////
        if
        (
            FAILED
            (
                hr = DirectInput8Create
                (
                    GetModuleHandle(NULL),
                    DIRECTINPUT_VERSION,
                    IID_IDirectInput8,
                    (VOID**)&m_pDI,
                    NULL
                )
            )
        )
        {
            doneDXInput(); //assert(0);
            return false; //... can't create DInput object
        }

        ///////////////////////////////////////////
        // ������� ���������� ����� "����������" //
        ///////////////////////////////////////////
        if (FAILED (hr = m_pDI->CreateDevice (GUID_SysKeyboard, &m_pKeyboard, NULL)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't create keyboard device
        }

        //������������� ������ ������ ��� ���������� ����� "����������"
        if (FAILED (hr = m_pKeyboard->SetDataFormat (&c_dfDIKeyboard)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set data format for keyboard device
        }

        //������������� ������ ������� � ����������
        if (FAILED (hr = m_pKeyboard->SetCooperativeLevel (hWnd, flags)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set cooperative level for keyboard device
        }

        //������ �������������� ������ � ����������
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dipdw.diph.dwObj        = 0;
        dipdw.diph.dwHow        = DIPH_DEVICE;
        dipdw.dwData            = KEYBOARD_BUFFER_SIZE;

        if (FAILED (hr = m_pKeyboard->SetProperty (DIPROP_BUFFERSIZE, &dipdw.diph)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set buffered device data for keyboard device
        }

        //����������� ����������
        m_pKeyboard->Acquire();

        /////////////////////////////////////
        // ������� ���������� ����� "����" //
        /////////////////////////////////////
        if (FAILED (hr = m_pDI->CreateDevice (GUID_SysMouse, &m_pMouse, NULL)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't create mouse device
        }

        //������������� ������ ������ ��� ���������� ����� "����"
        if (FAILED (hr = m_pMouse->SetDataFormat (&c_dfDIMouse2)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set data format for mouse device
        }

        //������������� ������ ������� � ����
        if (FAILED (hr = m_pMouse->SetCooperativeLevel (hWnd,flags)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set cooperative level for mouse device
        }

        //������ �������������� ������ � ����
        dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
        dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        dipdw.diph.dwObj        = 0;
        dipdw.diph.dwHow        = DIPH_DEVICE;
        dipdw.dwData            = MOUSE_BUFFER_SIZE;

        if (FAILED (hr = m_pMouse->SetProperty (DIPROP_BUFFERSIZE, &dipdw.diph)))
        {
            doneDXInput(); //assert(0);
            return false; //... can't set buffered device data for mouse device
        }

        //����������� ����
        m_pMouse->Acquire();

        //�������� ��������� �������������
        m_hWnd = hWnd;
        m_exclusive = exclusive;
        m_foreground = foreground;

        return true;
    }

    //��������������� DXInput
    void input_impl::doneDXInput()
    {
        if (m_pMouse)    m_pMouse   ->Unacquire();
        if (m_pKeyboard) m_pKeyboard->Unacquire();

        if (m_pMouse)    m_pMouse   ->Release();
        if (m_pKeyboard) m_pKeyboard->Release();
        if (m_pDI)       m_pDI      ->Release();

        m_pMouse    = NULL; //���������� ����� "����"
        m_pKeyboard = NULL; //���������� ����� "����������"
        m_pDI       = NULL; //���������� DInput
    }

    //��������� ������������ �������
    void input_impl::kProcess (DIDEVICEOBJECTDATA dod)
    {
		//���������, �� ������ �������� ������ ���������
		types::EControl eControl = types::InvalidControl;
		switch (dod.dwOfs)
		{
		    case DIK_ESCAPE       : eControl = types::KeyEscape	; break;
		    case DIK_1            : eControl = types::Key1		; break;
		    case DIK_2            : eControl = types::Key2		; break;
		    case DIK_3            : eControl = types::Key3		; break;
		    case DIK_4            : eControl = types::Key4		; break;
		    case DIK_5            : eControl = types::Key5		; break;
		    case DIK_6            : eControl = types::Key6            ; break;
		    case DIK_7            : eControl = types::Key7            ; break;
		    case DIK_8            : eControl = types::Key8            ; break;
		    case DIK_9            : eControl = types::Key9            ; break;
		    case DIK_0            : eControl = types::Key0            ; break;
		    case DIK_MINUS        : eControl = types::KeyMinus        ; break;
		    case DIK_EQUALS       : eControl = types::KeyEquals       ; break;
		    case DIK_BACK         : eControl = types::KeyBack         ; break;
		    case DIK_TAB          : eControl = types::KeyTab          ; break;
		    case DIK_Q            : eControl = types::KeyQ            ; break;
		    case DIK_W            : eControl = types::KeyW            ; break;
		    case DIK_E            : eControl = types::KeyE            ; break;
		    case DIK_R            : eControl = types::KeyR            ; break;
		    case DIK_T            : eControl = types::KeyT            ; break;
		    case DIK_Y            : eControl = types::KeyY            ; break;
		    case DIK_U            : eControl = types::KeyU            ; break;
		    case DIK_I            : eControl = types::KeyI            ; break;
		    case DIK_O            : eControl = types::KeyO            ; break;
		    case DIK_P            : eControl = types::KeyP            ; break;
		    case DIK_LBRACKET     : eControl = types::KeyLBracket     ; break;
		    case DIK_RBRACKET     : eControl = types::KeyRBracket     ; break;
		    case DIK_RETURN       : eControl = types::KeyReturn       ; break;
		    case DIK_LCONTROL     : eControl = types::KeyLControl     ; break;
		    case DIK_A            : eControl = types::KeyA            ; break;
		    case DIK_S            : eControl = types::KeyS            ; break;
		    case DIK_D            : eControl = types::KeyD            ; break;
		    case DIK_F            : eControl = types::KeyF            ; break;
		    case DIK_G            : eControl = types::KeyG            ; break;
		    case DIK_H            : eControl = types::KeyH            ; break;
		    case DIK_J            : eControl = types::KeyJ            ; break;
		    case DIK_K            : eControl = types::KeyK            ; break;
		    case DIK_L            : eControl = types::KeyL            ; break;
		    case DIK_SEMICOLON    : eControl = types::KeySemicolon    ; break;
		    case DIK_APOSTROPHE   : eControl = types::KeyApostrophe   ; break;
		    case DIK_GRAVE        : eControl = types::KeyGrave        ; break;
		    case DIK_LSHIFT       : eControl = types::KeyLShift       ; break;
		    case DIK_BACKSLASH    : eControl = types::KeyBackSlash    ; break;
		    case DIK_Z            : eControl = types::KeyZ            ; break;
		    case DIK_X            : eControl = types::KeyX            ; break;
		    case DIK_C            : eControl = types::KeyC            ; break;
		    case DIK_V            : eControl = types::KeyV            ; break;
		    case DIK_B            : eControl = types::KeyB            ; break;
		    case DIK_N            : eControl = types::KeyN            ; break;
		    case DIK_M            : eControl = types::KeyM            ; break;
		    case DIK_COMMA        : eControl = types::KeyComma        ; break;
		    case DIK_PERIOD       : eControl = types::KeyPeriod       ; break;
		    case DIK_SLASH        : eControl = types::KeySlash        ; break;
		    case DIK_RSHIFT       : eControl = types::KeyRShift       ; break;
		    case DIK_MULTIPLY     : eControl = types::KeyMultiply     ; break;
		    case DIK_LMENU        : eControl = types::KeyLMenu        ; break;
		    case DIK_SPACE        : eControl = types::KeySpace        ; break;
		    case DIK_CAPITAL      : eControl = types::KeyCapital      ; break;
		    case DIK_F1           : eControl = types::KeyF1           ; break;
		    case DIK_F2           : eControl = types::KeyF2           ; break;
		    case DIK_F3           : eControl = types::KeyF3           ; break;
		    case DIK_F4           : eControl = types::KeyF4           ; break;
		    case DIK_F5           : eControl = types::KeyF5           ; break;
		    case DIK_F6           : eControl = types::KeyF6           ; break;
		    case DIK_F7           : eControl = types::KeyF7           ; break;
		    case DIK_F8           : eControl = types::KeyF8           ; break;
		    case DIK_F9           : eControl = types::KeyF9           ; break;
		    case DIK_F10          : eControl = types::KeyF10          ; break;
		    case DIK_NUMLOCK      : eControl = types::KeyNumLock      ; break;
		    case DIK_SCROLL       : eControl = types::KeyScroll       ; break;
		    case DIK_NUMPAD7      : eControl = types::KeyNumPad7      ; break;
		    case DIK_NUMPAD8      : eControl = types::KeyNumPad8      ; break;
		    case DIK_NUMPAD9      : eControl = types::KeyNumPad9      ; break;
		    case DIK_SUBTRACT     : eControl = types::KeySubtract     ; break;
		    case DIK_NUMPAD4      : eControl = types::KeyNumPad4      ; break;
		    case DIK_NUMPAD5      : eControl = types::KeyNumPad5      ; break;
		    case DIK_NUMPAD6      : eControl = types::KeyNumPad6      ; break;
		    case DIK_ADD          : eControl = types::KeyAdd          ; break;
		    case DIK_NUMPAD1      : eControl = types::KeyNumPad1      ; break;
		    case DIK_NUMPAD2      : eControl = types::KeyNumPad2      ; break;
		    case DIK_NUMPAD3      : eControl = types::KeyNumPad3      ; break;
		    case DIK_NUMPAD0      : eControl = types::KeyNumPad0      ; break;
		    case DIK_DECIMAL      : eControl = types::KeyDecimal      ; break;
		    case DIK_OEM_102      : eControl = types::KeyOEM_102      ; break;
		    case DIK_F11          : eControl = types::KeyF11          ; break;
		    case DIK_F12          : eControl = types::KeyF12          ; break;
		    case DIK_F13          : eControl = types::KeyF13          ; break;
		    case DIK_F14          : eControl = types::KeyF14          ; break;
		    case DIK_F15          : eControl = types::KeyF15          ; break;
		    case DIK_KANA         : eControl = types::KeyKana         ; break;
		    case DIK_ABNT_C1      : eControl = types::KeyABNT_C1      ; break;
		    case DIK_CONVERT      : eControl = types::KeyConvert      ; break;
		    case DIK_NOCONVERT    : eControl = types::KeyNoConvert    ; break;
		    case DIK_YEN          : eControl = types::KeyYen          ; break;
		    case DIK_ABNT_C2      : eControl = types::KeyABNT_C2      ; break;
		    case DIK_NUMPADEQUALS : eControl = types::KeyNumPadEquals ; break;
		    case DIK_PREVTRACK    : eControl = types::KeyPrevTrack    ; break;
		    case DIK_AT           : eControl = types::KeyAt           ; break;
		    case DIK_COLON        : eControl = types::KeyColon        ; break;
		    case DIK_UNDERLINE    : eControl = types::KeyUnderLine    ; break;
		    case DIK_KANJI        : eControl = types::KeyKANJI        ; break;
		    case DIK_STOP         : eControl = types::KeyStop         ; break;
		    case DIK_AX           : eControl = types::KeyAx           ; break;
		    case DIK_UNLABELED    : eControl = types::KeyUnlabeled    ; break;
		    case DIK_NEXTTRACK    : eControl = types::KeyNextTrack    ; break;
		    case DIK_NUMPADENTER  : eControl = types::KeyNumPadEnter  ; break;
		    case DIK_RCONTROL     : eControl = types::KeyRControl     ; break;
		    case DIK_MUTE         : eControl = types::KeyMute         ; break;
		    case DIK_CALCULATOR   : eControl = types::KeyCalculator   ; break;
		    case DIK_PLAYPAUSE    : eControl = types::KeyPlayPause    ; break;
		    case DIK_MEDIASTOP    : eControl = types::KeyMediaStop    ; break;
		    case DIK_VOLUMEDOWN   : eControl = types::KeyVolumeDown   ; break;
		    case DIK_VOLUMEUP     : eControl = types::KeyVolumeUp     ; break;
		    case DIK_WEBHOME      : eControl = types::KeyWebHome      ; break;
		    case DIK_NUMPADCOMMA  : eControl = types::KeyNumPadComma  ; break;
		    case DIK_DIVIDE       : eControl = types::KeyDivide       ; break;
		    case DIK_SYSRQ        : eControl = types::KeySysRQ        ; break;
		    case DIK_RMENU        : eControl = types::KeyRMenu        ; break;
		    case DIK_PAUSE        : eControl = types::KeyPause        ; break;
		    case DIK_HOME         : eControl = types::KeyHome         ; break;
		    case DIK_UP           : eControl = types::KeyUp           ; break;
		    case DIK_PRIOR        : eControl = types::KeyPrior        ; break;
		    case DIK_LEFT         : eControl = types::KeyLeft         ; break;
		    case DIK_RIGHT        : eControl = types::KeyRight        ; break;
		    case DIK_END          : eControl = types::KeyEnd          ; break;
		    case DIK_DOWN         : eControl = types::KeyDown         ; break;
		    case DIK_NEXT         : eControl = types::KeyNext         ; break;
		    case DIK_INSERT       : eControl = types::KeyInsert       ; break;
		    case DIK_DELETE       : eControl = types::KeyDelete       ; break;
		    case DIK_LWIN         : eControl = types::KeyLWin         ; break;
		    case DIK_RWIN         : eControl = types::KeyRWin         ; break;
		    case DIK_APPS         : eControl = types::KeyApps         ; break;
		}

		if (eControl == types::InvalidControl)
			return; //... ����� ������� �� ��������������

        Control *pControl = keyboard->get_control(eControl);
		if (!pControl)
			return; //... ����� ������� ��� ���������� �� ������������ 

		pControl->m_time  = dod.dwTimeStamp;
		pControl->m_press = (dod.dwData & 0x80) ? true : false;
		pControl->m_delta = 0;

		pControl->notifyAllObservers();
    }

    //��������� ������� �������
    void input_impl::mProcess (DIDEVICEOBJECTDATA dod)
    {
        //���������, �� ������ �������� ������ ���������
        types::EControl eControl = types::InvalidControl;
        switch (dod.dwOfs)
        {
            case DIMOFS_BUTTON0: eControl = types::ButtonLeft  ; break;
            case DIMOFS_BUTTON1: eControl = types::ButtonRight ; break;
            case DIMOFS_BUTTON2: eControl = types::ButtonMid   ; break;
            case DIMOFS_X:       eControl = types::AxisX       ; break;
            case DIMOFS_Y:       eControl = types::AxisY       ; break;
            case DIMOFS_Z:       eControl = types::AxisWheel   ; break;
        }

		if (eControl == types::InvalidControl)
			return; //... ����� ������� �� ��������������

        Control *pControl = mouse->get_control(eControl);
		if (!pControl)
			return; //... ����� ������� ��� ���� �� ������������ 

        pControl->m_time = dod.dwTimeStamp;

        if (pControl->getType() == Control::Axis)
        {
            pControl->m_press = false;
            pControl->m_delta = dod.dwData;
        }
        else if (pControl->getType() == Control::Button)
        {
            pControl->m_press = (dod.dwData & 0x80) ? true : false;
            pControl->m_delta = 0;
        }

        pControl->notifyAllObservers();
    }
}