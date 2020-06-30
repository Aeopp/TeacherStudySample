#pragma once
#include "TTexture.h"
class TTextureMgr : public TSingleton<TTextureMgr>
{
	friend class TSingleton<TTextureMgr>;
private:
	int						m_iCurIndex;
	std::map<int, TTexture*>  m_Map;
	T_STR					m_csDefaultPath;
public:
	typedef std::map<int, TTexture*>::iterator TItor;
	void    SetDefaultPath(T_STR szPath)
	{
		m_csDefaultPath = szPath;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(ID3D11Device*, T_STR szName);
	TTexture* GetPtr(int iIndex);

private:
	TTextureMgr();
public:
	~TTextureMgr();
};

#define I_Tex TTextureMgr::GetInstance()