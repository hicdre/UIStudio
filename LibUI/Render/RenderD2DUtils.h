#pragma once
#include <d2d1.h>
#include <atlbase.h>
#include "Base/Geom/matrix.h"
#include "Base/Geom/rect.h"
#include "Base/object.h"
#include "Base/color.h"

#pragma comment(lib, "D2d1.lib")

class RenderContext;

D2D1::Matrix3x2F D2DMatrix(const base::Matrix& m);
D2D1_RECT_F D2DRect(const base::Rect& rc);
D2D1::ColorF D2DColor(base::Color color);

CComPtr<ID2D1HwndRenderTarget> D2DGetTargetFromContext(const SPtr<RenderContext>& context);