#include "TTextureMgr.h"

bool	TTextureMgr::Init()
{
	return true;
}
bool	TTextureMgr::Frame()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Frame();
	}
	return true;
}
bool	TTextureMgr::Render()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Render();
	}
	return true;
}


int		TTextureMgr::Load(ID3D11Device* pd3dDevice, T_STR szLoadName)
{
	// ../../../data/sound/xx.mp3
	TCHAR szDirve[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDirve, szDir, szName, szExt);
	T_STR szFileName = szName;
	szFileName += szExt;
	for (TItor itor = m_Map.begin();
		itor != m_Map.end(); itor++)
	{
		TTexture* pData = (*itor).second;
		if (pData->m_csName == szFileName)
		{
			return (*itor).first;
		}
	}

	TTexture* pData = nullptr;
	SAFE_NEW(pData, TTexture);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(pd3dDevice,szLoadName))
	{
		m_Map.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}

TTexture* TTextureMgr::GetPtr(int iIndex)
{
	TItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool TTextureMgr::Release()
{
	TTexture* pData = nullptr;
	for (TItor iter = m_Map.begin();
		iter != m_Map.end();
		iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	return true;
}
TTextureMgr::TTextureMgr()
{
	m_iCurIndex = 0;
	m_csDefaultPath = L"../../../data/";
	Init();
}
TTextureMgr::~TTextureMgr()
{
	Release();
}