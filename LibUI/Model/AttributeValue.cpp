#include "stdafx.h"
#include "AttributeValue.h"
#include "AttributeLength.h"

#include "Base/utils.h"

AttributeValue::AttributeValue( const std::string& v )
{
	SetStringValue(utils::MultiByteToWide(v));
}


void AttributeValue::SetBoolValue( bool v )
{
	Clear();  boolValue_ = v;  type_ = AttributeTypeBool;
}

void AttributeValue::SetInt32Value( int32_t v )
{
	Clear();  int32Value_ = v;  type_ = AttributeTypeInt32;
}

void AttributeValue::SetUInt32Value( uint32_t v )
{
	Clear();  uint32Value_ = v;  type_ = AttributeTypeUInt32;
}

void AttributeValue::SetInt64Value( int64_t v )
{
	Clear();  int64Value_ = v;  type_ = AttributeTypeInt64;
}

void AttributeValue::SetUInt64Value( uint64_t v )
{
	Clear();  uint64Value_ = v;  type_ = AttributeTypeUInt64;
}

void AttributeValue::SetFloatValue( float v )
{
	Clear();  floatValue_ = v;  type_ = AttributeTypeFloat;
}

void AttributeValue::SetDoubleValue( double v )
{
	Clear();  doubleValue_ = v;  type_ = AttributeTypeDouble;
}

void AttributeValue::SetObjectValue( const SPtr<Object>& v )
{
	Clear();  
	objectValue_ = v.get(); 
	if (objectValue_)
		objectValue_->AddRef();
	type_ = AttributeTypeObject;
}


void AttributeValue::SetObjectValue(const SPtr<Object>& v, AttributeValueType type)
{
	if (!IsObjectDerivedValue(type))
		type = AttributeTypeObject;
	Clear();
	objectValue_ = v.get();
	if (objectValue_)
		objectValue_->AddRef();
	type_ = type;
}

void AttributeValue::SetStringValue(const std::wstring& s)
{
	Clear();
	utf16Value_ = new std::wstring(s);
	type_ = AttributeTypeString;
}

void AttributeValue::SetStringValue( const std::string& s )
{
	SetStringValue(utils::MultiByteToWide(s));
}

// void AttributeValue::SetListValue()
// {
// 	Clear();
// 	listValue_ = new AttributeValueList;
// 	type_ = AttriubteTypeList;
// }
// 
// void AttributeValue::SetListValue(const SPtr<Object>& v)
// {
// 	Clear();
// 	listValue_ = new AttributeValueList;
// 	listValue_->Append(v);
// 	type_ = AttriubteTypeList;
// 
// }
//
// void AttributeValue::SetListValue(own AttributeValue* v)
// {
// 	Clear();
// 	listValue_ = new AttributeValueList;
// 	listValue_->Append(v);
// 	type_ = AttriubteTypeList;
// }
// 
// void AttributeValue::SetDictionaryValue()
// {
// 	Clear();
// 	dictValue_ = new AttributeValueDictionary;	
// 	type_ = AttriubteTypeList;
// }


std::wstring AttributeValue::ToUTF16() const
{
	switch (type_) {
	case AttributeTypeNull:
		return L"(Null)";
	case AttributeTypeBool:
		return boolValue_ ? L"true" : L"false";
	case AttributeTypeInt32:
		{
			wchar_t buffer[2 * _MAX_INT_DIG];

			std::swprintf(buffer, sizeof (buffer) / sizeof (buffer[0]),
				L"%d", int32Value_);
			return std::wstring(buffer);
		}		
	case AttributeTypeUInt32:
		{
			wchar_t buffer[2 * _MAX_INT_DIG];

			std::swprintf(buffer, sizeof (buffer) / sizeof (buffer[0]),
				L"%u", uint32Value_);
			return std::wstring(buffer);
		}
	case AttributeTypeInt64:
		return std::to_wstring(int64Value_);
	case AttributeTypeUInt64:
		return std::to_wstring(uint64Value_);
	case AttributeTypeFloat:
		return std::to_wstring((long double)floatValue_);
	case AttributeTypeDouble:
		return std::to_wstring((long double)doubleValue_);
	case AttributeTypeObject:
		assert(0);
		return L"(Object)";
	case AttributeTypeString:
		assert(utf16Value_);
		return *utf16Value_;
	default:
		return L"(Unknown)";
	}
}

void AttributeValue::Clear()
{
	if (IsObjectValue()) 
	{
		if (objectValue_)
			objectValue_->Release();			
	} 
	else if (IsStringValue())
	{
		if (utf16Value_)
			delete utf16Value_;
	}
// 	else if (IsListValue())
// 	{
// 		if (listValue_)
// 			delete listValue_;
// 	}
// 	else if (IsDictionaryValue())
// 	{
// 		if (dictValue_)
// 			delete dictValue_;
// 	}

	uint64Value_ = 0;
	type_ = AttributeTypeNull;
}

