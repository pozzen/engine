#ifndef _SERIALIZABLE_H_INCLUDED_
#define _SERIALIZABLE_H_INCLUDED_

#include "Engine.h"
#include "tinyxml2.h"

using namespace tinyxml2;

ST_NS_BEGIN

class Serializable
{
public:
	~Serializable();

protected:
	void openXMLFile(const string &fileName);

	XMLDocument *_document = nullptr;

};

ST_NS_END

#endif // _SERIALIZABLE_H_INCLUDED_
