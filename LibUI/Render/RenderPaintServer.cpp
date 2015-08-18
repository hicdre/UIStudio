#include "stdafx.h"
#include "RenderPaintServer.h"

RenderPaintServer::RenderPaintServer()
	: none_(true)
	, color_(base::Color_Black)
{

}

RenderPaintServer::~RenderPaintServer()
{

}

void RenderPaintServer::SetNone()
{
	none_ = true;
}

void RenderPaintServer::SetColor(base::Color c)
{
	none_ = false;
	color_ = c;
}
