#include "stdafx.h"
#include "UILine.h"
#include "Render/RenderEngine.h"

UILine::UILine()
	: x1_(AttributeLength::Pixel(0))
	, y1_(AttributeLength::Pixel(0))
	, x2_(AttributeLength::Pixel(0))
	, y2_(AttributeLength::Pixel(0))
{

}

UILine::~UILine()
{

}

SPtr<AttributeLength> UILine::GetX1() const
{
	return x1_;
}

void UILine::SetX1(const SPtr<AttributeLength>& v)
{
	if (x1_->IsEqual(v.get()))
		return;
	x1_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("x1", x1_));
}

SPtr<AttributeLength> UILine::GetY1() const
{
	return y1_;
}

void UILine::SetY1(const SPtr<AttributeLength>& v)
{
	if (y1_->IsEqual(v.get()))
		return;
	y1_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("y1", y1_));
}

SPtr<AttributeLength> UILine::GetX2() const
{
	return x2_;
}

void UILine::SetX2(const SPtr<AttributeLength>& v)
{
	if (x2_->IsEqual(v.get()))
		return;
	x2_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("x2", x2_));
}

SPtr<AttributeLength> UILine::GetY2() const
{
	return y2_;
}

void UILine::SetY2(const SPtr<AttributeLength>& v)
{
	if (y2_->IsEqual(v.get()))
		return;
	y2_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("y2", y2_));
}

SPtr<AttributePaint> UILine::GetFill()
{
	return NULL;
}

void UILine::SetFill(const SPtr<AttributePaint>& v)
{
	//do nothing
}

SPtr<RenderPath> UILine::GetPath(const SPtr<RenderContext>& context)
{
	if ((!renderPath_ || IsPathDirty()) && GetStrokeWidth() > 0)
	{
		base::PointF p1, p2;
		CalcLinePoint(p1, p2);

		SPtr<RenderPathBuilder> builder = RenderEngine::NewRenderPathBuilder(context);
		if (context)
		{
			builder->AddLine(p1, p2);
			SetPathDirty(false);
		}
		else
		{
			float radius = GetStrokeWidth() / 2.0f;
			builder->AddEllipse(base::Rect(p1.x() - radius, p1.y() - radius, radius*2, radius*2));
			builder->AddEllipse(base::Rect(p2.x() - radius, p2.y() - radius, radius * 2, radius * 2));
		}
		renderPath_ = builder->GetPath();
	}
	return renderPath_;
}

base::Rect UILine::GetBounds()
{
	return GetPath(NULL)->GetBounds();
}

void UILine::CalcLinePoint(base::PointF& p1, base::PointF& p2)
{	
	SPtr<UIVisualObject> obj = GetVisualParent();
	base::Rect bounds(obj->GetLocalBounds());
	p1.set_x(AttributeLength::CalcFromBounds(x1_, bounds.width()));
	p1.set_y(AttributeLength::CalcFromBounds(y1_, bounds.height()));
	p2.set_x(AttributeLength::CalcFromBounds(x2_, bounds.width()));
	p2.set_y(AttributeLength::CalcFromBounds(y2_, bounds.height()));
}
