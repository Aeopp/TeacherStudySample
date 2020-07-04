#include "TDevice.h"
void TDevice::CreateDXResource()
{

}
void TDevice::DeleteDXResource()
{

}
void TDevice::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice == nullptr) return;
	//ReleaseDevice();
	//SetD3DDevice(width, height);
	DeleteDXResource();

	m_pContext->OMSetRenderTargets(0, NULL, NULL);
	if (m_pRTV) m_pRTV->Release();

	DXGI_SWAP_CHAIN_DESC currentSD;
	m_pSwapChain->GetDesc(&currentSD);
	HRESULT hr = m_pSwapChain->ResizeBuffers(
		currentSD.BufferCount,
		width,
		height,
		currentSD.BufferDesc.Format,
		currentSD.Flags);
	if (FAILED(hr)) return;

	CreateRenderTarget();
	CreateDepthStencilView();
	CreateViewport();

	CreateDXResource();
}
bool	TDevice::SetD3DDevice(UINT width, UINT height)
{
	if (!CreateDevice()) return false;
	if (!CreateGIFactory()) return false;

	if (!CreateSwapChain(width, height)) return false;
	if (!CreateRenderTarget()) return false;
	if (!CreateDepthStencilView()) return false;
	if (!CreateViewport()) return false;
	return true;
}
bool	TDevice::CreateGIFactory()
{
	if (m_pd3dDevice == NULL) return E_FAIL;
	HRESULT hr;
	IDXGIDevice* pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);

	IDXGIAdapter* pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDXGIAdapter);

	IDXGIFactory* pIDXGIFactory;
	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory),
		(void**)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	return true;
}
bool	TDevice::CreateDevice()
{
	// 1�� : ����̽� ����

	UINT Flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef  _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

	HRESULT hr = D3D11CreateDevice(
		NULL,
		DriverType,
		NULL,
		Flags,
		&pFeatureLevels,
		1,
		D3D11_SDK_VERSION,
		&m_pd3dDevice,
		&FeatureLevel,
		&m_pContext);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool	TDevice::CreateSwapChain(UINT width, UINT height)
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.OutputWindow = g_hWnd;
	sd.Windowed = TRUE;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = m_pGIFactory->CreateSwapChain(
		m_pd3dDevice, &sd, &m_pSwapChain);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}
bool	TDevice::CreateRenderTarget()
{
	// 2�� ����Ÿ�� �� ����
	ID3D11Texture2D* pBackBuffer = nullptr;
	HRESULT hr = m_pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Texture2D),
		(void**)&pBackBuffer);
	if (FAILED(hr))
	{
		return false;
	}
	if (FAILED(m_pd3dDevice->CreateRenderTargetView(
		pBackBuffer,
		NULL,
		&m_pRTV)))
	{
		return false;
	}
	pBackBuffer->Release();

	m_pSwapChain->GetDesc(&m_SwapChainDesc);

	return true;
}
bool TDevice::CreateDepthStencilView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D>  pDSTex = nullptr;
	D3D11_TEXTURE2D_DESC td;
	td.Width = m_SwapChainDesc.BufferDesc.Width;
	td.Height = m_SwapChainDesc.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	hr = m_pd3dDevice->CreateTexture2D(&td, NULL, pDSTex.GetAddressOf());

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	hr = m_pd3dDevice->CreateDepthStencilView(pDSTex.Get(), &dsvd, &m_pDSV);
	return true;
}
bool	TDevice::CreateViewport()
{
	DXGI_SWAP_CHAIN_DESC currentSD;
	m_pSwapChain->GetDesc(&currentSD);
	// 3�� ����Ʈ ����
	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.Width = currentSD.BufferDesc.Width;
	m_vp.Height = currentSD.BufferDesc.Height;
	m_vp.MinDepth = 0;
	m_vp.MaxDepth = 1;
	m_pContext->RSSetViewports(1, &m_vp);
	return true;
}
bool	TDevice::ReleaseDevice()
{
	if (m_pRTV)m_pRTV->Release();
	if (m_pDSV)m_pDSV->Release();
	if (m_pSwapChain)m_pSwapChain->Release();
	if (m_pd3dDevice)m_pd3dDevice->Release();
	if (m_pContext)m_pContext->Release();
	if (m_pGIFactory)m_pGIFactory->Release();
	return true;
}
TDevice::TDevice()
{
	m_pGIFactory = nullptr;
	m_pd3dDevice = nullptr;
	m_pContext = nullptr;
	m_pSwapChain = nullptr;
	m_pRTV = nullptr;
}

TDevice::~TDevice()
{
}
