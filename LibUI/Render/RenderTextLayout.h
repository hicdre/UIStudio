#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Base/Geom/range.h"
#include "Model/AttributeConst.h"
#include <string>

class RenderTextLayout : public Object
{
public:
	RenderTextLayout();
	~RenderTextLayout();

	virtual void SetFontFamilyName(const std::wstring& name, const base::Range& range) = 0;

	virtual void SetFontSize(float size, const base::Range& range) = 0;

	virtual void SetFontWeight(AttributeFontWeight v, const base::Range& range) = 0;

	virtual void SetTextAnchor(AttributeTextAnchor v) = 0;

	virtual void SetFontStyle(AttributeFontStyle v, const base::Range& range) = 0;
};