#ifndef _RESOURCEMANAGER_H_INCLUDED_
#define _RESOURCEMANAGER_H_INCLUDED_

#include "Engine.h"
#include "Resource.h"

ST_NS_BEGIN

class ResourceManager
{
private:
	static unordered_map<string, Resource *> _resources;

public:
	template <class T>
	static Reference<T> get(string name)
	{
		if (_resources.find(name) == _resources.end())
		{
			cout<<"Resource '"<<name<<"' not cached."<<endl;
			return Reference<T>(nullptr);
		}
		cout<<"Resource '"<<name<<"' loaded from cache."<<endl;
		return Reference<T>(static_cast<T *>(_resources[name]));
	}

	template <class T>
	static Reference<T> add(string name, T *resource)
	{
		_resources[name] = resource;
		return Reference<T>(resource);
	}

	static void remove(string name);
	static void clear();
	static void purge();

};

ST_NS_END

#endif // _RESOURCEMANAGER_H_INCLUDED_
