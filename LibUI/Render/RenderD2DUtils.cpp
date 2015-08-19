#include "stdafx.h"
#include "RenderD2DUtils.h"
#include "RenderContextD2D.h"

D2D1::Matrix3x2F D2DMatrix(const base::Matrix& m)
{
	return D2D1::Matrix3x2F(m.a, m.b, m.c, m.d, m.tx, m.ty);
}

D2D1_RECT_F D2DRect(const base::Rect& rc)
{
	return D2D1::RectF(rc.x(), rc.y(), rc.right(), rc.bottom());
}


D2D1_ROUNDED_RECT D2DRoundRect(const base::Rect& rc, float rx, float ry)
{
	return D2D1::RoundedRect(D2DRect(rc), rx, ry);
}

D2D1::ColorF D2DColor(base::Color color)
{
	return D2D1::ColorF(color, ColorGetA(color) / 255.f);
}

D2D1_POINT_2F D2DPoint(const base::PointF& p)
{
	return D2D1::Point2F(p.x(), p.y());
}

D2D1_QUADRATIC_BEZIER_SEGMENT D2DQuadBezier(const base::PointF& p0, const base::PointF& p1)
{
	return D2D1::QuadraticBezierSegment(D2DPoint(p0), D2DPoint(p1));
}

CComPtr<ID2D1HwndRenderTarget> D2DGetTargetFromContext(const SPtr<RenderContext>& context)
{
	SPtr<RenderContextD2D> contextD2D = context;
	if (contextD2D)
		return contextD2D->GetD2DTarget();
	return NULL;
}
