#include "stdafx.h"
#include "PropertyValue.h"

#include "Base/utils.h"

PropertyValue::PropertyValue( const std::string& v )
{
	SetStringValue(utils::MultiByteToWide(v));
}


void PropertyValue::SetBoolValue( bool v )
{
	Clear();  boolValue_ = v;  type_ = PropertyTypeBool;
}

void PropertyValue::SetInt32Value( int32_t v )
{
	Clear();  int32Value_ = v;  type_ = PropertyTypeInt32;
}

void PropertyValue::SetUInt32Value( uint32_t v )
{
	Clear();  uint32Value_ = v;  type_ = PropertyTypeUInt32;
}

void PropertyValue::SetInt64Value( int64_t v )
{
	Clear();  int64Value_ = v;  type_ = PropertyTypeInt64;
}

void PropertyValue::SetUInt64Value( uint64_t v )
{
	Clear();  uint64Value_ = v;  type_ = PropertyTypeUInt64;
}

void PropertyValue::SetFloatValue( float v )
{
	Clear();  floatValue_ = v;  type_ = PropertyTypeFloat;
}

void PropertyValue::SetDoubleValue( double v )
{
	Clear();  doubleValue_ = v;  type_ = PropertyTypeDouble;
}

void PropertyValue::SetObjectValue( const SPtr<Object>& v )
{
	Clear();  
	objectValue_ = v.get(); 
	if (objectValue_)
		objectValue_->AddRef();
	type_ = PropertyTypeObject;
}


void PropertyValue::SetStringValue( const std::wstring& s )
{
	Clear();
	utf16Value_ = new std::wstring(s);
	type_ = PropertyTypeString;
}

void PropertyValue::SetStringValue( const std::string& s )
{
	SetStringValue(utils::MultiByteToWide(s));
}

void PropertyValue::SetListValue()
{
	Clear();
	listValue_ = new PropertyList;
	type_ = PropertyTypeList;
}

void PropertyValue::SetListValue(const SPtr<Object>& v)
{
	Clear();
	listValue_ = new PropertyList;
	listValue_->Append(v);
	type_ = PropertyTypeList;

}

void PropertyValue::SetListValue(own PropertyValue* v)
{
	Clear();
	listValue_ = new PropertyList;
	listValue_->Append(v);
	type_ = PropertyTypeList;
}

void PropertyValue::SetDictionaryValue()
{
	Clear();
	dictValue_ = new PropertyDictionary;	
	type_ = PropertyTypeList;
}


std::wstring PropertyValue::ToUTF16() const
{
	switch (type_) {
	case PropertyTypeNull:
		return L"(Null)";
	case PropertyTypeBool:
		return boolValue_ ? L"true" : L"false";
	case PropertyTypeInt32:
		{
			wchar_t buffer[2 * _MAX_INT_DIG];

			std::swprintf(buffer, sizeof (buffer) / sizeof (buffer[0]),
				L"%d", int32Value_);
			return std::wstring(buffer);
		}		
	case PropertyTypeUInt32:
		{
			wchar_t buffer[2 * _MAX_INT_DIG];

			std::swprintf(buffer, sizeof (buffer) / sizeof (buffer[0]),
				L"%u", uint32Value_);
			return std::wstring(buffer);
		}
	case PropertyTypeInt64:
		return std::to_wstring(int64Value_);
	case PropertyTypeUInt64:
		return std::to_wstring(uint64Value_);
	case PropertyTypeFloat:
		return std::to_wstring((long double)floatValue_);
	case PropertyTypeDouble:
		return std::to_wstring((long double)doubleValue_);
	case PropertyTypeObject:
		assert(0);
		return L"(Object)";
	case PropertyTypeString:
		assert(utf16Value_);
		return *utf16Value_;
	default:
		return L"(Unknown)";
	}
}

void PropertyValue::Clear()
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
	else if (IsListValue())
	{
		if (listValue_)
			delete listValue_;
	}
	else if (IsDictionaryValue())
	{
		if (dictValue_)
			delete dictValue_;
	}

	uint64Value_ = 0;
	type_ = PropertyTypeNull;
}

