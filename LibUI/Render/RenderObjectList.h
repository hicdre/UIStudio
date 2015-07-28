#pragma once
#include "Render/RenderObject.h"
#include <vector>

class RenderObjectList : public RenderObject
{
public:
	RenderObjectList();
	~RenderObjectList();

	virtual void Render() override;

private:
	std::vector<SPtr<RenderObject>> objects_;
};