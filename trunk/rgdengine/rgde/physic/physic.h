/******************************************************************************
@file    physic.h
@author  Neonic
@mail    gaba@male.ru
@project RGDE
@date    23.12.2005
@desc  
 ******************************************************************************/

//Neonic: octree

#ifndef PHYSIC_H
#define PHYSIC_H
#ifdef _WIN32
#pragma once
#endif

#pragma warning(disable : 4244) // type conversion warning.
#pragma warning(disable : 4305)	// truncation from 'const double' to 'float'

#include <rgde/base/singelton.h>

// this define allow us to use customized physic
#define PHYSIC_CUSTOM

#ifndef PHYSIC_CUSTOM
#define PHYSIC_REALM physic
#else
#define PHYSIC_REALM physic2
#endif

#ifndef PHYSIC_CUSTOM

//bullet includes
#include "CcdPhysicsEnvironment.h"
#include "CcdPhysicsController.h"

#include "PHY_IMotionState.h"
#include "SimdTransform.h"

#include "CollisionShapes/BoxShape.h"
#include "CollisionShapes/Simplex1to4Shape.h"
#include "CollisionShapes/EmptyShape.h"

#include "Dynamics/RigidBody.h"
#include "ConstraintSolver/SimpleConstraintSolver.h"
#include "ConstraintSolver/OdeConstraintSolver.h"
#include "CollisionDispatch/ToiContactDispatcher.h"
#include "BroadphaseCollision/SimpleBroadphase.h"

#include "PHY_Pro.h"

//��������� ��� ���������� ������� bullet
#include "IDebugDraw.h"


namespace physic
{
	using namespace math;

	/* \brief ��������������� ����� ����������� ��������� �������
	*/
	class CPhysicObject :
		public PHY_IMotionState
	{
	private:
		//TODO: add model ptr

		//TODO: add pos/rot/scale modificator to control renderable object

		// motion state
		SimdTransform		m_worldTransform;
		Matrix44f			m_transform;

		CcdPhysicsController* m_pcController;

		bool				m_IsChanged;

	public:
		CPhysicObject( void );
		~CPhysicObject( void );

		CcdPhysicsController* getController( void ) { return m_pcController; };
		CcdPhysicsController* operator()( void ) { return m_pcController; };
		void operator() ( CcdPhysicsController* p ) { m_pcController = p; };

		void	registerController( void );

		Matrix44f getTransform( void ) const;
		void	getWorldPosition( Point3f& pos );
		void	getWorldScaling( Vec3f& scale );
		void	getWorldOrientation( Quatf& rot );

		void	setWorldPosition( const Point3f& pos );
		void	setWorldOrientation( const Quatf& rot );

		// motion state function implementations
		void	getWorldPosition( float& posX, float& posY, float& posZ );
		void	getWorldScaling( float& scaleX, float& scaleY, float& scaleZ );
		void	getWorldOrientation( float& quatIma0, float& quatIma1, float& quatIma2, float& quatReal );
		
		void	setWorldPosition( float posX, float posY, float posZ );
		void	setWorldOrientation( float quatIma0, float quatIma1, float quatIma2, float quatReal );

		void	calculateWorldTransformations( void );
	};

	typedef std::auto_ptr<CPhysicObject> PPhysicObject;
	typedef std::vector<CPhysicObject*> TVecPhysObjPtr;

	/* \brief �������� ����� ���������� �������
	*/
	class CPhysic
		: public CcdPhysicsEnvironment
	{
	public:
		CPhysic( void );
		~CPhysic( void );

		//�������������
		void init( void );              

		//���������� ����� ����������
		void setUpdateTime( float dt ) { m_fDeltaTime = dt; };

		//�������� ���������� �������
		void update( void );

		//���������� ��������� ������
		void drawDebug( void );

		//�������
		int	getDebug( void ) { return m_iDebugPhysic; };
		void setDebug( int dbg ) { m_iDebugPhysic = dbg; };
		void switchDebug( void );

		//���������/���������� �����.
		//TODO: �� ����� ���� ���������� ����������� ITask, �� ��� ���� ����������, ��� ��� �������� �� IApplication
		void switchIdle( void ) { m_bIdle = !m_bIdle; };
		bool getIdle( void ) { return m_bIdle; };

		//������� ���������� ������
		CPhysicObject* createObject( void );

		//�������� ��������� �� ��������� ���������� ��������
		TVecPhysObjPtr* getStorage( void ) { return &m_vecObjects; };

		//������������� � �������� ���������� ���������� ��������. ��� ������ ��������� ����
		void prepareStorage( int num ) { m_vecObjects.reserve(num); };

	private:

		float						m_fDeltaTime;
		// ������� ������. ��������� AABB ��� ���������� �����
		int							m_iDebugPhysic;
		// ��������� ��������
		bool						m_bIdle;
		
		// ��� ���������� ������� �� ������ �����
		TVecPhysObjPtr				m_vecObjects;

		//TODO: modify vector storage to auto-deletion

		//TODO: add sync between physic & renderable object in update cycle
	};
	typedef base::TSingelton<CPhysic>	Physic;
}

#endif // PHYSIC_CUSTOM

namespace physic2
{
	using namespace math;
//	using namespace octree;