std::string PropertyValue::GetUTF8Value() const
{
	return utils::WideToMultiByte(GetUTF16Value());
}

bool PropertyValue::IsEqual(const PropertyValue* other) const
{
	if (other->type_ != type_)
		return false;
	switch (type_) {
	case PropertyTypeNull:
		return true;
	case PropertyTypeBool:
	case PropertyTypeInt32:
	case PropertyTypeUInt32:
	case PropertyTypeInt64:
	case PropertyTypeUInt64:
	case PropertyTypeFloat:
	case PropertyTypeDouble:
		return uint64Value_ == other->uint64Value_;
	case PropertyTypeObject:
		return objectValue_ == other->objectValue_;
	case PropertyTypeString:
		return *utf16Value_ == *other->utf16Value_;
	case PropertyTypeList:
		return listValue_->IsEqual(other->listValue_);
	case PropertyTypeDictionary:
		return dictValue_->IsEqual(other->dictValue_);
	}
	return true;

}

PropertyList::PropertyList()
{

}

PropertyList::~PropertyList()
{
	Clear();
}


void PropertyList::Clear()
{
	for (auto iter = list_.begin(); iter != list_.end(); iter++)
	{
		delete *iter;
	}
	list_.clear();
}


void PropertyList::Append(own PropertyValue* v)
{
	list_.push_back(v);
}

void PropertyList::Append(const SPtr<Object>& v)
{
	Append(new PropertyValue(v));
}

bool PropertyList::IsEqual(PropertyList* other) const
{
	if (GetSize() != other->GetSize())
		return false;
	size_t count = list_.size();
	for (int i = 0; i < count; i++)
	{
		PropertyValue* a = list_[i];
		PropertyValue* b = other->list_[i];		
		if (!a->IsEqual(b))
			return false;
	}
	return true;
}

PropertyValue* PropertyList::Get(int index) const
{
	if (index >= 0 && index < list_.size())
		return list_[index];
	return NULL;
}


PropertyDictionary::PropertyDictionary()
{

}

PropertyDictionary::~PropertyDictionary()
{
	Clear();
}

void PropertyDictionary::Clear()
{
	for (auto pair : dictionary_)
	{
		delete pair.second;
	}
	dictionary_.clear();
}

bool PropertyDictionary::HasKey(const std::string& key) const
{
	return dictionary_.find(key) != dictionary_.end();
}

void PropertyDictionary::Set(const std::string& path, own PropertyValue* in_value)
{
	assert(in_value);

	std::string current_path(path);
	PropertyDictionary* current_dictionary = this;
	for (size_t delimiter_position = current_path.find('.');
		delimiter_position != std::string::npos;
		delimiter_position = current_path.find('.')) {
		// Assume that we're indexing into a dictionary.
		std::string key(current_path, 0, delimiter_position);

		PropertyValue* val = NULL;
		if (!current_dictionary->GetInteranl(key, &val))
		{
			val = new PropertyValue;
			current_dictionary->SetInternal(key, val);
		}		
		if (!val->IsDictionaryValue())
		{
			val->SetDictionaryValue();
		}		
		current_dictionary = val->GetDictonaryValue();
		
		current_path.erase(0, delimiter_position + 1);
	}

	current_dictionary->SetInternal(current_path, in_value);
}

void PropertyDictionary::SetBoolean(const std::string& path, bool in_value)
{
	Set(path, new PropertyValue(in_value));
}

void PropertyDictionary::SetInteger(const std::string& path, int in_value)
{
	Set(path, new PropertyValue(in_value));
}

void PropertyDictionary::SetDouble(const std::string& path, double in_value)
{
	Set(path, new PropertyValue(in_value));
}

void PropertyDictionary::SetString(const std::string& path, const std::string& in_value)
{
	Set(path, new PropertyValue(in_value));
}

void PropertyDictionary::SetString(const std::string& path, const std::wstring& in_value)
{
	Set(path, new PropertyValue(in_value));
}

