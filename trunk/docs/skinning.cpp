class CSkeleton//������ ��������� �� Root ����� ������� � ������, � ����� �������� (�������, �������� �� ���������)
			   //� �������� �������, �, ������� ��, ������� ��������
{
public:
	typedef math::PFrame Bone;
	typedef std::vector<Bone> Bones;
	typedef std::vector<math::Matrix34f> Matrices;

	const Bone& getRootFrame() const;
	const Bones& getBones() const;

	const Matrices& getInverseZeroMatrices();
	const Matrices& getTransitionMatrices();

	void update();//������������� TransitionMatrices ��� �������� ������� ������� (� ������������ � ���������� �������)
	//...
};

class CFrameAnimation//������ �������� �� ���������� ��� ������ ������
{
public:
	struct Key
	{
		math::Quatf		rotation;
		math::Point3f	postition;
		math::Vec3f		scale;
		float			time;	
	};

	typedef .... Keys;

	CFrameAnimation(const math::PFrame& frame) // ���� �����������
		m_frame(frame)
	{
	}

	Keys& getKeys() {return m_keys;}

	void update(float fNormalizedTime) const;

private:
	math::PFrame m_frame;
	Keys	m_keys;
};

/*
class CSkeletonAnimation//������ �������� ��� ������ �������
{
public:
	CSkeletonAnimation(const PSkeleton& pSkeleton) 
		: m_skeleton(pSkeleton)
	{
	}

	void update(float fNormalizedTime) const
	{
		//pSkeleton->getBones(), � ����� ��� ���� ���� �������� �� ��������� CFrameAnimation�� (�� ����) ���������
		//���������
	}

private:
	//����� ���� ��� ��������� CFrameAnimation�� (��� ������� ����)
};
*/
/*
class CHierarchyDescriptor
{
public:

	struct SHierarchyNode
	{
		SHierarchyNode(SHierarchyNode* pParentNode, int nType);
		SHierarchyNode(int nType);

		int                          nType;
		SHierarchyNode*              pParentNode;
		std::vector<SHierarchyNode*> vChildNodes;
	};

	SHierarchyNode* 

};
*/
class CAnimation
{
public:

	typedef std::vector<CFrameAnimation> FrameAnimationsVector;
//	typedef std::vector<CSkeletonAnimation> SkeletonAnimationsVector;

	const FrameAnimationsVector& getFrameAnimations() const;
//	const SkeletonAnimationsVector& getSkeletonAnimations() const;

	FrameAnimationsVector& getFrameAnimations();
//	SkeletonAnimationsVector& getSkeletonAnimations();

};

class CFrameAnimator//���������� ��� ��, ��� ������ ���� ������������. ��� ������������� � ������ � ��������� ���,
					//������� ������� �����.
{
public:

	CFrameAnimator(math::PFrame& pFrame);

	void setAnimation(PFrameAnimation pAnimation);

	void updateState();//������ ��� ���������� dt
	void update(float dtNorm);

	void getCurrentNormalizedTime()
    
	void pause();
	void play();

	void setLooped(bool bLooped);
};

class CAnimationController
{
public:
/*
	template <class T>
	struct SClient
	{
		SClient(bool bLooped, float fRate, T& rClient);

		//�������� ��� ���-��
		bool  bLooped;
		float fRate;
		T&    rClient;
	};

	typedef SClient<math::PFrame> FrameClient;
	typedef SClient<PSkeleton> SkeletonClient;

	void addFrame(const FrameClient&, PFrameAnimation);
	void addSkeleton(const SkeletonClient&, PSkeletonAnimation);
*/
/*
	struct SClient
	{
		SClient(bool bLooped, float fRate, T& rClient);

		//�������� ��� ���-��
		bool  bLooped;
		float fRate;
		T&    rClient;
	};
*/
	void addAnimator(PFrameAnimator pAnimator);
	//��� ������ ����� �� ����

	void addSkeleton(PSkeleton);
	//��� ������ ����� �� ����

	void update(float dt);//��������� ��� ���������� CFrameAnimator � ������� ���� ��������� �������� �������� �������
	void play();
	void pause();

	void setCurrentAnimation(PAnimation);//��������� �� ���� CFrameAnimator�� � ������ �� �������� �� ��� ��� �����
										 //��������
};

class CMesh
{
public:

//...

	CAnimationController& getAnimationController();

//...

};