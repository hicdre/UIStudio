#pragma once
#include "Model/UITextBase.h"

class UIBasicText : public UITextBase
{
public:
	UIBasicText();
	~UIBasicText();

	virtual base::SizeF GetTextLayoutSize() override;
};