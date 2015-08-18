#include "stdafx.h"
#include "RenderPathD2D.h"

RenderPathD2D::RenderPathD2D(const CComPtr<ID2D1Geometry>& g)
	: d2dGeometry_(g)
{

}

RenderPathD2D::~RenderPathD2D()
{

}
