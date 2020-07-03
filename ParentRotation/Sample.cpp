#include "Sample.h"

static constexpr float dt = 1.f / 500.f; 
static std::pair<float, float> mousepos{}; 
static std::pair<float, float> mouse_move_delta{};

bool Sample::Init()
{
	RECT rt = { 400,300,600, 450 };
	m_PlaneObj.SetScreenRect(rt);
	m_PlaneObj.Create(m_pd3dDevice,
		m_pContext,
		L"Lin.png",
		L"Lin.png");
	m_PlaneObj.m_pBlendState = TDxState::g_pBlendState;
	m_PlaneObj.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObj.Create(m_pd3dDevice,
		m_pContext, 
		L"Lin.png",
		L"Lin.png");
	m_BoxObj.m_pBlendState = TDxState::g_pBlendState;
	m_BoxObj.m_pSamplerState = TDxState::g_pSamplerState;

	TBoxObj box;

	box.Create(m_pd3dDevice,
		m_pContext,
		L"Lin2.jpg",
		L"Lin2.jpg");
	box.m_pBlendState = TDxState::g_pBlendState;
	box.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObjs.push_back(box);
	TMatrix _temp;
	_temp.Translation(Vector3{0,5,0}); 
	m_BoxMats.push_back(_temp);

	TBoxObj box2;

	box2.Create(m_pd3dDevice,
		m_pContext,
		L"Lin3.jpg",
		L"Lin3.jpg");
	box2.m_pBlendState = TDxState::g_pBlendState;
	box2.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObjs.push_back(box2);
	TMatrix _temp2;
	_temp2.Translation(Vector3{ 0,-5,0 });
	m_BoxMats.push_back(_temp2);

	this->BoxTesterAdd(L"Lin4.jpg", Vector3{ -5,0,0 });
	this->BoxTesterAdd(L"Lin5.jpg", Vector3{ -5,-5,0 });
	this->BoxTesterAdd(L"Lin6.jpg", Vector3{ -5,+5,0 });
	this->BoxTesterAdd(L"Lin7.jpg", Vector3{ 5,-5,0 });
	this->BoxTesterAdd(L"Lin8.jpg", Vector3{ 5,+5,0 });
	this->BoxTesterAdd(L"Lin9.jpg", Vector3{ 5,0,0 });

	m_Camera.m_vPos = Vector3(0, 0, -5.0f);
	m_Camera.m_vTarget= Vector3(0, 0, 0.0f);
	m_Camera.m_vUp = Vector3(0, 1, 0.0f);
	m_Camera.m_matView.ViewMatrix(
		m_Camera.m_vPos,
		m_Camera.m_vTarget,
		m_Camera.m_vUp);

	float Aspect = g_rtClient.right / g_rtClient.bottom;
	m_Camera.m_matProj.PerspectiveFovLH(
		1.0f, 
		100.0f,
		TBASIS_PI * 0.25f,
		Aspect);
	return true;
}
bool Sample::Frame()
{
	m_matWorldBox.YRotate(g_fTimer);
	for (size_t i = 0; i < m_BoxMats.size(); ++i) {
		if (i % 2==0) {
			
			m_BoxMats[i].XRotate(g_fTimer);
		}
		else if (i % 2==1) {
			m_BoxMats[i].YRotate(g_fTimer);
		}
	};

	m_PlaneObj.Frame();
	m_BoxObj.Frame();
	
	for (auto& box : m_BoxObjs) {
		box.Frame();
	}
	auto [x, y] = I_Input.m_MousePos;

	mouse_move_delta = {
		mousepos.first - x,
		mousepos.second - y};

	mousepos = { x,y, };

	return true;
}
bool Sample::Render()
{
	if (g_InputData.bWKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthEnable);

		m_Camera.m_vPos = m_Camera.m_vPos - m_Camera.GetForwardVector().Normal() * dt;
		/*m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * 1.3f;*/
	}
	if (g_InputData.bSKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);
	
		m_Camera.m_vPos = m_Camera.m_vPos  + m_Camera.GetForwardVector().Normal() * dt; 
		//m_Camera.m_vPos = m_Camera.m_vTarget - m_Camera.GetForwardVector().Normal() * dt; 
		/*m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;*/
	}
	if (g_InputData.bAKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);

		m_Camera.m_vPos = m_Camera.m_vPos - m_Camera.GetRightVector().Normal() * dt;
	//	m_Camera.m_vPos = m_Camera.m_vTarget  - m_Camera.GetRightVector().Normal() * dt;  
		/*m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;*/
	}
	if (g_InputData.bDKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);

		TMatrix Rotation;

		Rotation.Identity();
		Rotation.XRotate(-g_fTimer);
		m_Camera.m_vPos* Rotation;

		m_Camera.m_vPos = m_Camera.m_vPos  +  m_Camera.GetRightVector().Normal() * dt;
	//	m_Camera.m_vPos = m_Camera.m_vTarget  + m_Camera.GetRightVector().Normal() * dt;
		/*m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;*/
	}

	if (g_InputData.bEKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);

		TMatrix Rotation;
		Rotation.Identity();
		Rotation.XRotate(g_fTimer);
		m_Camera.m_vPos* Rotation;

		m_Camera.m_vPos = m_Camera.m_vPos + m_Camera.GetUpVector().Normal() * dt;
		//	m_Camera.m_vPos = m_Camera.m_vTarget  + m_Camera.GetRightVector().Normal() * dt;
			/*m_Camera.m_vPos =
				m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;*/
	}


	if (g_InputData.bQKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);

		m_Camera.m_vPos = m_Camera.m_vPos  - m_Camera.GetUpVector().Normal() * dt;
		//	m_Camera.m_vPos = m_Camera.m_vTarget  + m_Camera.GetRightVector().Normal() * dt;
			/*m_Camera.m_vPos =
				m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;*/
	}

	auto [ x,y ]  = mouse_move_delta;

	if (x > 0 || g_InputData.bLeftKey) {
		m_Camera.m_vTarget = m_Camera.m_vTarget +Vector3{ -1,0,0 }*dt;
	}
	if (x < 0 || g_InputData.bRightKey ) {
		m_Camera.m_vTarget = m_Camera.m_vTarget + Vector3{ 1,0,0 } * dt;
	}
	if (y > 0 || g_InputData.bUpKey ) {
		m_Camera.m_vTarget = m_Camera.m_vTarget + Vector3{ 0,1  ,0 }* dt;
	}
	if (y  < 0 || g_InputData.bDownKey ) {
		m_Camera.m_vTarget = m_Camera.m_vTarget + Vector3{ 0,-1 ,0 } * dt;
	}

	m_Camera.m_matView.ViewMatrix(
		m_Camera.m_vPos,
		m_Camera.m_vTarget,
		m_Camera.m_vUp);

	m_matWorldPlane._11 = 2;
	m_matWorldPlane._22 = 2;
	m_matWorldPlane._33 = 2;
	m_matWorldPlane._43 = -2;

	auto temp = g_fTimer;

	m_matWorldPlane.Identity();
	m_matWorldPlane._22 = sinf(g_fTimer) * 0.5f + 0.5f;

	m_PlaneObj.SetMatrix(&m_matWorldPlane,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);

	m_PlaneObj.Render();

	m_BoxObj.SetMatrix(&m_matWorldBox,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_BoxObj.Render();

	for (size_t i = 0; i < m_BoxObjs.size(); ++i) {
		m_BoxObjs[i].SetMatrix(&m_BoxMats[i],
			&m_Camera.m_matView,
			&m_Camera.m_matProj);
		m_BoxObjs[i].Render();
	}
	return true;
};

bool Sample::Release()
{	
	m_PlaneObj.Release();	
	m_BoxObj.Release();
	for (auto& box : m_BoxObjs) {
		box.Release();
	}
	return true;
}