#pragma once
#include "Property/PropertyValue.h"
#include "Delegate/Delegate.h"
#include "Property/PropertySize.h"

#include <unordered_map>

class PropertyObject;
typedef Event<void(const SPtr<PropertyObject>&, const std::string&)> PropertyChangedEvent;

class PropertyObject : public Object
{
public:
	PropertyObject();
	~PropertyObject();	

	const PropertyValue* GetProperty(const std::string& propertyName) const;
	void SetProperty(const std::string& propertyName, own PropertyValue* value);
	
	PropertyChangedEvent EventPropertyChanged;

protected:
	friend class UIPrototype;
	void OnPropertyChanged(const std::string& name);
	PropertyDictionary property_dict_;

};


/*

Window* w = new Window;
w->SetPropertyTitle(L"abc");
w->SetPropertySize(500,300);
{
	VBox* box = new VBox;
	box->SetPadding(5);
	{
		Lable* label = new Label;
		label->SetPropertyText(L"label");
		box->AddChild(label);
	}
	{
		Image* image = new Image;
		image->SetPropertyUri(L"res:\\a.png");
		box->AddChild(image);
	}

}
w->SetLayout(box);
w->ShowWindow(true);

*/

/*
PropertyTree       LayoutTree   RenderTree



ShowWindow

WindowObject get LayoutObject (VBox)
LayoutManager add LayoutObject
LayoutObject listen WindowObject property Size changed -->  LayoutObject::Layout  child setBounds


WindowObject create RenderObjectList
{
   GetSelfRenderObject (背景，边框等等)
   LayoutObject::GetRenderObjectList
}
				   RenderObjectList[

Window			-> RenderObjectList [RenderImage(Background), RenderRect(Border), RenderText(title)]
 VBox			-> 
	Label		-> RenderObjectList[RenderFilledRect(Background), RenderText(text)]
	Image		-> RenderObjectList[RenderImage(content)]

				]
*/