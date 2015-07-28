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


