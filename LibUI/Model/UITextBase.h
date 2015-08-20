#pragma once
#include "Model/UIVisualObject.h"
#include "Model/AttributeUnitCollection.h"
#include "Model/AttributeConst.h"


class UITextBase : public UIVisualObject
{
public:
	UITextBase();
	~UITextBase();

	virtual std::wstring GetText();
	virtual void SetText(const std::wstring& str);

	virtual AttributeTextAnchor GetTextAnchor();
	virtual void SetTextAnchor(AttributeTextAnchor v);

	virtual SPtr<AttributeFloatCollection> GetX();
	virtual void SetX(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetDX();
	virtual void SetDX(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetY();
	virtual void SetY(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetDY();
	virtual void SetDY(const SPtr<AttributeFloatCollection>& v);

	virtual float GetTextLength();
	virtual void SetTextLength(float v);

	virtual AttributeTextLengthAdjust GetTextLengthAdjust();
	virtual void SetAttributeTextLengthAdjust(AttributeTextLengthAdjust v);

	virtual float GetLetterSpacing();
	virtual void SetLetterSpacing(float v);

	virtual float GetWordSpacing();
	virtual void SetWordSpacing(float v);

	virtual SPtr<AttributePaint> GetFill() override;
	virtual void SetFill(const SPtr<AttributePaint>& v) override;
protected:
	SPtr<AttributeFloatCollection> x_;
	SPtr<AttributeFloatCollection> y_;
	SPtr<AttributeFloatCollection> dx_;
	SPtr<AttributeFloatCollection> dy_;

	std::wstring contents_;
};