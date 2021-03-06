#pragma once
#include "TStd.h"
class TTexture
{
public:
	T_STR		m_csName;
	ID3D11ShaderResourceView* m_pSRV;
	PVOID		m_pRaster = nullptr;
public:
	bool	Load(ID3D11Device* pd3dDevice, T_STR szName);
	bool	Release();
	bool	Frame();
	bool	Render();
	bool	Init();
public:
	TTexture();
	virtual ~TTexture();
};