bool PropertyDictionary::Get(const std::string& path, const PropertyValue** out_value) const
{
	std::string current_path(path);
	const PropertyDictionary* current_dictionary = this;
	for (size_t delimiter_position = current_path.find('.');
		delimiter_position != std::string::npos;
		delimiter_position = current_path.find('.')) {
		const PropertyDictionary* child_dictionary = NULL;
		if (!current_dictionary->GetDictionary(
			current_path.substr(0, delimiter_position), &child_dictionary))
			return false;

		current_dictionary = child_dictionary;
		current_path.erase(0, delimiter_position + 1);
	}

	return current_dictionary->GetInteranl(current_path, out_value);
}

bool PropertyDictionary::Get(const std::string& path, PropertyValue** out_value)
{
	return static_cast<const PropertyDictionary&>(*this).Get(
		path,
		const_cast<const PropertyValue**>(out_value));
}

bool PropertyDictionary::GetBoolean(const std::string& path, bool* out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsBoolValue())
		return false;
	*out_value = value->GetBoolValue();
	return true;
}

bool PropertyDictionary::GetInteger(const std::string& path, int* out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsInt32Value())
		return false;
	*out_value = value->GetInt32Value();
	return true;
}

bool PropertyDictionary::GetDouble(const std::string& path, double* out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsDoubleValue())
		return false;
	*out_value = value->GetDoubleValue();
	return true;
}

bool PropertyDictionary::GetString(const std::string& path, std::string* out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsStringValue())
		return false;
	*out_value = value->GetUTF8Value();
	return true;
}

bool PropertyDictionary::GetString(const std::string& path, std::wstring* out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsStringValue())
		return false;
	*out_value = value->GetUTF16Value();
	return true;
}

bool PropertyDictionary::GetDictionary(const std::string& path, PropertyDictionary** out_value)
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsDictionaryValue())
		return false;
	*out_value = value->GetDictonaryValue();
	return true;
}

bool PropertyDictionary::GetDictionary(const std::string& path, const PropertyDictionary** out_value) const
{
	assert(out_value);
	const PropertyValue* value;
	if (!Get(path, &value))
		return false;

	if (!value->IsDictionaryValue())
		return false;
	*out_value = value->GetDictonaryValue();
	return true;
}

bool PropertyDictionary::Remove(const std::string& path, own PropertyValue** out_value)
{
	std::string current_path(path);
	PropertyDictionary* current_dictionary = this;
	size_t delimiter_position = current_path.rfind('.');
	if (delimiter_position != std::string::npos) {
		if (!GetDictionary(current_path.substr(0, delimiter_position),
			&current_dictionary))
			return false;
		current_path.erase(0, delimiter_position + 1);
	}

	return current_dictionary->RemoveInternal(current_path,
		out_value);
}

bool PropertyDictionary::IsEqual(const PropertyDictionary* other) const
{
	if (other->size() != size())
		return false;

	auto lhs_it = dictionary_.begin();
	auto rhs_it = other->dictionary_.begin();
	while (rhs_it != other->dictionary_.end() && lhs_it != dictionary_.end()) {
		if (lhs_it->first != rhs_it->first ||
			lhs_it->second->IsEqual(rhs_it->second)) {
			return false;
		}
		lhs_it++;
		rhs_it++;
	}	
	return true;
}

void PropertyDictionary::SetInternal(const std::string& path, own PropertyValue* in_value)
{
	auto iter = dictionary_.find(path);
	if (iter != dictionary_.end()) {
		delete iter->second;
	}
	iter->second = in_value;
}

bool PropertyDictionary::GetInteranl(const std::string& path, const PropertyValue** out_value) const
{
	auto iter = dictionary_.find(path);
	if (iter == dictionary_.end())
		return false;
	*out_value = iter->second;
	return true;
}

bool PropertyDictionary::GetInteranl(const std::string& path, PropertyValue** out_value)
{
	return static_cast<const PropertyDictionary&>(*this).GetInteranl(
		path,
		const_cast<const PropertyValue**>(out_value));
}

bool PropertyDictionary::RemoveInternal(const std::string& key, own PropertyValue** out_value)
{
	auto entry_iterator = dictionary_.find(key);
	if (entry_iterator == dictionary_.end())
		return false;

	PropertyValue* entry = entry_iterator->second;
	if (out_value)
		*out_value = entry;
	else
		delete entry;
	dictionary_.erase(entry_iterator);
	return true;
}
