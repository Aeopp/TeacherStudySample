#include "TCore.h"

// RTV 갱신에 따른 추가적인 생성 작업들.
void	TCore::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();
}
// RTV 갱신에 따른 사전 소멸 작업들.
void	TCore::DeleteDXResource()
{
	m_Write.DeleteDXResource();
}
bool TCore::Init() { return true; }
bool TCore::Frame() { return true; }
bool TCore::PreRender() 
{ 	
	m_pContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);

	float clearcolor[4] = { 0.0f,0.0f,0.0f,1 };
	m_pContext->ClearRenderTargetView(m_pRTV, clearcolor);
	m_pContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH| D3D11_CLEAR_STENCIL, 1.0f, 0);	
	ApplyRS(m_pContext, TDxState::g_pRSSolidBack);
	ApplyBS(m_pContext, TDxState::g_pBSAlphaBlend);
	ApplySS(m_pContext, TDxState::g_pSamplerState);
	ApplyDSS(m_pContext, TDxState::g_pDSSDepthEnable);

	if (g_InputData.bChangeFillMode)
	{
		ApplyRS(m_pContext, TDxState::g_pRSWireFrameBack);
	}
	if (g_InputData.bChangeCullMode)
	{
		ApplyRS(m_pContext, TDxState::g_pRSSolidNone);
	}
	return true; 
}
bool TCore::Render() { return true; }
bool TCore::PostRender() 
{ 
	m_Write.Render();
	m_pSwapChain->Present(0, 0);
	return true; 
}
bool TCore::Release() { return true; }

bool TCore::TCoreInit()
{	
	m_Timer.Init();
	//I_SoundMgr.Init();
	I_Input.Init();
		
	if (!SetD3DDevice(
		m_rtClient.right,
		m_rtClient.bottom)) return false;
	
	HRESULT hr = m_pGIFactory->MakeWindowAssociation(m_hWnd,
			DXGI_MWA_NO_WINDOW_CHANGES |
			DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr))
	{
		return false;
	}

	m_Write.Init();

	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();

	//BOOL fullscreen;
	//m_pSwapChain->GetFullscreenState(&fullscreen, NULL);
	//m_pSwapChain->SetFullscreenState(!fullscreen, NULL);

	TDxState::Create(m_pd3dDevice, m_pContext);

	Init();
	return true;
}
bool TCore::TCoreFrame()
{
	m_Timer.Frame();
	I_Input.Frame();

	/*I_SoundMgr.Frame();*/
	if (g_InputData.bExit)
	{
		m_bExit = true;
		return false;
	}
	Frame();
	return true;
}
bool TCore::TCoreRender()
{
	PreRender();
		Render();

		//m_Timer.Render();
		/*I_SoundMgr.Render();
		I_Input.Render();	*/

		T_STR strBuffer = L"GameTime";
		strBuffer += m_Timer.m_csBuffer;
		m_Write.Draw(1, strBuffer.c_str(), m_rtClient);

	PostRender();
	return true;
}
bool TCore::TCoreRelease()
{
	TDxState::Release();
	Release();
	m_Timer.Release();
	I_Input.Release();
	//I_SoundMgr.Release();

	TDevice::ReleaseDevice();
	return true;
}
bool TCore::TRun()
{
	TCoreInit();
	while (!m_bExit)
	{
		if (WinRun())
		{
			TCoreFrame();
			TCoreRender();
		}
	}
	TCoreRelease();
	return true;
}
TCore::TCore()
{
	m_bExit = false;
}
TCore::~TCore()
{

}