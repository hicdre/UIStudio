#pragma once
#include "Resource/ResourceProvider.h"


class ResourceFolderProvider : public ResourceProvider
{
public:
	ResourceFolderProvider();
	~ResourceFolderProvider();

	virtual SPtr<Object> GetResource(const base::Uri& uri) override;

private:
	std::wstring baseFolderPath_;
};