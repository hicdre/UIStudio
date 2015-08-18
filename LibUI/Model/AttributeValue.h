#pragma once
#include "Base/base_defines.h"
#include "Base/object.h"
#include <string>
#include <stdint.h>
#include <cassert>
#include <vector>
#include <unordered_map>

enum AttributeValueType
{
	AttributeTypeNull = 0,
	AttributeTypeBool,
	AttributeTypeInt32,
	AttributeTypeUInt32,
	AttributeTypeInt64,
	AttributeTypeUInt64,
	AttributeTypeFloat,
	AttributeTypeDouble,
	AttributeTypeObject,
	AttributeTypeString,
	AttriubteTypeList,
	AttributeTypeDictionary,

	AttributeTypeLength,
};

class AttributeValueList;
class AttributeValueDictionary;
class AttributeValue : public Object
{	
public:
	AttributeValue() : type_(AttributeTypeNull) {}
	AttributeValue(bool v) { SetBoolValue(v); }
	AttributeValue(int32_t v) { SetInt32Value(v); }
	AttributeValue(uint32_t v) { SetUInt32Value(v); }
	AttributeValue(int64_t v) { SetInt64Value(v); }
	AttributeValue(uint64_t v) { SetUInt64Value(v); }
	AttributeValue(float v) { SetFloatValue(v); }
	AttributeValue(double v) { SetDoubleValue(v); }
	AttributeValue(const SPtr<Object>& v) { SetObjectValue(v); }
	AttributeValue(const SPtr<Object>& v, AttributeValueType type) { SetObjectValue(v, type); }
	AttributeValue(const std::wstring& v) { SetStringValue(v); }
	AttributeValue(const std::string& v);

	inline bool IsBoolValue() const { return type_ == AttributeTypeBool; }
	inline bool IsInt32Value() const { return type_ == AttributeTypeInt32; }
	inline bool IsUInt32Value() const { return type_ == AttributeTypeUInt32; }
	inline bool IsInt64Value() const { return type_ == AttributeTypeInt64; }
	inline bool IsUInt64Value() const { return type_ == AttributeTypeUInt64; }
	inline bool IsFloatValue() const { return type_ == AttributeTypeFloat; }
	inline bool IsDoubleValue() const { return type_ == AttributeTypeDouble; }
	inline bool IsObjectValue() const { return type_ == AttributeTypeObject || IsObjectDerivedValue(type_); }
	inline bool IsStringValue() const { return type_ == AttributeTypeString; }
	inline bool IsListValue() const { return type_ == AttriubteTypeList; }
	inline bool IsDictionaryValue() const { return type_ == AttributeTypeDictionary; }
	inline bool IsLengthValue() const { return type_ == AttributeTypeLength; }

	inline bool IsObjectDerivedValue(AttributeValueType type) const { return type == AttributeTypeLength; }

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
	//inline AttributeValueList* GetListValue() const { assert(IsListValue());	return listValue_; }
	//inline AttributeValueDictionary* GetDictonaryValue() const { assert(IsListValue());	return dictValue_; }
	

	void SetBoolValue(bool v);
	void SetInt32Value(int32_t v);
	void SetUInt32Value(uint32_t v);
	void SetInt64Value(int64_t v);
	void SetUInt64Value(uint64_t v);
	void SetFloatValue(float v);
	void SetDoubleValue(double v);
	void SetObjectValue(const SPtr<Object>& v);
	void SetObjectValue(const SPtr<Object>& v, AttributeValueType type);
	void SetStringValue(const std::wstring& s);
	void SetStringValue(const std::string& s);
// 	void SetListValue();
// 	void SetListValue(own AttributeValue* v);
// 	void SetListValue(const SPtr<Object>& v);
// 	void SetDictionaryValue();

	std::wstring ToUTF16() const;

	bool IsEqual(const AttributeValue* other) const;

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
		//AttributeValueList* listValue_;
		//AttributeValueDictionary* dictValue_;
	};
	AttributeValueType type_;
};

// class AttributeValueList
// {
// public:
// 	AttributeValueList();
// 	~AttributeValueList();
// 
// 	void Clear();
// 
// 	// Returns the number of Values in this list.
// 	size_t GetSize() const { return list_.size(); }
// 
// 	// Returns whether the list is empty.
// 	bool empty() const { return list_.empty(); }
// 
// 	void Append(const SPtr<AttributeValue>& v);
// 	void Append(const SPtr<Object>& v);
// 
// 	SPtr<AttributeValue> Get(int index) const;
// 	
// 	bool IsEqual(AttributeValueList* other) const;
// 
// 
// private:
// 	std::vector<SPtr<AttributeValue>> list_;
// };


// class AttributeValueDictionary
// {
// public:
// 	AttributeValueDictionary();
// 	~AttributeValueDictionary();
// 
// 	void Clear();
// 
// 	bool HasKey(const std::string& key) const;	
// 
// 	// Returns the number of Values in this dictionary.
// 	size_t size() const { return dictionary_.size(); }
// 
// 	// Returns whether the dictionary is empty.
// 	bool empty() const { return dictionary_.empty(); }
// 
// 
// 	void Set(const std::string& path, own AttributeValue* in_value);
// 
// 	void SetBoolean(const std::string& path, bool in_value);
// 	void SetInteger(const std::string& path, int in_value);
// 	void SetDouble(const std::string& path, double in_value);
// 	void SetString(const std::string& path, const std::string& in_value);
// 	void SetString(const std::string& path, const std::wstring& in_value);
// 
// 	bool Get(const std::string& path, const AttributeValue** out_value) const;
// 	bool Get(const std::string& path, AttributeValue** out_value);
// 
// 	// These are convenience forms of Get().  The value will be retrieved
// 	// and the return value will be true if the path is valid and the value at
// 	// the end of the path can be returned in the form specified.
// 	bool GetBoolean(const std::string& path, bool* out_value) const;
// 	bool GetInteger(const std::string& path, int* out_value) const;
// 	bool GetDouble(const std::string& path, double* out_value) const;
// 	bool GetString(const std::string& path, std::string* out_value) const;
// 	bool GetString(const std::string& path, std::wstring* out_value) const;
// 	bool GetDictionary(const std::string& path, AttributeValueDictionary** out_value);
// 	bool GetDictionary(const std::string& path,
// 		const AttributeValueDictionary** out_value) const;
// 
// 	bool Remove(const std::string& path, own AttributeValue** out_value);
// 
// 	bool IsEqual(const AttributeValueDictionary* other) const;
// private:
// 	void SetInternal(const std::string& path, own AttributeValue* in_value);
// 	bool GetInteranl(const std::string& path, const AttributeValue** out_value) const;
// 	bool GetInteranl(const std::string& path, AttributeValue** out_value);
// 	bool RemoveInternal(const std::string& key, own AttributeValue** out_value);
// 
// 	std::unordered_map<std::string, AttributeValue*> dictionary_;
// };