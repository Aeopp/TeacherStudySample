#pragma once
#include "xObject.h"
class TPlaneObj : public xObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
	//void CreateScreen2NDCVertexData();
};

