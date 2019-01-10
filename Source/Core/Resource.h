#ifndef _RESOURCE_H_INCLUDED_
#define _RESOURCE_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class Resource
{
public:
	bool keep() const
	{
		return _keep;
	}
	void setKeep(bool keep)
	{
		_keep = keep;
	}

	void addRef()
	{
		_refs++;
	}
	void removeRef()
	{
		assert(_refs > 0);
		_refs--;
	}

	int getRefs() const
	{
		return _refs;
	}

	void setRefs(int refs)
	{
		_refs = refs;
	}

private:
	bool _keep = false;
	int _refs = 0;

};

template <class T>
class Reference
{
public:
	Reference():
		_resource(nullptr)
	{
	}

	Reference(T *resource):
		_resource(resource)
	{
		if (_resource) _resource->addRef();
	}

	Reference(const Reference<T> &reference):
		_resource(reference.resource())
	{
		if (_resource) _resource->addRef();
	}

	Reference<T> &operator =(const Reference<T> &reference)
	{
		_resource = reference.resource();
		if (_resource) _resource->addRef();
	}

	bool operator ==(const Reference<T> &reference)
	{
		return reference.resource() == _resource;
	}

	bool operator !=(const Reference<T> &reference)
	{
		return reference.resource() != _resource;
	}

	~Reference()
	{
		if (_resource) _resource->removeRef();
	}

	T *operator->() const
	{
		if (_resource) return static_cast<T *>(_resource);
	}

	T &operator*() const
	{
		if (_resource) return *static_cast<T *>(_resource);
	}

	Resource *resource() const
	{
		return _resource;
	}

	void setResource(Resource *resource)
	{
		_resource = resource;
	}

	operator bool() const
	{
		return _resource != nullptr;
	}

private:
	Resource *_resource = nullptr;

};

ST_NS_END

#endif // _RESOURCE_H_INCLUDED_