std::string AttributeValue::GetUTF8Value() const
{
	return utils::WideToMultiByte(GetUTF16Value());
}

bool AttributeValue::IsEqual(const AttributeValue* other) const
{
	if (other->type_ != type_)
		return false;
	switch (type_) {
	case AttributeTypeNull:
		return true;
	case AttributeTypeBool:
	case AttributeTypeInt32:
	case AttributeTypeUInt32:
	case AttributeTypeInt64:
	case AttributeTypeUInt64:
	case AttributeTypeFloat:
	case AttributeTypeDouble:
		return uint64Value_ == other->uint64Value_;
	case AttributeTypeObject:
		return objectValue_ == other->objectValue_;
	case AttributeTypeString:
		return *utf16Value_ == *other->utf16Value_;
// 	case AttriubteTypeList:
// 		return listValue_->IsEqual(other->listValue_);
// 	case AttributeTypeDictionary:
// 		return dictValue_->IsEqual(other->dictValue_);
	case AttributeTypeLength:
		return (static_cast<AttributeLength*>(objectValue_))
					->IsEqual(static_cast<AttributeLength*>(other->objectValue_));
	}
	return true;	
}

// AttributeValueList::AttributeValueList()
// {
// 
// }
// 
// AttributeValueList::~AttributeValueList()
// {
// 	Clear();
// }
// 
// 
// void AttributeValueList::Clear()
// {
// 	for (auto iter = list_.begin(); iter != list_.end(); iter++)
// 	{
// 		delete *iter;
// 	}
// 	list_.clear();
// }
// 
// 
// void AttributeValueList::Append(own AttributeValue* v)
// {
// 	list_.push_back(v);
// }
// 
// void AttributeValueList::Append(const SPtr<Object>& v)
// {
// 	Append(new AttributeValue(v));
// }
// 
// bool AttributeValueList::IsEqual(AttributeValueList* other) const
// {
// 	if (GetSize() != other->GetSize())
// 		return false;
// 	size_t count = list_.size();
// 	for (int i = 0; i < count; i++)
// 	{
// 		AttributeValue* a = list_[i];
// 		AttributeValue* b = other->list_[i];		
// 		if (!a->IsEqual(b))
// 			return false;
// 	}
// 	return true;
// }
// 
// SPtr<AttributeValue> AttributeValueList::Get(int index) const
// {
// 	if (index >= 0 && index < list_.size())
// 		return list_[index];
// 	return NULL;
// }

