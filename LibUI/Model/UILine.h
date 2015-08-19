#pragma once
#include "Model/UIVisualObject.h"
#include "Base/Geom/point.h"

class UILine : public UIVisualObject
{
public:
	UILine();
	~UILine();

	SPtr<AttributeLength> GetX1() const;
	void SetX1(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetY1() const;
	void SetY1(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetX2() const;
	void SetX2(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetY2() const;
	void SetY2(const SPtr<AttributeLength>& v);

	virtual SPtr<AttributePaint> GetFill() override;
	virtual void SetFill(const SPtr<AttributePaint>& v) override;

	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) override;

	virtual base::Rect GetBounds() override;
protected:
	void CalcLinePoint(base::PointF& p1, base::PointF& p2);
	SPtr<AttributeLength> x1_;
	SPtr<AttributeLength> y1_;
	SPtr<AttributeLength> x2_;
	SPtr<AttributeLength> y2_;
	SPtr<RenderPath> renderPath_;
};