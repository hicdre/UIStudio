#pragma once
#include "Base/object.h"
#include "Base/color.h"

class RenderPaintServer : public Object
{
public:
	RenderPaintServer();
	~RenderPaintServer();

	bool IsNone() const { return none_; }
	base::Color GetColor() const { return color_; }
	void SetNone();
	void SetColor(base::Color c);
private:
	base::Color color_;
	bool none_;
};