#pragma once
#include "Delegate/Delegate.h"
#include "Resource/ResourceProvider.h"
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* Get();

	void RegisterResourceProvider(const std::string& scheme, const SPtr<ResourceProvider>& provider);

	SPtr<Object> GetResource(const base::Uri& uri);
private:
	std::map<std::string, SPtr<ResourceProvider>> provider_map_;

};