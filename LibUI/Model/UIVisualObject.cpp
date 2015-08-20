#include "stdafx.h"
#include "UIVisualObject.h"
#include "Render/RenderEngine.h"

UIVisualObject::UIVisualObject()
{
	SetPathDirty(true);
}

UIVisualObject::~UIVisualObject()
{

}


base::Rect UIVisualObject::GetLocalBounds()
{
	base::Rect rc(GetBounds());
	return base::Rect(0, 0, rc.width(), rc.height());
}

void UIVisualObject::Render(const SPtr<RenderContext>& context)
{
	if (!IsVisible())
		return;

	
	PushTranslate(context);
	SetClip(context);

	if (!IsContainer())
	{
		RenderFill(context);
		RenderStroke(context);
	}
	else
	{
		RenderChildren(context);
	}

	ResetClip(context);
	PopTranslate(context);
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
	SPtr<AttributePaint> stroke = GetStroke();
	if (stroke && stroke != AttributeColorPaint::NotSet())
	{
		float strokeWidth = GetStrokeWidth();
		float opicaty = FixOpacityValue(GetStrokeOpacity() * GetOpacity());
		SPtr<RenderBrush> brush = stroke->GetBrush(GetSelf<UIObject>(), context, opicaty, true);
		if (brush)
		{
			SPtr<RenderPath> path = GetPath(context);
			base::Rect bounds = path->GetBounds();
			if (!bounds.IsEmpty())
			{
				SPtr<RenderPen> pen = RenderEngine::NewRenderPen(brush, strokeWidth);
				if (pen)
				{
					pen->SetLineJoin(GetStrokeLineJoin());
					pen->SetLineCap(GetStrokeLineCap());
					pen->SetLineMiterLimit(GetStrokeMiterLimit());
					
					context->DrawPath(pen, path);
				}
			}			
		}

	}
	return true;
}

void UIVisualObject::SetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

void UIVisualObject::ResetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

bool UIVisualObject::IsContainer()
{
	return false;
}



