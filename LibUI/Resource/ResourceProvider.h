#pragma once
#include "base/object.h"
#include "base/Uri.h"

//ResourceImage
//ResourceStringList
//ResourceLayout
class ResourceProvider : public Object
{
public:
	ResourceProvider();
	~ResourceProvider();

	virtual SPtr<Object> GetResource(const base::Uri& uri) = 0;
};