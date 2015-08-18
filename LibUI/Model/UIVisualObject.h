#pragma once
#include "Model/UIObject.h"
#include "Render/RenderPath.h"
#include "Base/Geom/rect.h"

class UIVisualObject : public UIObject
{
public:
	UIVisualObject();
	~UIVisualObject();

	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) = 0;

	virtual base::Rect GetBounds() = 0;

	base::Rect GetLocalBounds();

	virtual void Render(const SPtr<RenderContext>& context) override;

	virtual bool IsVisible();
	virtual void SetVisible(bool v);
protected:
	virtual void RenderFill(const SPtr<RenderContext>& context);
	virtual bool RenderStroke(const SPtr<RenderContext>& context);
	virtual void SetClip(const SPtr<RenderContext>& context);
	virtual void ResetClip(const SPtr<RenderContext>& context);

	virtual bool IsContainer();

	
};