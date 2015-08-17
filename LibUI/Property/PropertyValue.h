#pragma once
#include "Base/base_defines.h"
#include "Base/object.h"
#include <string>
#include <stdint.h>
#include <cassert>
#include <vector>
#include <unordered_map>

enum PropertyValueType
{
	PropertyTypeNull = 0,
	PropertyTypeBool,
	PropertyTypeInt32,
	PropertyTypeUInt32,
	PropertyTypeInt64,
	PropertyTypeUInt64,
	PropertyTypeFloat,
	PropertyTypeDouble,
	PropertyTypeObject,
	PropertyTypeString,
	PropertyTypeList,
	PropertyTypeDictionary,

	PropertyTypeLength,
};

class PropertyList;
class PropertyDictionary;
class PropertyValue
{	
public:
	PropertyValue() : type_(PropertyTypeNull) {}
	PropertyValue(bool v) { SetBoolValue(v); }
	PropertyValue(int32_t v) { SetInt32Value(v); }
	PropertyValue(uint32_t v) { SetUInt32Value(v); }
	PropertyValue(int64_t v) { SetInt64Value(v); }
	PropertyValue(uint64_t v) { SetUInt64Value(v); }
	PropertyValue(float v) { SetFloatValue(v); }
	PropertyValue(double v) { SetDoubleValue(v); }
	PropertyValue(const SPtr<Object>& v) { SetObjectValue(v); }
	PropertyValue(const std::wstring& v) { SetStringValue(v); }
	PropertyValue(const std::string& v);

	inline bool IsBoolValue() const { return type_ == PropertyTypeBool; }
	inline bool IsInt32Value() const { return type_ == PropertyTypeInt32; }
	inline bool IsUInt32Value() const { return type_ == PropertyTypeUInt32; }
	inline bool IsInt64Value() const { return type_ == PropertyTypeInt64; }
	inline bool IsUInt64Value() const { return type_ == PropertyTypeUInt64; }
	inline bool IsFloatValue() const { return type_ == PropertyTypeFloat; }
	inline bool IsDoubleValue() const { return type_ == PropertyTypeDouble; }
	inline bool IsObjectValue() const { return type_ == PropertyTypeObject; }
	inline bool IsStringValue() const { return type_ == PropertyTypeString; }
	inline bool IsListValue() const { return type_ == PropertyTypeList; }
	inline bool IsDictionaryValue() const { return type_ == PropertyTypeDictionary; }
	inline bool IsLengthValue() const { return type_ == PropertyTypeLength; }

	inline bool GetBoolValue() const {assert(IsBoolValue());	return boolValue_;}
	inline int32_t GetInt32Value() const { assert(IsInt32Value());	return int32Value_; }
	inline uint32_t GetUInt32Value() const { assert(IsUInt32Value());	return uint32Value_; }
	inline int64_t GetInt64Value() const { assert(IsInt64Value());	return int64Value_; }
	inline uint64_t GetUInt64Value() const { assert(IsUInt64Value());	return uint64Value_; }
	inline float GetFloatValue() const { assert(IsFloatValue());	return floatValue_; }
	inline double GetDoubleValue() const { assert(IsDoubleValue());	return doubleValue_; }
	inline SPtr<Object> GetObjectValue() const { assert(IsObjectValue());	return objectValue_; }
	inline std::wstring GetUTF16Value() const { assert(IsStringValue());	return *utf16Value_; }
	std::string GetUTF8Value() const;
	inline PropertyList* GetListValue() const { assert(IsListValue());	return listValue_; }
	inline PropertyDictionary* GetDictonaryValue() const { assert(IsListValue());	return dictValue_; }
	

	void SetBoolValue(bool v);
	void SetInt32Value(int32_t v);
	void SetUInt32Value(uint32_t v);
	void SetInt64Value(int64_t v);
	void SetUInt64Value(uint64_t v);
	void SetFloatValue(float v);
	void SetDoubleValue(double v);
	void SetObjectValue(const SPtr<Object>& v);
	void SetStringValue(const std::wstring& s);
	void SetStringValue(const std::string& s);
	void SetListValue();
	void SetListValue(own PropertyValue* v);
	void SetListValue(const SPtr<Object>& v);
	void SetDictionaryValue();

	std::wstring ToUTF16() const;

	bool IsEqual(const PropertyValue* other) const;

private:
	void Clear();
	union {
		bool boolValue_;
		int32_t int32Value_;
		uint32_t uint32Value_;
		int64_t	int64Value_;
		uint64_t uint64Value_;
		float	floatValue_;
		double	doubleValue_;
		Object* objectValue_;
		std::wstring* utf16Value_;
		PropertyList* listValue_;
		PropertyDictionary* dictValue_;
	};
	PropertyValueType type_;
};

class PropertyList
{
public:
	PropertyList();
	~PropertyList();

	void Clear();

	// Returns the number of Values in this list.
	size_t GetSize() const { return list_.size(); }

	// Returns whether the list is empty.
	bool empty() const { return list_.empty(); }

	void Append(own PropertyValue* v);
	void Append(const SPtr<Object>& v);

	PropertyValue* Get(int index) const;
	
	bool IsEqual(PropertyList* other) const;


private:
	std::vector<PropertyValue*> list_;
};


class PropertyDictionary
{
public:
	PropertyDictionary();
	~PropertyDictionary();

	void Clear();

	bool HasKey(const std::string& key) const;	

	// Returns the number of Values in this dictionary.
	size_t size() const { return dictionary_.size(); }

	// Returns whether the dictionary is empty.
	bool empty() const { return dictionary_.empty(); }


	void Set(const std::string& path, own PropertyValue* in_value);

	void SetBoolean(const std::string& path, bool in_value);
	void SetInteger(const std::string& path, int in_value);
	void SetDouble(const std::string& path, double in_value);
	void SetString(const std::string& path, const std::string& in_value);
	void SetString(const std::string& path, const std::wstring& in_value);

	bool Get(const std::string& path, const PropertyValue** out_value) const;
	bool Get(const std::string& path, PropertyValue** out_value);

	// These are convenience forms of Get().  The value will be retrieved
	// and the return value will be true if the path is valid and the value at
	// the end of the path can be returned in the form specified.
	bool GetBoolean(const std::string& path, bool* out_value) const;
	bool GetInteger(const std::string& path, int* out_value) const;
	bool GetDouble(const std::string& path, double* out_value) const;
	bool GetString(const std::string& path, std::string* out_value) const;
	bool GetString(const std::string& path, std::wstring* out_value) const;
	bool GetDictionary(const std::string& path, PropertyDictionary** out_value);
	bool GetDictionary(const std::string& path,
		const PropertyDictionary** out_value) const;

	bool Remove(const std::string& path, own PropertyValue** out_value);

	bool IsEqual(const PropertyDictionary* other) const;
private:
	void SetInternal(const std::string& path, own PropertyValue* in_value);
	bool GetInteranl(const std::string& path, const PropertyValue** out_value) const;
	bool GetInteranl(const std::string& path, PropertyValue** out_value);
	bool RemoveInternal(const std::string& key, own PropertyValue** out_value);

	std::unordered_map<std::string, PropertyValue*> dictionary_;
};