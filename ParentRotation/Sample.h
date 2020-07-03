#pragma once
#include "TCore.h"
#include "TPlaneObj.h"
#include "TBoxObj.h"
#include <vector>
#include <string_view>
struct TCamera
{
	TMatrix				m_matView;
	TMatrix				m_matProj;
	Vector3				m_vPos;
	Vector3				m_vTarget;
	Vector3				m_vLook;//z
	Vector3				m_vUp; //y
 	Vector3				m_vRight;//x

	Vector3 GetRightVector() & noexcept {
		Vector3 _Up = { 0, 1,0 };
		return _Up ^ GetLookVec(); 
	};
	Vector3 GetUpVector()& noexcept {
		Vector3 _Right = { 1,0,0 };
		return GetLookVec() ^ _Right  ;
	}
	Vector3 GetLookVec()& noexcept{
		return m_vTarget - m_vPos;
	}
	Vector3 GetForwardVector() & noexcept {
		return GetUpVector() ^ GetRightVector();
	}
};
class Sample : public TCore
{
public:
	TPlaneObj m_TriangleObj;
	TPlaneObj			m_PlaneObj;
	TBoxObj				m_BoxObj;
	std::vector<TBoxObj> m_BoxObjs;
	std::vector<TMatrix> m_BoxMats; 
	TMatrix				m_matWorldPlane;
	TMatrix				m_matWorldBox;
	TCamera				m_Camera;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

private:
	void BoxTesterAdd(const std::wstring_view filename , 
		Vector3 BoxFromOriginTranslastion) & noexcept {
		TBoxObj box2;
		box2.Create(m_pd3dDevice,
			m_pContext,
			filename.data(),
			filename.data());

		box2.m_pBlendState = TDxState::g_pBlendState;
		box2.m_pSamplerState = TDxState::g_pSamplerState;

		m_BoxObjs.push_back(box2);
		TMatrix _temp2;
		_temp2.Translation( std::move ( BoxFromOriginTranslastion )  ); 
		m_BoxMats.push_back(_temp2);
	}
};
TWINGAME;