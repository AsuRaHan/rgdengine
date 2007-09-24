//RGDE
#include <rgde/engine.h>

#include <rgde/render/particles/particlesMain.h>
#include <rgde/render/particles/particlesBoxEmitter.h>
#include <rgde/render/particles/particlesMayaEmitter.h>
#include <rgde/render/particles/particlesSphericalEmitter.h>
#include <rgde/render/particles/particlesParticlesProcessor.h>
#include <rgde/render/particles/particlesEffect.h>


class CParticleTest : public game::IDynamicObject
{
public:
	CParticleTest() : 
		spApp(core::IApplication::Create(L"Test Particles Example", 640, 480, false)),
		m_bDebugDraw (false),
		m_bSaveParticles (false),
		m_bLoadParticles (false)
	{
		spApp->addTask<core::RenderTask>(2)
			  .addTask<core::CGameTask>(1)
			  .addTask<core::InputTask>(0, false);

		m_spFont = render::IFont::Create(20, L"Arial", render::IFont::Heavy);

		math::Vec3f vEyePt(40, 40, -40);
		math::Vec3f vLookatPt( 0.0f, 0.0f, 0.0f );
		math::Vec3f vUpVec( 00.0f, 1.0f, 0.0f );

		// ������ ������
		m_pEffect = new particles::IEffect();
		//m_pEffect->setDebugDraw(m_bDebugDraw);

		if (m_bLoadParticles)
			loadParticles();
		else
			initParticles();

		if (m_bSaveParticles)
			saveParticles();

		// ������������� �����
		initInput();

		// ������������� ������
		m_pCamera  = render::CRenderCamera::Create();
		m_pCamera->setProjection(math::Math::PI/4, 1.0f, 1.0f, 10000.0f);
		m_cTargetCamera = math::CTargetCamera::Create(m_pCamera);
		render::TheCameraManager::Get().addCamera(m_pCamera);
		m_cTargetCamera->setPosition(vEyePt,vLookatPt,vUpVec);
		m_cTargetCamera->activate();

		spApp->Run();
	}

	void initInput()
	{
		using namespace input;

		//m_cXAxis.attachToControl(input::Mouse, input::AxisX);
		//m_cYAxis.attachToControl(input::Mouse, input::AxisY);
		//m_cRightButton.attachToControl(input::Mouse, input::ButtonRight);
		//m_cZAxis.attachToControl(input::Mouse, input::AxisWheel);
		//m_cEsc.addHandler(this,&CParticleTest::onEsc);
		//m_cYAxis.addHandler(this,&CParticleTest::onYAxis);
		//m_cXAxis.addHandler(this,&CParticleTest::onXAxis);
		//m_cZAxis.addHandler(this,&CParticleTest::onWheelAxis);

		//��������� ������� � ����������
		Input::getDevice(types::Keyboard)->getControl(types::KeyEscape)->bind(L"Quit");
		//Input::getDevice(types::Keyboard)->getControl(types::KeyW     )->bind(L"Froward");
		//Input::getDevice(types::Keyboard)->getControl(types::KeyS     )->bind(L"Backward");
		//Input::getDevice(types::Keyboard)->getControl(types::KeyE     )->bind(L"CW");
		//Input::getDevice(types::Keyboard)->getControl(types::KeyQ     )->bind(L"CCW");
		Input::getDevice(types::Mouse   )->getControl(types::AxisX    )->bind(L"Horz");
		Input::getDevice(types::Mouse   )->getControl(types::AxisY    )->bind(L"Vert");

		//������ ������� � ���������		
		//m_cR    .attach(L"Reset");
		//m_cW    .attach(L"Froward");
		//m_cS    .attach(L"Backward");
		//m_cE    .attach(L"CW");
		//m_cQ    .attach(L"CCW");
		m_keyupQuit.attach(L"Quit");
		m_cXAxis.attach(L"Horz");
		m_cYAxis.attach(L"Vert");

		//������ ��� ������ �������-�����������		
		//m_cEsc   += boost::bind(&TestInterpolator::onEsc,   this);
		//m_cR     += boost::bind(&TestInterpolator::onReset, this);
		m_keyupQuit += boost::bind(&CParticleTest::onQuit, this);
		m_cYAxis += boost::bind(&CParticleTest::onYAxis, this, _1);
		m_cXAxis += boost::bind(&CParticleTest::onXAxis, this, _1);
	}

	~CParticleTest()
	{
		deleteParticles();
	}

public:
	//����� �� ���������
	void onQuit()
	{
		core::IApplication::Get()->close();
	}

	//��� X
	void onXAxis(int dx)
	{
		const int accel = 5;
		const float slow = .01f;
		const float fast = 2*slow;
		float angle = dx>accel ? dx*fast : dx*slow;

		//if (m_cRightButton)
			m_cTargetCamera->rotateLeft(-angle);
	}

