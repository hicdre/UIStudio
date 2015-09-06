#pragma once
#include "Model/UIVisualObject.h"
#include "Model/AttributeUnitCollection.h"
#include "Model/AttributeConst.h"
#include "Render/RenderTextLayout.h"


class UITextBase : public UIVisualObject
{
public:
	UITextBase();
	~UITextBase();

	virtual std::wstring GetText();
	virtual void SetText(const std::wstring& str);
	
	virtual AttributeTextAnchor GetTextAnchor();
	virtual void SetTextAnchor(AttributeTextAnchor v);

	//not impl
	virtual SPtr<AttributeFloatCollection> GetX();
	virtual void SetX(const SPtr<AttributeFloatCollection>& v);

	//not impl
	virtual SPtr<AttributeFloatCollection> GetDX();
	virtual void SetDX(const SPtr<AttributeFloatCollection>& v);

	//not impl
	virtual SPtr<AttributeFloatCollection> GetY();
	virtual void SetY(const SPtr<AttributeFloatCollection>& v);

	//not impl
	virtual SPtr<AttributeFloatCollection> GetDY();
	virtual void SetDY(const SPtr<AttributeFloatCollection>& v);

	//not impl
	virtual float GetTextLength();
	virtual void SetTextLength(float v);

	//not impl
	virtual AttributeTextLengthAdjust GetTextLengthAdjust();
	virtual void SetAttributeTextLengthAdjust(AttributeTextLengthAdjust v);

	//not impl
	virtual float GetLetterSpacing();
	virtual void SetLetterSpacing(float v);

	//not impl
	virtual float GetWordSpacing();
	virtual void SetWordSpacing(float v);

	//not impl
	virtual SPtr<AttributePaint> GetFill() override;
	virtual void SetFill(const SPtr<AttributePaint>& v) override;

	virtual base::Rect GetBounds() override;

	//return null
	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) override;

	virtual base::SizeF GetTextLayoutSize() = 0;
protected:
	SPtr<RenderTextLayout> GetTextLayout(const SPtr<RenderContext>& context);
	virtual bool RenderStroke(const SPtr<RenderContext>& context) override;

	bool IsTextLayoutDirty() const { return isTextLayoutDirty_; }
	void SetTextLayoutDirty(bool dirty);
	void AdjustTextLayout();

	SPtr<AttributeFloatCollection> x_;
	SPtr<AttributeFloatCollection> y_;
	SPtr<AttributeFloatCollection> dx_;
	SPtr<AttributeFloatCollection> dy_;

	std::wstring contents_;

	SPtr<RenderTextLayout> text_layout_;
	bool isTextLayoutDirty_;
	
};