#pragma once
#include "base/object.h"
#include <vector>

template <class T>
class AttributeUnitCollection : public Object
{	
public:
	typedef std::vector<T> ContainerType;
	typedef typename ContainerType::iterator iterator;
	typedef typename ContainerType::const_iterator const_iterator;

	AttributeUnitCollection() {}
	~AttributeUnitCollection() {}

	iterator begin() { return vector_.begin(); }
	iterator end() { return vector_.end(); }
	const_iterator cbegin() const { return vector_.cbegin(); }
	const_iterator cend() const { return vector_.cend(); }

	bool IsEmpty() const { return vector_.empty(); }
	uint32 GetCount() const { return vector_.size(); }
	const T& at(uint32 index) const { return vector_.at(index); }

	bool IsEqual(AttributeUnitCollection* other) const
	{
		if (other->GetCount() != GetCount())
			return false;
		for (uint32 i = 0; i < vector_.size(); i++)
		{
			if (vector_[i] != other->vector_[i])
				return false;
		}
		return true;
	}

private:
	ContainerType vector_;
};

typedef AttributeUnitCollection<float> AttributeFloatCollection;