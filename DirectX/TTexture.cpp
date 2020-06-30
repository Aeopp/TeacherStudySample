#include "TTexture.h"
bool	TTexture::Frame()
{
	return true;
}
bool	TTexture::Render()
{
	return true;
}
bool	TTexture::Init()
{
	return true;
}

bool	TTexture::Load( ID3D11Device* pd3dDevice,
						T_STR szLoadFileName)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, szLoadFileName.c_str(), NULL, NULL,
		&m_pSRV, NULL);
	return true;
}
bool	TTexture::Release()
{
	if(m_pSRV)m_pSRV->Release();
	return true;
}
TTexture::TTexture()
{
	m_pSRV = nullptr;
}

TTexture::~TTexture()
{

}