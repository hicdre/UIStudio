#include "stdafx.h"
#include "ResourceImageFile.h"

ResourceImageFile::ResourceImageFile()
	: ResourceStream(ImageFile)
{

}

ResourceImageFile::~ResourceImageFile()
{

}

SPtr<RenderImage> ResourceImageFile::GetRenderImage()
{
	if (!image_)
	{

	}
}
