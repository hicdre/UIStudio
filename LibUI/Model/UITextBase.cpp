#include "stdafx.h"
#include "UITextBase.h"

UITextBase::UITextBase()
	: x_(new AttributeFloatCollection)
	, y_(new AttributeFloatCollection)
	, dx_(new AttributeFloatCollection)
	, dy_(new AttributeFloatCollection)
{

}

UITextBase::~UITextBase()
{

}

std::wstring UITextBase::GetText()
{
	return contents_;
}

void UITextBase::SetText(const std::wstring& str)
{
	if (contents_ == str)
		return;
	contents_ = str;
	SetPathDirty(true);
	//OnAttributeChanged(new AttributeEventArgs("content", new AttributeValue(contents_)));
}

AttributeTextAnchor UITextBase::GetTextAnchor()
{
	return !GetAttributes()->HasAttribute("text-anchor")
		? TextAnchorStart
		: (AttributeTextAnchor)GetAttributes()->GetAttributeInt("text-anchor");
}

void UITextBase::SetTextAnchor(AttributeTextAnchor v)
{
	GetAttributes()->SetAttributeIntIfDifferent("text-anchor", (int)v, [this](){
		SetPathDirty(true);
	});	
}

SPtr<AttributeFloatCollection> UITextBase::GetX()
{
	return x_;
}

void UITextBase::SetX(const SPtr<AttributeFloatCollection>& v)
{
	assert(v);
	if (x_->IsEqual(v.get()))
		return;
	x_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("x", x_));
}

SPtr<AttributeFloatCollection> UITextBase::GetDX()
{
	return dx_;
}

void UITextBase::SetDX(const SPtr<AttributeFloatCollection>& v)
{
	assert(v);
	if (dx_->IsEqual(v.get()))
		return;
	dx_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("dx", dx_));
}

SPtr<AttributeFloatCollection> UITextBase::GetY()
{
	return y_;
}

void UITextBase::SetY(const SPtr<AttributeFloatCollection>& v)
{
	assert(v);
	if (y_->IsEqual(v.get()))
		return;
	y_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("y", y_));
}

SPtr<AttributeFloatCollection> UITextBase::GetDY()
{
	return dy_;
}

void UITextBase::SetDY(const SPtr<AttributeFloatCollection>& v)
{
	assert(v);
	if (dy_->IsEqual(v.get()))
		return;
	dy_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("dy", dy_));
}

float UITextBase::GetTextLength()
{
	return !GetAttributes()->HasAttribute("textLength")
		? 0.f
		: GetAttributes()->GetAttributeFloat("textLength");
}

void UITextBase::SetTextLength(float v)
{
	GetAttributes()->SetAttributeFloatIfDifferent("textLength", v, [this](){
		SetPathDirty(true);
	});
}

AttributeTextLengthAdjust UITextBase::GetTextLengthAdjust()
{
	return !GetAttributes()->HasAttribute("lengthAdjust")
		? TextLengthAdjustSpacing
		: (AttributeTextLengthAdjust)GetAttributes()->GetAttributeInt("lengthAdjust");
}

void UITextBase::SetAttributeTextLengthAdjust(AttributeTextLengthAdjust v)
{
	GetAttributes()->SetAttributeIntIfDifferent("textLength", (int)v, [this](){
		SetPathDirty(true);
	});
}

float UITextBase::GetLetterSpacing()
{
	return !GetAttributes()->HasAttribute("text-letter-spacing")
		? 0.f
		: GetAttributes()->GetAttributeFloat("text-letter-spacing");
}

void UITextBase::SetLetterSpacing(float v)
{
	GetAttributes()->SetAttributeFloatIfDifferent("text-letter-spacing", v, [this](){
		SetPathDirty(true);
	});
}

float UITextBase::GetWordSpacing()
{
	return !GetAttributes()->HasAttribute("text-word-spacing")
		? 0.f
		: GetAttributes()->GetAttributeFloat("text-word-spacing");
}

void UITextBase::SetWordSpacing(float v)
{
	GetAttributes()->SetAttributeFloatIfDifferent("text-word-spacing", v, [this](){
		SetPathDirty(true);
	});
}

SPtr<AttributePaint> UITextBase::GetFill()
{
	return !GetAttributes()->HasAttribute("fill")
		? AttributePaint::Color(base::Color_Black)
		: GetAttributes()->GetAttributePaint("fill");
}

void UITextBase::SetFill(const SPtr<AttributePaint>& v)
{
	GetAttributes()->SetAttributePaintIfDifferent("fill", v, [this](){
		SetPathDirty(true);
	});
}

base::Rect UITextBase::GetBounds()
{
	return GetPath(NULL)->GetBounds();
}

SPtr<RenderPath> UITextBase::GetPath(const SPtr<RenderContext>& context)
{
	if (!renderPath_ || IsPathDirty())
	{
		SetPath(new TextDrawingState(context, this));
	}
	return renderPath_;
}

void UITextBase::SetPath(TextDrawingState* state)
{
	SetPath(state, true);
}

void UITextBase::SetPath(TextDrawingState* state, bool doMeasurements)
{
	TextDrawingState* origState = NULL;
	bool alignOnBaseline = false;

	if (doMeasurements)
	{
		if (GetTextLength() != 0)
		{
			origState = state->Clone();
		}
	}

	state->DrawString(GetText());
}