	/** \brief ������� ��������� ���������� �������
		class Ptr ������ ���� boost::shared_ptr<T>
	*/
	template<class T, class Ptr>
	class IPhContainer :
		public std::vector<Ptr>
	{
		//TODO: perform tests within container
	public:
		typedef T					elem_type;
		typedef T*					pointer;
		typedef Ptr					spointer;
		typedef std::vector<Ptr>	base;

		/// ������� ������
		virtual spointer			create( void )
		{
			spointer p = spointer(new T());
			assert(p);
			push_back(p);
			return p;
		}

		/// ������� ������
		virtual void				erase( pointer p )
		{
			assert(p);
			Ptr ptr(p);
			for(iterator it = begin(); it!=end(); it++)
				if(*it==ptr)
				{
					base::erase(it);
					break;
				}
		};
	};

	// classes
	class	CPhSystem;
	struct	CPhWorld;
	struct	CPhController;
	struct	CPhContact;
	struct	CPhJoint;

	// pointers
	typedef boost::shared_ptr<CPhWorld>			PPhWorld;
	typedef boost::shared_ptr<CPhController>	PPhController;
	typedef boost::shared_ptr<CPhContact>		PPhContact;
	typedef boost::shared_ptr<CPhJoint>			PPhJoint;

	// containers
	typedef IPhContainer<CPhController,PPhController>	TPhControllers;
	typedef IPhContainer<CPhWorld,PPhWorld>				TPhWorlds;
	typedef IPhContainer<CPhContact,PPhContact>			TPhContacts;
	typedef IPhContainer<CPhJoint,PPhJoint>				TPhJoints;

	enum ePhGeom {
		PGNone		= 0,			// nothing
		PGSphere,					// simple sphere geometry
        PGCube,						// simple cube geometry
		PGTriangles,				// advanced geometry
	};

	/** \brief ���������� ����������� �������
	*/
	struct CPhController
	{
		/// ���������� ���, � �������� ����������� ������
		PPhWorld		m_pWorld;
		/// ����������
		TPhJoints		m_Joints;
		/// �����
		float			m_Mass;
		/// ���������, ����� �����
		Point3f			m_position;
		/// ����������
		Quatf			m_rotation;
		/// ������
		Vec3f			m_scale;
		/// �����
		unsigned		m_Flags;
		/// ��������� �� ������ ������������
		void*			m_pData;
		/// ������� �������������
		Matrix44f		m_Transform;
		/// ���������� �� ����������� ������� �������������
		bool			m_bIsNeedRecompute;

		/// �������� � ������� ���������
		Vec3f			m_lvel, m_avel;
		/// ������������ ���� � ��������
		Vec3f			m_fass, m_tass;

	// ���������
		//typedef TIndexedGeometry<vertex::Position, false>	Geometry;
		//typedef boost::shared_ptr<Geometry>					PGeometry;
		/// ��� ���������
		ePhGeom			m_Type;
		/// ������ ��������� - �� �������� � CMesh 
		//PGeometry		m_geometry;

		/// �����������
		CPhController( void );
		/// ������� ���������� ���
		void			changeWorld( PPhWorld p );
	};

	/** \brief ������� ����� ����������� ���������
	*/
	struct CPhContact
	{
		//
	};

	/** \brief ���������� ����� ����������� ���������
	*/
	struct CPhJoint
	{
		//
	};
	
	/** \brief ���������� ���
	*/
	struct CPhWorld
	{
		/// ����������
		Point3f			m_vGravity;
		/// ���������� �����������
		TPhControllers	m_Controllers;
		/// ���������� ����������
		TPhJoints		m_Joints;
		/// ��������. ���������� ��������� ������� �� ������������ ������� ����������
		TPhContacts		m_Contacts;

		/// �����������
		CPhWorld( void );
		/// ����������
		void	update( float dt );
		/// ���������� � ����������� ������������ �������-�����
		void	update( float dt, TPhContacts* p );
	};

	/** \brief ���������� �������
	*/
	class CPhSystem
	{
	private:
		/// ����� ��������� �� ���������� �����
		float			m_fDeltaTime;
		/// ����� �����������
		float			m_fDeactivationTime;
		/// ������ �����
		TPhWorlds		m_Worlds;
		/// ������� ������. ��������� AABB ��� ���������� �����
		int				m_iDebugPhysic;
		/// ��������� ��������
		bool			m_bIdle;

	public:
		/// �����������
		CPhSystem( void );
		/// �������������
		void				init( void );              
		/// ���������� ����� ����������
		void				setUpdateTime( float dt ) { m_fDeltaTime = dt; };
		/// �������� ���������� �������
		void				update( void );
		/// ���������� ��������� ������
		void				drawDebug( void );
		/// ��������� ������� �����������
		void				setDeactivationTime( float f );
		/// ���������� ���������� ��� ���������� ����
		void				setGravity( PPhWorld w, Point3f &pt);
		/// �������� ���������� ���������� ����
		Point3f				getGravity( PPhWorld w );
		/// ������� ���������� ���
		PPhWorld			createWorld( void );
		/// ���������� ���������� ���
		void				eraseWorld( PPhWorld pWorld );
		/// ���������� ��� ������������ ���������� ����
		void				cleanWorlds( void );
		/// ������� ���������� ����������
		PPhController		createController( PPhWorld p );
		/// ������������� � �������� ���������� ���������� ��������. ��� ������ ��������� ����
		void				reserve( unsigned num );
		/// ��������� ��������
		TPhWorlds*			getWorlds( void );
		/// �������
		int					getDebug( void );
		void				setDebug( int dbg );
		void				switchDebug( void );
		//���������/���������� �����.
		//TODO: �� ����� ���� ���������� ����������� ITask, �� ��� ���� ����������, ��� ��� �������� �� IApplication
		void				switchIdle( void ) { m_bIdle = !m_bIdle; };
		bool				getIdle( void ) { return m_bIdle; };
	};

	typedef base::TSingelton<CPhSystem> Physic;
}

#endif // PHYSIC_H
