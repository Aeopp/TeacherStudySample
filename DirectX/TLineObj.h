#pragma once
#include "TObject.h"
class TLineObj : public TObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	virtual bool	Draw(ID3D11DeviceContext* pContext,
		Vector3 vStart,
		Vector3 vEnd,
		Vector4 Color);
};

class TDirectionLineObj : public TObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
};