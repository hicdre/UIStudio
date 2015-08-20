#pragma once
#include <d2d1.h>
#include <atlbase.h>
#include "Base/Geom/matrix.h"
#include "Base/Geom/rect.h"
#include "Base/object.h"
#include "Base/color.h"
#include "Model/AttributeConst.h"

#pragma comment(lib, "D2d1.lib")

class RenderContext;

D2D1::Matrix3x2F D2DMatrix(const base::Matrix& m);
D2D1_RECT_F D2DRect(const base::Rect& rc);
D2D1_ROUNDED_RECT D2DRoundRect(const base::Rect& rc, float rx, float ry);
D2D1::ColorF D2DColor(base::Color color);
D2D1_POINT_2F D2DPoint(const base::PointF& p);
D2D1_QUADRATIC_BEZIER_SEGMENT D2DQuadBezier(const base::PointF& p0, const base::PointF& p1);

D2D1_CAP_STYLE D2DLineCap(AttributeStrokeLineCap v);
D2D1_LINE_JOIN D2DLineJoin(AttributeStrokeLineJoin v);

CComPtr<ID2D1HwndRenderTarget> D2DGetTargetFromContext(const SPtr<RenderContext>& context);