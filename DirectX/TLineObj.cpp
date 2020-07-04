#include "TLineObj.h"
bool TLineObj::Draw(ID3D11DeviceContext* pContext,
	Vector3 vStart,
	Vector3 vEnd,
	Vector4 Color)
{
	m_pVertexList[0].p = vStart;
	m_pVertexList[0].c = Color;
	m_pVertexList[1].p = vEnd;
	m_pVertexList[1].c = Color;
	pContext->UpdateSubresource(m_dxObj.m_pVertexBuffer.Get(),
		0, NULL, &m_pVertexList.at(0), 0, 0);
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	return Render();
}
void TLineObj::CreateVertexData()
{
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;

	m_pVertexList.resize(2);
	m_pVertexList[0].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[0].n = Vector3(0, 0, 1);
	m_pVertexList[0].c = Vector4(1, 0, 0, 1);
	m_pVertexList[0].t = Vector2(0, 0);

	m_pVertexList[1].p = { 1.0f, 0.0f, 0.0f };
	m_pVertexList[1].n = Vector3(0, 0, 1);
	m_pVertexList[1].c = Vector4(0, 1, 0, 1);
	m_pVertexList[1].t = Vector2(1, 0);
	m_iNumVertex = m_pVertexList.size();
}
void TLineObj::CreateIndexData()
{
	m_pIndexList.resize(2);
	m_pIndexList[0] = 0;
	m_pIndexList[1] = 1;

	m_iNumIndex = m_pIndexList.size();
}
void TDirectionLineObj::CreateVertexData()
{
	m_dxObj.m_iPrimitiveType = D3D_PRIMITIVE_TOPOLOGY_LINELIST;

	m_pVertexList.resize(6);
	m_pVertexList[0].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[0].n = Vector3(0, 0, 1);
	m_pVertexList[0].c = Vector4(1, 0, 0, 1);
	m_pVertexList[0].t = Vector2(0, 0);

	m_pVertexList[1].p = { 100000.0f, 0.0f, 0.0f };
	m_pVertexList[1].n = Vector3(0, 0, 1);
	m_pVertexList[1].c = Vector4(1, 0, 0, 1);
	m_pVertexList[1].t = Vector2(1, 0);

	m_pVertexList[2].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[2].n = Vector3(0, 0, 1);
	m_pVertexList[2].c = Vector4(0, 1, 0, 1);
	m_pVertexList[2].t = Vector2(0, 0);

	m_pVertexList[3].p = { 0, 100000.0f, 0.0f };
	m_pVertexList[3].n = Vector3(0, 0, 1);
	m_pVertexList[3].c = Vector4(0, 1, 0, 1);
	m_pVertexList[3].t = Vector2(1, 0);

	m_pVertexList[4].p = { 0.0f, 0.0f, 0.0f };
	m_pVertexList[4].n = Vector3(0, 0, 1);
	m_pVertexList[4].c = Vector4(0, 0, 1, 1);
	m_pVertexList[4].t = Vector2(0, 0);

	m_pVertexList[5].p = { 0.0f, 0.0f, 100000.0f };
	m_pVertexList[5].n = Vector3(0, 0, 1);
	m_pVertexList[5].c = Vector4(0, 0, 1, 1);
	m_pVertexList[5].t = Vector2(1, 0);
	m_iNumVertex = m_pVertexList.size();
}
void TDirectionLineObj::CreateIndexData()
{
	m_pIndexList.resize(6);
	m_pIndexList[0] = 0;
	m_pIndexList[1] = 1;
	m_pIndexList[2] = 2;
	m_pIndexList[3] = 3;
	m_pIndexList[4] = 4;
	m_pIndexList[5] = 5;
	m_iNumIndex = m_pIndexList.size();
}