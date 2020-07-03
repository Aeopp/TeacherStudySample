#pragma once
#include "TTextureMgr.h"
#include "TMath.h"

struct PCT_VERTEX
{
	Vector3 p;   // POSITION
	Vector4 c;	 // COLOR
	Vector2 t;
};
struct PNCT_VERTEX
{
	Vector3 p;   // POSITION
	Vector3 n;   // 정점노말
	Vector4 c;	 // COLOR
	Vector2 t;
	PNCT_VERTEX() {};
	PNCT_VERTEX(const PNCT_VERTEX& v)
	{
		p = v.p;
		n = v.n;
		c = v.c;
		t = v.t;
	}
};
// 상수버퍼는 레지스터(float4) 단위로만 저장되어야 한다.
struct VS_CB
{
	TMatrix matWorld;
	TMatrix matView;
	TMatrix matProj;
	Vector4 c;
	float x, y, z, fTime;
};
class TObject
{
public:
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pContext;
	UINT					m_iNumVertex;
	UINT					m_iNumIndex;
	std::vector<PNCT_VERTEX>	m_pVertexList;
	std::vector<DWORD>		m_pIndexList;
	
	RECT					m_rt;
	VS_CB					m_cbData;
	Vector3					m_vInitPos;
	Vector3					m_vPos;

	TMatrix					m_matWorldPlane;
	TMatrix					m_matView;
	TMatrix					m_matProj;
public:
	DX::TDxObject			m_dxObj;
	/*ID3D11Buffer*		m_pVertexBuffer;
	ID3D11Buffer*		m_pIndexBuffer;
	ID3D11Buffer*		m_pConstantBuffer;
	ID3D11InputLayout*  m_pVertexLayout;
	ID3D11VertexShader* m_pVS;	
	ID3D11PixelShader*  m_pPS;*/
	TTexture* m_pTexture[2];
	ID3D11SamplerState* m_pSamplerState;
	ID3D11BlendState*   m_pBlendState;
public:
	void	SetMatrix(	TMatrix* matWorld, 
						TMatrix* matView=nullptr, 
						TMatrix* matProj = nullptr);
	void    SetPos(Vector3 p);
	Vector3  ScreenToNDC(POINT pt);
	void     SetScreenRect(RECT rt)
	{
		m_rt = rt;
	}
	virtual bool Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext*	pContext,		
		const TCHAR* pTextureFileName,
		const TCHAR* pShaderFileName);

	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	virtual void	CreateConstantData();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadShaderFile(T_STR szShaderFileName);
	virtual HRESULT SetInputLayout();
	virtual bool	LoadTexture(ID3D11Device * pd3dDevice,
		const TCHAR* pTextureFileName);
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
public:
	TObject();
	~TObject();
};

