#pragma once
#include "TCore.h"
#include "TPlaneObj.h"
#include "TBoxObj.h"
struct TCamera
{
	TMatrix				m_matView;
	TMatrix				m_matProj;
	Vector3				m_vPos;
	Vector3				m_vTarget;
	Vector3				m_vLook;//z
	Vector3				m_vUp; //y
 	Vector3				m_vRight;//x
};
class Sample : public TCore
{
	ComPtr<ID3D11DepthStencilState> m_pDSSBox;
	ComPtr<ID3D11DepthStencilState> m_pDSSPlane;
public:
	TPlaneObj			m_PlaneObj;
	TBoxObj				m_BoxObj;
	TBoxObj				m_BoxObjChild;
	TBoxObj				m_BoxObjLeaf;
	TMatrix				m_matWorldPlane;
	TMatrix				m_matWorldBox;
	TMatrix				m_matWorldBoxChild;
	TMatrix				m_matWorldBoxLeaf;
	TCamera				m_Camera;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};
TWINGAME;