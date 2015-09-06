#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::Get()
{
	static ResourceManager inst;
	return &inst;
}

void ResourceManager::RegisterResourceProvider(const std::string& scheme, const SPtr<ResourceProvider>& provider)
{
	provider_map_[scheme] = provider;
}

SPtr<Object> ResourceManager::GetResource(const base::Uri& uri)
{
	auto it = provider_map_.find(uri.scheme());
	if (it == provider_map_.end())
		return NULL;
	return it->second->GetResource(uri);
}
