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
public:
	TPlaneObj m_TriangleObj;
	TPlaneObj			m_PlaneObj;
	TBoxObj				m_BoxObj;
	TMatrix				m_matWorldPlane;
	TMatrix				m_matWorldBox;
	TCamera				m_Camera;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};
TWINGAME;