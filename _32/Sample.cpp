#include "Sample.h"
bool Sample::Init() {

	D3D11_DEPTH_STENCIL_DESC dsd;
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	dsd.StencilEnable = TRUE;
	dsd.StencilReadMask = 1;
	dsd.StencilWriteMask = 1;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	m_pd3dDevice->CreateDepthStencilState(&dsd, m_pDSSBox.GetAddressOf());
	
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	dsd.BackFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;

	m_pd3dDevice->CreateDepthStencilState(&dsd, m_pDSSPlane.GetAddressOf());

	RECT rt = { 400,300,600,450 };

	m_PlaneObj.SetScreenRect(rt);
	m_PlaneObj.Create(m_pd3dDevice,
		m_pContext,
		L"Lin3.jpg",
		L"ShapeShader.txt");

	m_PlaneObj.m_pBlendState = TDxState::g_pBSAlphaBlend; 
	m_PlaneObj.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObj.Create(m_pd3dDevice,
		m_pContext,
		L"Lin4.jpg",
		L"ShapeShader.txt");

	m_BoxObj.m_pBlendState = TDxState::g_pBSNoColorBlend;
	m_BoxObj.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObjChild.Create(m_pd3dDevice,
		m_pContext,
		L"Lin5.jpg",
		L"ShapeShader.txt");

	m_BoxObjChild.m_pBlendState = TDxState::g_pBSNoColorBlend;
	m_BoxObjChild.m_pSamplerState = TDxState::g_pSamplerState;

	m_BoxObjLeaf.Create(m_pd3dDevice,
		m_pContext,
		L"Lin6.jpg",
		L"ShapeShader.txt");

	m_BoxObjLeaf.m_pBlendState = TDxState::g_pBSNoColorBlend;
	m_BoxObjLeaf.m_pSamplerState = TDxState::g_pSamplerState;

	

	m_Camera.m_vPos = Vector3(0, 35, -0.2f);
	m_Camera.m_vTarget = Vector3(0, 0, 0.0f);
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

	TMatrix scale;
	scale.Scale(20, 20, 20);
	m_matWorldPlane.XRotate(DegreeToRadian(90));
	m_matWorldPlane = scale * m_matWorldPlane;

	m_matWorldPlane._42 = 3;
	return true;

}

bool Sample::Frame()
{
	TMatrix trans, spin, scale;
	trans.Translation(7, 0, 0);
	scale.Scale(2, 2, 2);
	spin.YRotate(g_fTimer);

	m_matWorldBox = scale * spin;
	TMatrix invScale = scale.Transpose();
	m_matWorldBoxChild = spin * trans * spin;
	trans.Translation(3, 0, 0);

	scale.Scale(0.5f, 0.5f, 0.5f);
	m_matWorldBoxLeaf = scale * trans * spin * m_matWorldBoxChild;

	m_PlaneObj.Frame();
	m_BoxObj.Frame();
	m_BoxObjChild.Frame();
	return true;
};

bool Sample::Render()
{
	if (g_InputData.bWKey)
	{
		//ApplyDSS(m_pContext, TDxState::g_pDSSDepthEnable);
		m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * 1.3f;
	}
	if (g_InputData.bSKey)
	{
		//ApplyDSS(m_pContext, TDxState::g_pDSSDepthDisable);
		m_Camera.m_vPos =
			m_Camera.m_vPos + Vector3(0, 0, 1) * g_fSecondPerFrame * -1.3f;
	}
	m_Camera.m_matView.ViewMatrix(
		m_Camera.m_vPos,
		m_Camera.m_vTarget,
		m_Camera.m_vUp);


	ApplyRS(m_pContext, TDxState::g_pRSSolidBack);
	ApplyDSS(m_pContext, m_pDSSBox.Get(), 0x01);

	m_BoxObj.SetMatrix(&m_matWorldBox,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_BoxObj.Render();

	m_BoxObjChild.SetMatrix(&m_matWorldBoxChild,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_BoxObjChild.Render();

	m_BoxObjLeaf.SetMatrix(&m_matWorldBoxLeaf,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_BoxObjLeaf.Render();

	ApplyDSS(m_pContext, m_pDSSPlane.Get(), 0x00);
	ApplyBS(m_pContext, TDxState::g_pBSAlphaBlend);
	m_PlaneObj.SetMatrix(&m_matWorldPlane,
		&m_Camera.m_matView,
		&m_Camera.m_matProj);
	m_PlaneObj.Render();

	return true;
}
bool Sample::Release()
{
	m_PlaneObj.Release();
	m_BoxObj.Release();
	m_BoxObjChild.Release();
	m_BoxObjLeaf.Release();
	return true;
}
