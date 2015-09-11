#pragma once
#include "Resource/ResourceStream.h"

class RenderImage;
class ResourceImageFile : public ResourceStream
{
public:
	ResourceImageFile();
	~ResourceImageFile();

	SPtr<RenderImage> GetRenderImage();


private:
	SPtr<RenderImage> image_;
};