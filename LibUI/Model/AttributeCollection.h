#pragma once
#include "Model/AttributeValue.h"
#include "Model/AttributeLength.h"
#include "Model/AttributePaint.h"
#include "Delegate/Delegate.h"
#include <unordered_map>
#include <functional>

struct AttributeEventArgs : public Object
{
	AttributeEventArgs(const std::string& name, const SPtr<AttributeValue>& value)
		: name(name), value(value) {}
	std::string name;
	SPtr<AttributeValue> value;
};

class UIObject;
class AttributeCollection : public Object
{
	typedef std::unordered_map<std::string, SPtr<AttributeValue>> AttributeMap;
public:
	AttributeCollection(const SPtr<UIObject>& owner);
	~AttributeCollection();

	static void InitDefaultMap();

	uint32 GetCount() const { return attribute_map_.size(); }
	void Clear();

	bool HasAttribute(const std::string& attributeName) const;
	SPtr<AttributeValue> GetAttribute(const std::string& attributeName) const;
	
	void SetAttribute(const std::string& attributeName, const SPtr<AttributeValue>& value);
	void SetAttributeIfDifferent(const std::string& attributeName, const SPtr<AttributeValue>& value,
		const std::function<void(void)>& setCallback);

	bool GetAttributeBool(const std::string& attributeName) const;
	int32 GetAttributeInt(const std::string& attributeName) const;
	uint32 GetAttributeUInt(const std::string& attributeName) const;
	float GetAttributeFloat(const std::string& attributeName) const;
	double GetAttributeDouble(const std::string& attributeName) const;
	std::wstring GetAttributeUTF16(const std::string& attributeName) const;
	std::string GetAttributeUTF8(const std::string& attributeName) const;
	SPtr<AttributeLength> GetAttributeLength(const std::string& attributeName) const;
	SPtr<AttributePaint> GetAttributePaint(const std::string& attributeName) const;

	void SetAttributeBool(const std::string& attributeName, bool value);
	void SetAttributeBoolIfDifferent(const std::string& attributeName, bool value,
		const std::function<void(void)>& setCallback);
	void SetAttributeInt(const std::string& attributeName, int value);
	void SetAttributeIntIfDifferent(const std::string& attributeName, int value, 
		const std::function<void(void)>& setCallback);
	void SetAttributeUInt(const std::string& attributeName, uint32 value);
	void SetAttributeUIntIfDifferent(const std::string& attributeName, uint32 value,
		const std::function<void(void)>& setCallback);
	void SetAttributeFloat(const std::string& attributeName, float value);
	void SetAttributeFloatIfDifferent(const std::string& attributeName, float value,
		const std::function<void(void)>& setCallback);
	void SetAttributeDouble(const std::string& attributeName, double value);
	void SetAttributeDoubleIfDifferent(const std::string& attributeName, double value,
		const std::function<void(void)>& setCallback);
	void SetAttributeString(const std::string& attributeName, const std::string& value);
	void SetAttributeStringIfDifferent(const std::string& attributeName, const std::string& value,
		const std::function<void(void)>& setCallback);
	void SetAttributeString(const std::string& attributeName, const std::wstring& value);
	void SetAttributeStringIfDifferent(const std::string& attributeName, const std::wstring& value,
		const std::function<void(void)>& setCallback);
	void SetAttributeLength(const std::string& attributeName, const SPtr<AttributeLength>& value);
	void SetAttributeLengthIfDifferent(const std::string& attributeName, const SPtr<AttributeLength>& value,
		const std::function<void(void)>& setCallback);
	void SetAttributePaint(const std::string& attributeName, const SPtr<AttributePaint>& value);
	void SetAttributePaintIfDifferent(const std::string& attributeName, const SPtr<AttributePaint>& value,
		const std::function<void(void)>& setCallback);

	void RemoveAttribute(const std::string& attributeName);

	typedef AttributeMap::iterator iterator;
	typedef AttributeMap::const_iterator const_iterator;
	iterator begin() { return attribute_map_.begin(); }
	iterator end() { return attribute_map_.end(); }
	const_iterator cbegin() const { return attribute_map_.cbegin(); }
	const_iterator cend() const { return attribute_map_.cend(); }

	Event<void(const SPtr<UIObject>&, const SPtr<AttributeEventArgs>&)> EventAttributechanged;
private:
	void OnAttributeChanged(const std::string& name, const SPtr<AttributeValue>& value);
	AttributeMap attribute_map_;
	static AttributeMap default_attribute_map_;
	WPtr<UIObject> owner_;
};