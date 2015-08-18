#include "stdafx.h"
#include "UIVisualObject.h"

UIVisualObject::UIVisualObject()
{
	SetPathDirty(true);
}

UIVisualObject::~UIVisualObject()
{

}


void UIVisualObject::Render(const SPtr<RenderContext>& context)
{
	if (!IsVisible())
		return;
	//push transform
	SetClip(context);
	RenderFill(context);
	RenderStroke(context);

	ResetClip(context);
	//pop transform
}

bool UIVisualObject::IsVisible()
{
	return !GetAttributes()->HasAttribute("visible")
		? true
		: GetAttributes()->GetAttributeBool("visible");
}

void UIVisualObject::SetVisible(bool v)
{
	GetAttributes()->SetAttributeBool("visible", v);
}

void UIVisualObject::RenderFill(const SPtr<RenderContext>& context)
{
	SPtr<AttributePaint> paint = GetFill();
	if (paint)
	{
		float opicaty = FixOpacityValue(GetFillOpacity() * GetOpacity());
		SPtr<RenderBrush> brush = paint->GetBrush(GetSelf<UIObject>(), context, opicaty);
		if (brush)
		{
			context->FillPath(brush, GetPath(context));
		}
	}
}

bool UIVisualObject::RenderStroke(const SPtr<RenderContext>& context)
{

}

void UIVisualObject::SetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

void UIVisualObject::ResetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

