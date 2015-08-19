#pragma once
#include "Model/UIObject.h"


class UIObjectCollection : public Object
{
public:
	UIObjectCollection(const SPtr<UIObject>& owner);
	~UIObjectCollection();

	SPtr<UIObject> GetOwner();

	uint32 GetIndexOf(const SPtr<UIObject>& obj);

	uint32 GetCount() const { return objects_.size(); }
	bool IsEmpty() const { return objects_.empty(); }

	typedef std::vector<SPtr<UIObject>>::iterator iterator;
	typedef std::vector<SPtr<UIObject>>::const_iterator const_iterator;
	iterator begin() { return objects_.begin(); }
	const_iterator cbegin() const { return objects_.cbegin(); }
	iterator end() { return objects_.end(); }
	const_iterator cend() const { return objects_.cend(); }
	
	void Add(const SPtr<UIObject>& obj);
	void Remove(const SPtr<UIObject>& obj);
private:
	SPtr<UIObject> InternalRemove(const SPtr<UIObject>& obj);
	std::vector<SPtr<UIObject>> objects_;
	WPtr<UIObject> owner_;
};