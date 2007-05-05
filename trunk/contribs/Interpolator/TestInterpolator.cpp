//TestInterpolator.cpp
#include "engine.h"
#include "TestInterpolator.h"

TestInterpolator::TestInterpolator()
{
    m_spCamera = render::CRenderCamera::Create();
    m_spTargetCamera = math::CTargetCamera::Create(m_spCamera);

    render::TheCameraManager::Get().addCamera(m_spCamera);
    render::TheRenderManager::Get().enableVolumes(false);
    render::TheRenderManager::Get().enableLighting(true);

    m_spFont = render::IFont::Create(11, L"Arial", render::IFont::Heavy);

    initInput();
    initCamera();
    initLights();

    //m_spModel = render::CModel::Create("test_scene");

    m_spline.m_values.push_back(math::Vec3f(  0,  0,  0));
    m_spline.m_values.push_back(math::Vec3f( 20,  0,  0));
    m_spline.m_values.push_back(math::Vec3f(  0, 20,-20));
    m_spline.m_values.push_back(math::Vec3f(-20,  0, 20));
    m_spline.m_values.push_back(math::Vec3f(  0,-20,  0));
    m_spline.m_values.push_back(math::Vec3f(-20,  0,  0));
    m_spline.apply();
}

TestInterpolator::~TestInterpolator()
{
}

void TestInterpolator::initInput()
{
    {
        using namespace input;

        //�������� �������
        CInput::addCommand(L"Quit");
        CInput::addCommand(L"Reset");
        CInput::addCommand(L"Froward");
        CInput::addCommand(L"Backward");
        CInput::addCommand(L"CW");
        CInput::addCommand(L"CCW");
        CInput::addCommand(L"Horz");
        CInput::addCommand(L"Vert");

        //��������� ������� � ����������
        CInput::getDevice(Keyboard)->getControl(KeyEscape)->bind(L"Quit");
        CInput::getDevice(Keyboard)->getControl(KeyR     )->bind(L"Reset");
        CInput::getDevice(Keyboard)->getControl(KeyW     )->bind(L"Froward");
        CInput::getDevice(Keyboard)->getControl(KeyS     )->bind(L"Backward");
        CInput::getDevice(Keyboard)->getControl(KeyE     )->bind(L"CW");
        CInput::getDevice(Keyboard)->getControl(KeyQ     )->bind(L"CCW");
        CInput::getDevice(Mouse   )->getControl(AxisX    )->bind(L"Horz");
        CInput::getDevice(Mouse   )->getControl(AxisY    )->bind(L"Vert");
    }

    //������ ������� � ���������
    m_cEsc  .attach(L"Quit");
    m_cR    .attach(L"Reset");
    m_cW    .attach(L"Froward");
    m_cS    .attach(L"Backward");
    m_cE    .attach(L"CW");
    m_cQ    .attach(L"CCW");
    m_cXAxis.attach(L"Horz");
    m_cYAxis.attach(L"Vert");

    //������ ��� ������ �������-�����������
    m_cEsc   += boost::bind(&TestInterpolator::onEsc,   this);
    m_cR     += boost::bind(&TestInterpolator::onReset, this);
    m_cYAxis += boost::bind(&TestInterpolator::onYAxis, this, _1);
    m_cXAxis += boost::bind(&TestInterpolator::onXAxis, this, _1);
}

void TestInterpolator::initCamera()
{
    math::Vec3f vUpVec    ( 0.0f,   0.0f, 1.0f );
    math::Vec3f vEyePt    ( 0.0f, 100.0f, 0.0f );
    math::Vec3f vLookatPt ( 0.0f,   0.0f, 0.0f );

    m_spCamera->setProjection(math::Math::PI/4, 4.f/3.f, 1.0f, 10000.0f);

    m_spTargetCamera->setPosition(vUpVec,vEyePt,vLookatPt);
    m_spTargetCamera->activate();
}

void TestInterpolator::initLights()
{
    //render::TheLightManager::Get().setAmbientColor(math::Color(20, 20, 20, 255));

    //render::CPointLight *pPointLight = new render::CPointLight("point1");
    //scene::TheScene::Get().getRootFrame()->addChild(pPointLight);
    //pPointLight->setPosition(math::Vec3f(0,40,60));

    //pPointLight->setDiffuse(math::Color(180, 180, 180, 250));
    //pPointLight->setSpecular(math::Color(30, 30, 30, 250));
    //pPointLight->setAmbient(math::Color(0, 0, 0, 0));
    //pPointLight->setRange(5500);
    //pPointLight->setEnabled(true);
}

void TestInterpolator::update(float dt)
{
    //���
    render::TheDevice::Get().showFPS(m_spFont);

    //�������
    std::wstring text =
        L"ESC - �����\n"
        L"R - �������� ��������� � ��������� ���������\n"
        L"\n"
        L"W - ����������\n"
        L"S - �������\n"
        L"Q - ������� ������ ������� �������\n"
        L"E - ������� �� ������� �������\n";
    m_spFont->render(text,math::Rect(1,416,400,400),0xFFFFFFFF,false);

    //������
    float t=0;
    const float step = m_spline.length()/100;
    while (t<m_spline.length())
    {
        math::Vec3f v1 = m_spline(t);
        math::Vec3f v2 = m_spline(t+step);
        t += 2*step;
        render::Line3dManager::Get().addLine(v1,v2);
    }

    render::Line3dManager::Get().addBox(math::MAT_IDENTITY44F, math::Vec3f(20.f,20.f,20.f), 0xffff0000);

    //��������
    if(m_cE)
        m_spTargetCamera->rotateCW(dt*2.0f);
    if(m_cQ)
        m_spTargetCamera->rotateCCW(dt*2.0f);
    if(m_cW)
        m_spTargetCamera->goForward(dt*100.0f);
    if(m_cS)
        m_spTargetCamera->goBackward(dt*100.0f);
}

void TestInterpolator::onEsc()
{
    core::IApplication::Get()->close();
}

void TestInterpolator::onReset()
{
    initCamera();
}

void TestInterpolator::onXAxis(int dx)
{
    const int accel = 5;
    const float slow = .01f;
    const float fast = 2*slow;
    float angle = dx>accel ? dx*fast : dx*slow;

    m_spTargetCamera->rotateLeft(-angle);
}

void TestInterpolator::onYAxis(int dy)
{
    const int accel = 5;
    const float slow = .01f;
    const float fast = 2*slow;
    float angle = dy>accel ? dy*fast : dy*slow;

    m_spTargetCamera->rotateUp(angle);
}