	//��� Y
	void onYAxis(int dy)
	{
		const int accel = 5;
		const float slow = .01f;
		const float fast = 2*slow;
		float angle = dy>accel ? dy*fast : dy*slow;

		//if (m_cRightButton)
			m_cTargetCamera->rotateUp(angle);
	}

	///*onWheelAxis*/
	//void onWheelAxis(const input::CRelativeAxisEvent &event)
	//{
	//	const float slow = .1f;
	//	m_cTargetCamera.goBackward(-event.m_nDelta*slow);
	//}

	//-----------------------------------------------------------------------------------
	virtual void update(float dt)
	{
		render::TheDevice::Get().showWiredFloorGrid(100.0f, 20, math::Color(150, 150, 150, 255));
		render::TheDevice::Get().showWiredFloorGrid(100.0f, 2, math::Color(60, 60, 60, 255));
	}
protected:
	//-----------------------------------------------------------------------------------
	void initParticles()
	{
		// ������ ��������
		for( int i = 0; i < 3; i++ )
		{
			float fDist = (float)i*10;
			// ������ ����������� ������
			particles::ISphericalEmitter* pSphericalEmitter = new particles::ISphericalEmitter();
			m_pEffect->addEmitter(pSphericalEmitter);

			particles::IParticlesProcessor* pProcessor = new particles::IParticlesProcessor();
			pProcessor->setTextureName( "particles/Shot_Smoke.png" );
			pProcessor->setMaxParticles( 100 );
			pProcessor->setGlobal( false );
			pSphericalEmitter->addProcessor(pProcessor);
			pProcessor->load();


			pSphericalEmitter->getTransform().setPosition(math::Point3f( fDist, 0, -fDist/1.732f));

			// ������ ���������� ������
			particles::IBoxEmitter* pBoxEmitter = new particles::IBoxEmitter();
			m_pEffect->addEmitter(pBoxEmitter);

			pProcessor = new particles::IParticlesProcessor();
			pBoxEmitter->addProcessor(pProcessor);
			pProcessor->setTextureName( "particles/Shot_Smoke.png" );
			pProcessor->setMaxParticles( 100 );
			pProcessor->setGlobal( false );
			pProcessor->load();

			pBoxEmitter->getTransform().setPosition( math::Point3f( -fDist, 0, -fDist/1.732f) );

			// ������ ���� ������
			particles::IMayaEmitter* pMayaEmitter = new particles::IMayaEmitter("particles/cannonShot_smoke.prt", "particles/shot_smoke.png");
			m_pEffect->addEmitter( pMayaEmitter );

			pMayaEmitter->setCycling(true);
			pMayaEmitter->setVisible(true);

			pMayaEmitter->getTransform().setPosition( math::Point3f(0, 0, fDist ) );
		}
	}

	//-----------------------------------------------------------------------------------
	void deleteParticles()
	{
		//delete m_pEffect;
		particles::IMayaEmitter::ClearCachedData();
		render::IEffect::ClearAll();
	}

	//-----------------------------------------------------------------------------------
	void loadParticles()
	{
		//io::ReadFile in( 
		//	io::helpers::createFullFilePathA(L"Media/particles/particles_serialization.dat").c_str() );
		//if (!in.isOpened())
		//{
			initParticles();
			//saveParticles();
			//deleteParticles();

			// ������ ������
			//m_pEffect = new particles::IEffect();
			//m_pEffect->setDebugDraw(true);
		//	in.open( io::helpers::createFullFilePathA(L"Media/particles/particles_serialization.dat").c_str() );
		//}
		//in >> *m_pEffect;
	}

	//-----------------------------------------------------------------------------------
	void saveParticles()
	{
		//io::CWriteFileStream out( 
		//	io::helpers::createFullFilePathA(L"Media/particles/particles_serialization.dat").c_str() );
		//out << *m_pEffect;
	}


protected:
	std::auto_ptr<core::IApplication> spApp;

	//������ ��� �����
	input::KeyUp        m_keyupQuit;
	input::RelativeAxis m_cXAxis;
	input::RelativeAxis m_cYAxis;
	//input::CButtonCommand       m_cEsc;
	//input::CButtonCommand		m_cRightButton;
	//input::CRelativeAxisCommand m_cZAxis;

	math::PCamera				m_pCamera;
	math::PTargetCamera			m_cTargetCamera;      //���������� ������ "���������� ������"


	::render::PFont		m_spFont;

	bool m_bDebugDraw;				// ����� �� ��������� � ����� �������� ���������
	bool m_bSaveParticles;			// ����� �� ��������� ������ ������ � ����
	bool m_bLoadParticles;			// ����� �� ��������� ������ ������ ���������� ��� ������� �� �����
	particles::IEffect*	m_pEffect;	// ������ ������
};

int main()
{
	CParticleTest particleTest;
	return 0;
}