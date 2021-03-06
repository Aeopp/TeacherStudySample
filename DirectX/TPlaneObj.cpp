#include "TPlaneObj.h"
//void TPlaneObj::CreateVertexData()
//{
//	m_pVertexList.resize(4);
//	m_pVertexList[0].p = ScreenToNDC({ m_rt.left, m_rt.top });
//	m_pVertexList[0].n = Vector3(0, 0, -1);
//	m_pVertexList[0].c = Vector4(1, 0, 0, 1);
//	m_pVertexList[0].t = Vector2(0, 0);
//
//	m_pVertexList[1].p = ScreenToNDC({ m_rt.right, m_rt.top });
//	m_pVertexList[1].n = Vector3(0, 0, -1);
//	m_pVertexList[1].c = Vector4(0, 1, 0, 1);
//	m_pVertexList[1].t = Vector2(1, 0);
//
//	m_pVertexList[2].p = ScreenToNDC({ m_rt.left, m_rt.bottom });
//	m_pVertexList[2].n = Vector3(0, 0, -1);
//	m_pVertexList[2].c = Vector4(0, 0, 1, 1);
//	m_pVertexList[2].t = Vector2(0, 1);
//
//	m_pVertexList[3].p = ScreenToNDC({ m_rt.right, m_rt.bottom });
//	m_pVertexList[3].n = Vector3(0, 0, -1);
//	m_pVertexList[3].c = Vector4(1, 1, 1, 1);
//	m_pVertexList[3].t = Vector2(1, 1);
//
//	m_vInitPos = (  m_pVertexList[0].p +
//				m_pVertexList[1].p +
//				m_pVertexList[2].p +
//				m_pVertexList[3].p ) / 4.0f;
//	m_pVertexList[0].p = m_pVertexList[0].p - m_vInitPos;
//	m_pVertexList[1].p = m_pVertexList[1].p - m_vInitPos;
//	m_pVertexList[2].p = m_pVertexList[2].p - m_vInitPos;
//	m_pVertexList[3].p = m_pVertexList[3].p - m_vInitPos;
//
//	//m_vPos = { 0,0,0 };
//	SetPos(m_vInitPos);
//
//	m_iNumVertex = m_pVertexList.size();
//}
void TPlaneObj::CreateVertexData()
{
	m_pVertexList.resize(4);
	m_pVertexList[0].p = { -1.0f, 1.0f, 0.0f };
	m_pVertexList[0].n = Vector3(0, 0, -1);
	m_pVertexList[0].c = Vector4(1, 0, 0, 1);
	m_pVertexList[0].t = Vector2(0, 0);

	m_pVertexList[1].p = { 1.0f, 1.0f, 0.0f };
	m_pVertexList[1].n = Vector3(0, 0, -1);
	m_pVertexList[1].c = Vector4(0, 1, 0, 1);
	m_pVertexList[1].t = Vector2(1, 0);

	m_pVertexList[2].p = { -1.0f, -1.0f, 0.0f };
	m_pVertexList[2].n = Vector3(0, 0, -1);
	m_pVertexList[2].c = Vector4(0, 0, 1, 1);
	m_pVertexList[2].t = Vector2(0, 1);

	m_pVertexList[3].p = { 1.0f, -1.0f, 0.0f };
	m_pVertexList[3].n = Vector3(0, 0, -1);
	m_pVertexList[3].c = Vector4(1, 1, 1, 1);
	m_pVertexList[3].t = Vector2(1, 1);

	m_iNumVertex = m_pVertexList.size();
}
void TPlaneObj::CreateIndexData()
{
	m_pIndexList.resize(6);
	m_pIndexList[0] = 0; m_pIndexList[1] = 1; m_pIndexList[2] = 2;
	m_pIndexList[3] = 2; m_pIndexList[4] = 1; m_pIndexList[5] = 3;
	m_iNumIndex = m_pIndexList.size();
}
