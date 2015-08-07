#pragma once
#include "Base/object.h"
#include "Base/Geom/size.h"

class PropertySize : public Object
{
public:
	PropertySize();
	PropertySize(int w, int h);
	~PropertySize();

	int width() const { return size_.width(); }
	int height() const { return size_.height(); }
	const base::Size& size() const { return size_; }

	void SetSize(int width, int height) {
		size_.SetSize(width, height);
	}

private:
	base::Size size_;
};