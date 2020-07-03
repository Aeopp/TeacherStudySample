#pragma once
#include "TObject.h"
class TPlaneObj : public TObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	//void CreateScreen2NDCVertexData();
};

