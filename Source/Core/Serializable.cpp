#include "Serializable.h"

ST_NS_BEGIN

Serializable::~Serializable()
{
	if (_document) delete _document;
}

void Serializable::openXMLFile(const string &fileName)
{
	_document = new XMLDocument();
	_document->LoadFile(fileName.c_str());
}

ST_NS_END
