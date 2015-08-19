#pragma once
#include "Delegate/Delegate.h"
#include "Model/AttributeCollection.h"
#include "Layout/LayoutObject.h"
#include "Render/RenderContext.h"

class RenderObject;
class LayoutObject;
class LayoutContainer;
class UIObjectCollection;
class UIVisualObject;
class UIObject : public Object
{
public:
	UIObject();
	~UIObject();

	SPtr<UIObjectCollection> GetChildren();
	bool HasChildren();

	SPtr<UIObject> GetParent();

	SPtr<AttributeCollection> GetAttributes();		

	Event<void(const SPtr<UIObject>&, const SPtr<AttributeEventArgs>&)> EventAttributechanged;

	virtual void Render(const SPtr<RenderContext>& context);
public:
	bool IsPathDirty() const { return isPathDirty_; }
	void SetPathDirty(bool dirty);

	virtual SPtr<AttributeLength> GetTranslateX();
	virtual void SetTranslateX(const SPtr<AttributeLength>& v);

	virtual SPtr<AttributeLength> GetTranslateY();
	virtual void SetTranslateY(const SPtr<AttributeLength>& v);

// 	virtual SPtr<AttributePaint> GetColor();
// 	virtual void SetColor(const SPtr<AttributePaint>& p);

	virtual SPtr<AttributePaint> GetColor();
	virtual void SetColor(const SPtr<AttributePaint>& p);

	virtual SPtr<AttributePaint> GetFill();
	virtual void SetFill(const SPtr<AttributePaint>& v);

	virtual SPtr<AttributePaint> GetStroke();
	virtual void SetStroke(const SPtr<AttributePaint>& v);

	virtual float GetFillOpacity();
	virtual void SetFillOpacity(float v);

	virtual float GetStrokeWidth();
	virtual void SetStrokeWidth(float v);

	virtual float GetStrokeOpacity();
	virtual void SetStrokeOpacity(float v);

	virtual SPtr<AttributePaint> GetStopColor();
	virtual void SetStopColor(const SPtr<AttributePaint>& v);

	virtual float GetOpacity();
	virtual void SetOpacity(float v);

	virtual std::wstring GetFontFamily();
	virtual void SetFontFamily(const std::wstring& v);

	virtual uint32 GetFontSize();
	virtual void SetFontSize(uint32 v);
// 	SPtr<AttributeLength> GetX();
// 	SPtr<AttributeLength> GetY();
// 	SPtr<AttributeLength> GetWidth();
// 	SPtr<AttributeLength> GetHeight();
// 
// 	void SetX(const SPtr<AttributeLength>& v);
// 	void SetY(const SPtr<AttributeLength>& v);
// 	void SetWidth(const SPtr<AttributeLength>& v);
// 	void SetHeight(const SPtr<AttributeLength>& v);
// 
// 	//visible
// 	bool IsVisible();
// 	void SetVisible(bool visible);
// 
// 	//layout
// 	void SetLayoutContainerType(LayoutContainerType type);
// 	LayoutContainerType GetLayoutContainerType();
public:
// 	void SetRenderObjectNeedsUpdate(bool v);
// 	bool IsRenderObjectNeedsUpdate() const;
// 
// 	virtual void OnParentLayoutContainerTypeChanged(LayoutContainerType type);
// 
// 	virtual SPtr<LayoutObject> GetLayoutObject() = 0;	
// 	virtual SPtr<LayoutContainer> GetLayoutContainer() = 0;
// 
// 	virtual SPtr<RenderObject> GetRenderObject() = 0;
// 
// 	void OnChildRemoved(const SPtr<UIObject>& obj);
// 
// 	virtual void OnLayoutObjectSizeChanged();
protected:
	friend class UIObjectCollection;
	virtual void RenderChildren(const SPtr<RenderContext>& context);
	virtual bool PushTranslate(const SPtr<RenderContext>& context);
	virtual void PopTranslate(const SPtr<RenderContext>& context);

	SPtr<UIVisualObject> GetVisualParent();
	base::PointF CalcTranslateTransform();

	void OnAttributesAttributeChanged(const SPtr<UIObject>& owner, const SPtr<AttributeEventArgs>& args);
	void OnAttributeChanged(const SPtr<AttributeEventArgs>& args);

	virtual void OnChildAdded(const SPtr<UIObject>& obj, uint32 index);
	virtual void OnChildRemoved(const SPtr<UIObject>& obj);

	static float FixOpacityValue(float v);
	
	SPtr<UIObjectCollection> children_;
	SPtr<AttributeCollection> attributes_;
	WPtr<UIObject> parent_;


 	bool isPathDirty_;
private:
	base::Matrix m_;
// 	bool isLayoutObjectNeedsUpdate_;
// 	bool isLayoutContainerChanged_;
	//SPtr<PropertyObject> attributes_;
};