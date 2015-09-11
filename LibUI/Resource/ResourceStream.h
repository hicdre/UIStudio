#pragma once
#include "base/object.h"
#include <string>

class RenderImage;
class ResourceStream : public Object
{
public:
	enum Type {
		ImageFile,
	};
	ResourceStream(Type type);
	~ResourceStream();

	Type stream_type() const { return stream_type_; }
	
	virtual uint64 GetSize() = 0;
	
private:
	Type stream_type_;
	
};