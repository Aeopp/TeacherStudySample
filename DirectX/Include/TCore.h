#pragma once
#include "TWindow.h"
#include "TWrite.h"
//#include "TSoundMgr.h"
#include "TTimer.h"
#include "TInput.h"
#include "TDxState.h" 
#include "TTextureMgr.h" 

class TCore : public TWindow
{
public:
	TWrite		m_Write;
	TTimer		m_Timer;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
	virtual void	CreateDXResource() override;
	virtual void	DeleteDXResource() override;
private:
	bool TCoreInit();
	bool TCoreFrame();
	bool TCoreRender();
	bool TCoreRelease();
public:
	bool TRun();
public:
	TCore();
	virtual ~TCore();
};