// 
// AttributeValueDictionary::AttributeValueDictionary()
// {
// 
// }
// 
// AttributeValueDictionary::~AttributeValueDictionary()
// {
// 	Clear();
// }
// 
// void AttributeValueDictionary::Clear()
// {
// 	for (auto pair : dictionary_)
// 	{
// 		delete pair.second;
// 	}
// 	dictionary_.clear();
// }
// 
// bool AttributeValueDictionary::HasKey(const std::string& key) const
// {
// 	return dictionary_.find(key) != dictionary_.end();
// }
// 
// void AttributeValueDictionary::Set(const std::string& path, own AttributeValue* in_value)
// {
// 	assert(in_value);
// 
// 	std::string current_path(path);
// 	AttributeValueDictionary* current_dictionary = this;
// 	for (size_t delimiter_position = current_path.find('.');
// 		delimiter_position != std::string::npos;
// 		delimiter_position = current_path.find('.')) {
// 		// Assume that we're indexing into a dictionary.
// 		std::string key(current_path, 0, delimiter_position);
// 
// 		AttributeValue* val = NULL;
// 		if (!current_dictionary->GetInteranl(key, &val))
// 		{
// 			val = new AttributeValue;
// 			current_dictionary->SetInternal(key, val);
// 		}		
// 		if (!val->IsDictionaryValue())
// 		{
// 			val->SetDictionaryValue();
// 		}		
// 		current_dictionary = val->GetDictonaryValue();
// 		
// 		current_path.erase(0, delimiter_position + 1);
// 	}
// 
// 	current_dictionary->SetInternal(current_path, in_value);
// }
// 
// void AttributeValueDictionary::SetBoolean(const std::string& path, bool in_value)
// {
// 	Set(path, new AttributeValue(in_value));
// }
// 
// void AttributeValueDictionary::SetInteger(const std::string& path, int in_value)
// {
// 	Set(path, new AttributeValue(in_value));
// }
// 
// void AttributeValueDictionary::SetDouble(const std::string& path, double in_value)
// {
// 	Set(path, new AttributeValue(in_value));
// }
// 
// void AttributeValueDictionary::SetString(const std::string& path, const std::string& in_value)
// {
// 	Set(path, new AttributeValue(in_value));
// }
// 
// void AttributeValueDictionary::SetString(const std::string& path, const std::wstring& in_value)
// {
// 	Set(path, new AttributeValue(in_value));
// }
// 
// bool AttributeValueDictionary::Get(const std::string& path, const AttributeValue** out_value) const
// {
// 	std::string current_path(path);
// 	const AttributeValueDictionary* current_dictionary = this;
// 	for (size_t delimiter_position = current_path.find('.');
// 		delimiter_position != std::string::npos;
// 		delimiter_position = current_path.find('.')) {
// 		const AttributeValueDictionary* child_dictionary = NULL;
// 		if (!current_dictionary->GetDictionary(
// 			current_path.substr(0, delimiter_position), &child_dictionary))
// 			return false;
// 
// 		current_dictionary = child_dictionary;
// 		current_path.erase(0, delimiter_position + 1);
// 	}
// 
// 	return current_dictionary->GetInteranl(current_path, out_value);
// }
// 
// bool AttributeValueDictionary::Get(const std::string& path, AttributeValue** out_value)
// {
// 	return static_cast<const AttributeValueDictionary&>(*this).Get(
// 		path,
// 		const_cast<const AttributeValue**>(out_value));
// }
// 
// bool AttributeValueDictionary::GetBoolean(const std::string& path, bool* out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsBoolValue())
// 		return false;
// 	*out_value = value->GetBoolValue();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetInteger(const std::string& path, int* out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsInt32Value())
// 		return false;
// 	*out_value = value->GetInt32Value();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetDouble(const std::string& path, double* out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsDoubleValue())
// 		return false;
// 	*out_value = value->GetDoubleValue();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetString(const std::string& path, std::string* out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsStringValue())
// 		return false;
// 	*out_value = value->GetUTF8Value();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetString(const std::string& path, std::wstring* out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsStringValue())
// 		return false;
// 	*out_value = value->GetUTF16Value();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetDictionary(const std::string& path, AttributeValueDictionary** out_value)
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsDictionaryValue())
// 		return false;
// 	*out_value = value->GetDictonaryValue();
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetDictionary(const std::string& path, const AttributeValueDictionary** out_value) const
// {
// 	assert(out_value);
// 	const AttributeValue* value;
// 	if (!Get(path, &value))
// 		return false;
// 
// 	if (!value->IsDictionaryValue())
// 		return false;
// 	*out_value = value->GetDictonaryValue();
// 	return true;
// }
// 
// bool AttributeValueDictionary::Remove(const std::string& path, own AttributeValue** out_value)
// {
// 	std::string current_path(path);
// 	AttributeValueDictionary* current_dictionary = this;
// 	size_t delimiter_position = current_path.rfind('.');
// 	if (delimiter_position != std::string::npos) {
// 		if (!GetDictionary(current_path.substr(0, delimiter_position),
// 			&current_dictionary))
// 			return false;
// 		current_path.erase(0, delimiter_position + 1);
// 	}
// 
// 	return current_dictionary->RemoveInternal(current_path,
// 		out_value);
// }
// 
// bool AttributeValueDictionary::IsEqual(const AttributeValueDictionary* other) const
// {
// 	if (other->size() != size())
// 		return false;
// 
// 	auto lhs_it = dictionary_.begin();
// 	auto rhs_it = other->dictionary_.begin();
// 	while (rhs_it != other->dictionary_.end() && lhs_it != dictionary_.end()) {
// 		if (lhs_it->first != rhs_it->first ||
// 			lhs_it->second->IsEqual(rhs_it->second)) {
// 			return false;
// 		}
// 		lhs_it++;
// 		rhs_it++;
// 	}	
// 	return true;
// }
// 
// void AttributeValueDictionary::SetInternal(const std::string& path, own AttributeValue* in_value)
// {
// 	auto iter = dictionary_.find(path);
// 	if (iter != dictionary_.end()) {
// 		delete iter->second;
// 	}
// 	iter->second = in_value;
// }
// 
// bool AttributeValueDictionary::GetInteranl(const std::string& path, const AttributeValue** out_value) const
// {
// 	auto iter = dictionary_.find(path);
// 	if (iter == dictionary_.end())
// 		return false;
// 	*out_value = iter->second;
// 	return true;
// }
// 
// bool AttributeValueDictionary::GetInteranl(const std::string& path, AttributeValue** out_value)
// {
// 	return static_cast<const AttributeValueDictionary&>(*this).GetInteranl(
// 		path,
// 		const_cast<const AttributeValue**>(out_value));
// }
// 
// bool AttributeValueDictionary::RemoveInternal(const std::string& key, own AttributeValue** out_value)
// {
// 	auto entry_iterator = dictionary_.find(key);
// 	if (entry_iterator == dictionary_.end())
// 		return false;
// 
// 	AttributeValue* entry = entry_iterator->second;
// 	if (out_value)
// 		*out_value = entry;
// 	else
// 		delete entry;
// 	dictionary_.erase(entry_iterator);
// 	return true;
// }
