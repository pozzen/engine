#include "ResourceManager.h"

ST_NS_BEGIN

unordered_map<string, Resource *> ResourceManager::_resources;

void ResourceManager::remove(string name)
{
	ResourceManager::_resources.erase(name);
}

void ResourceManager::clear()
{
	for (unordered_map<string, Resource *>::iterator iter = _resources.begin(); iter != _resources.end(); iter++)
		delete iter->second;
	ResourceManager::_resources.clear();
}

void ResourceManager::purge()
{
	for (unordered_map<string, Resource *>::iterator iter = _resources.begin(); iter != _resources.end(); iter++)
	{
		if (iter->second->getRefs() == 0)
		{
			ResourceManager::_resources.erase(iter);
		}
	}
}

ST_NS_END
