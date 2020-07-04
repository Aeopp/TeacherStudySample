#include "TObject.h"

void	 TObject::SetMatrix(TMatrix* matWorld,
	TMatrix* matView,
	TMatrix* matProj)
{
	if (matWorld != nullptr)m_matWorldPlane = *matWorld;
	if (matView != nullptr)m_matView = *matView;
	if (matProj != nullptr)m_matProj = *matProj;

	m_cbData.matWorld = m_matWorldPlane.Transpose();
	m_cbData.matView = m_matView.Transpose();
	m_cbData.matProj = m_matProj.Transpose();
	m_pContext->UpdateSubresource(
		m_dxObj.m_pConstantBuffer.Get(),
		0, NULL, &m_cbData, 0, 0);
}
void    TObject::SetPos(Vector3 p)
{
	m_vPos = p;
}
Vector3  TObject::ScreenToNDC(POINT pt)
{
	Vector3 v;
	v.x = ((float)pt.x / (float)g_rtClient.right) * 2.0f - 1.0f; //-1.0f;
	v.y = -(((float)pt.y / (float)g_rtClient.bottom) * 2.0f - 1.0f);// 1.0f;
	v.z = 0.5f;
	return v;
}
void TObject::CreateVertexData()
{
}
void TObject::CreateIndexData()
{
}
void TObject::CreateConstantData()
{
	m_cbData.c = { 1,1,1,1 };
	m_cbData.x = 0.0f;
	m_cbData.y = 0.0f;
	m_cbData.z = 0.0f;
	m_cbData.fTime = 0.0f * (3.141592f / 180.0f);
}

HRESULT TObject::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pVertexBuffer.Attach(DX::CreateVertexBuffer(
		m_pd3dDevice,
		&m_pVertexList.at(0),
		m_iNumVertex,
		sizeof(PNCT_VERTEX)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(PNCT_VERTEX)*m_iNumVertex;
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_pVertexList.at(0);
	////hr=m_pd3dDevice->CreateBuffer(&bd, NULL,&m_pVertexBuffer);
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);
	return hr;
}
HRESULT TObject::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pIndexBuffer.Attach(DX::CreateIndexBuffer(
		m_pd3dDevice,
		&m_pIndexList.at(0),
		m_iNumIndex,
		sizeof(DWORD)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(DWORD)*m_iNumIndex;
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_pIndexList.at(0);	
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer);
	return hr;
}
HRESULT TObject::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	m_dxObj.m_pConstantBuffer.Attach(DX::CreateConstantBuffer(
		m_pd3dDevice,
		&m_cbData,
		1,
		sizeof(VS_CB)));
	//D3D11_BUFFER_DESC bd;
	//bd.ByteWidth = sizeof(VS_CB);
	//bd.Usage = D3D11_USAGE_DEFAULT; // 그래픽카드 메모리에
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//D3D11_SUBRESOURCE_DATA sd;
	//sd.pSysMem = &m_cbData;
	//hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer);
	//
	return hr;
}

HRESULT TObject::LoadShaderFile(T_STR szShaderFileName)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = 0;
	ID3DBlob* pErrorBuf = nullptr;
	m_dxObj.m_pVS.Attach(DX::LoadVertexShaderFile(m_pd3dDevice,
		szShaderFileName.c_str(),
		0,
		"VS",
		"vs_5_0",
		&m_dxObj.m_pVSBuf));
	if (m_dxObj.m_pVS.Get() == nullptr)
	{
		hr = E_FAIL;
	}
	m_dxObj.m_pPS.Attach(DX::LoadPixelShaderFile(m_pd3dDevice,
		szShaderFileName.c_str(),
		0,
		"PS",
		"ps_5_0",
		nullptr));
	if (m_dxObj.m_pPS.Get() == nullptr)
	{
		hr = E_FAIL;
	}
	return hr;
}
HRESULT TObject::SetInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{  "POSITION", 0,	DXGI_FORMAT_R32G32B32_FLOAT,0,0,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "NORMAL", 0,		DXGI_FORMAT_R32G32B32_FLOAT,0,12,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "COLOR", 0,		DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
		{  "TEXCOORD", 0,	DXGI_FORMAT_R32G32_FLOAT,0,40,
							D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT iNumElement = sizeof(layout) / sizeof(layout[0]);
	m_dxObj.m_pVertexLayout.Attach(DX::CreateInputlayout(
		m_pd3dDevice,
		m_dxObj.m_pVSBuf->GetBufferSize(),
		m_dxObj.m_pVSBuf->GetBufferPointer(),
		layout,
		iNumElement));

	/*UINT iNumElement = sizeof(layout) / sizeof(layout[0]);
	hr = m_pd3dDevice->CreateInputLayout(
		layout,
		iNumElement,
		m_pVSBuf->GetBufferPointer(),
		m_pVSBuf->GetBufferSize(),
		&m_pVertexLayout);

	if (m_pVSBuf)m_pVSBuf->Release();*/
	return hr;
}
bool TObject::LoadTexture(
	ID3D11Device* pd3dDevice,
	const TCHAR* pTextureFileName)
{
	if (pTextureFileName == nullptr) return true;
	m_pTexture[0] = I_Tex.GetPtr(I_Tex.Load(pd3dDevice, pTextureFileName));
	T_STR szMask = L"Mask";
	szMask += pTextureFileName;
	m_pTexture[1] = I_Tex.GetPtr(I_Tex.Load(pd3dDevice, szMask.c_str()));
	return true;
}
bool TObject::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,
	const TCHAR* pTextureFileName,
	const TCHAR* pShaderFileName)
{
	HRESULT hr;
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;

	Init();

	CreateVertexData();
	CreateIndexData();
	CreateConstantData();

	if (FAILED(CreateVertexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	if (FAILED(LoadShaderFile(pShaderFileName)))
	{
		return false;
	}
	if (FAILED(SetInputLayout()))
	{
		return false;
	}

	if (FAILED(LoadTexture(pd3dDevice, pTextureFileName)))
	{
		return false;
	}
	return true;
}

bool TObject::Init()
{
	return true;
}
bool TObject::Frame()
{
	return true;
}

bool TObject::PreRender()
{
	m_dxObj.PreRender(m_pContext, sizeof(PNCT_VERTEX));
	return true;
}
bool TObject::Render()
{
	PreRender();

	m_pContext->UpdateSubresource(
		m_dxObj.m_pConstantBuffer.Get(), 0, NULL,
		&m_cbData, 0, 0);

	if (m_pTexture[0] != nullptr)
		m_pContext->PSSetShaderResources(0, 1, &m_pTexture[0]->m_pSRV);
	if (m_pTexture[1] != nullptr)
		m_pContext->PSSetShaderResources(1, 1, &m_pTexture[1]->m_pSRV);
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pContext->OMSetBlendState(m_pBlendState, 0, 0xff);

	PostRender();
	return true;
}
bool TObject::PostRender()
{
	m_dxObj.PostRender(m_pContext, m_iNumIndex);
	return true;
}
bool TObject::Release()
{

	return true;
}


TObject::TObject()
{
	m_pBlendState = nullptr;

}


TObject::~TObject()
{
}
