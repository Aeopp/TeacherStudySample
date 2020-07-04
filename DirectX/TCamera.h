#pragma once
#include "TMath.h"
#include "TObject.h"

class TCamera
{
public :
	TMatrix m_matView;
	TMatrix m_matProj;
	Vector3 m_vPos;
	Vector3 m_vTarget;
	Vector3 m_vLook;
	Vector3 m_vUp;
	Vector3 m_vRight;
public :
	bool Init();
};

