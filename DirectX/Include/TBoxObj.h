#pragma once
#include "TObject.h"
class TBoxObj : public TObject
{
public:
	virtual void	CreateVertexData();
	virtual void	CreateIndexData();
};

