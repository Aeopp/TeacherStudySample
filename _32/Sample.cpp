#include "Sample.h"
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
	m_PlaneObj.Frame();
	m_BoxObj.Frame();
	return true;
}
bool Sample::Render()
{
	if (g_InputData.bWKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthEnable);
		m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0,0,1)*g_fSecondPerFrame*1.3f;
	}
	if (g_InputData.bSKey)
	{
		ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);
		m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1)*g_fSecondPerFrame*-1.3f;
	}
	m_Camera.m_matView.ViewMatrix(
		m_Camera.m_vPos,
		m_Camera.m_vTarget,
		m_Camera.m_vUp);

    // 
	m_matWorldPlane._11 = 2;
	m_matWorldPlane._22 = 2;
	m_matWorldPlane._33 = 2;
	m_matWorldPlane._43 = -2;
	
	auto temp = g_fTimer;

	m_matWorldPlane.Identity();
	m_matWorldPlane._22   = sinf(g_fTimer) * 0.5f + 0.5f; 
	
	
	m_PlaneObj.SetMatrix(&m_matWorldPlane,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);


	m_PlaneObj.Render();






	m_BoxObj.SetMatrix(&m_matWorldBox,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	//m_BoxObj.Render();
	return true;
}
bool Sample::Release()
{	
	m_PlaneObj.Release();	
	m_BoxObj.Release();
	return true;
}