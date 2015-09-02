#pragma once
#include "Model/UIVisualObject.h"
#include "Model/AttributeUnitCollection.h"
#include "Model/AttributeConst.h"



class UITextBase : public UIVisualObject
{
public:
	UITextBase();
	~UITextBase();

	virtual std::wstring GetText();
	virtual void SetText(const std::wstring& str);

	virtual AttributeTextAnchor GetTextAnchor();
	virtual void SetTextAnchor(AttributeTextAnchor v);

	virtual SPtr<AttributeFloatCollection> GetX();
	virtual void SetX(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetDX();
	virtual void SetDX(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetY();
	virtual void SetY(const SPtr<AttributeFloatCollection>& v);

	virtual SPtr<AttributeFloatCollection> GetDY();
	virtual void SetDY(const SPtr<AttributeFloatCollection>& v);

	virtual float GetTextLength();
	virtual void SetTextLength(float v);

	virtual AttributeTextLengthAdjust GetTextLengthAdjust();
	virtual void SetAttributeTextLengthAdjust(AttributeTextLengthAdjust v);

	virtual float GetLetterSpacing();
	virtual void SetLetterSpacing(float v);

	virtual float GetWordSpacing();
	virtual void SetWordSpacing(float v);

	virtual SPtr<AttributePaint> GetFill() override;
	virtual void SetFill(const SPtr<AttributePaint>& v) override;

	virtual base::Rect GetBounds() override;

	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) override;
protected:
	class TextDrawingState
	{
	public:
		TextDrawingState() {}
		TextDrawingState(const SPtr<RenderContext>& context, const SPtr<UITextBase>& elem) 
			: Element(elem), Renderer(context), _xAnchor(0)
		{
			_authorPathLength = 0;
		}

		TextDrawingState* Clone()
		{
			TextDrawingState* result = new TextDrawingState;
			result->_xAnchor = _xAnchor;
			result->Current = Current;
			result->Element = Element;
			result->NumChars = NumChars;
			result->Parent = Parent;
			result->Renderer = Renderer;
			return result;
		}

		void DrawString(const std::wstring& value)
		{
			std::vector<float> xAnchors, yAnchors;
			GetValues(value.size(), Element->GetX(), xAnchors);
			GetValues(value.size(), Element->GetY(), yAnchors);

			SPtr<RenderFont> font = Element->GetFont(Renderer);
			if (!font) {
				assert(0);
				return;
			}			
			float fontBaselineHeight = font->GetAscent(Renderer);
			std::vector<float> xOffsets, yOffsets;
			float baselineShift = 0.0f;
			GetValues(value.size(), Element->GetDX(), xOffsets);
			GetValues(value.size(), Element->GetDY(), yOffsets);

			if (StartOffserAdjust != 0)
			{
				if (xOffsets.size() < 1)
				{
					xOffsets.push_back(StartOffserAdjust);
				}
				else
				{
					xOffsets[0] += StartOffserAdjust;
				}
			}

			float spacing = Element->GetLetterSpacing();
			float wordSpacing = Element->GetWordSpacing();
			if (spacing != 0 || wordSpacing != 0 || LetterSpacingAdjust != 0)
			{
				if (Parent && NumChars == 0 && xOffsets.size() == 0)
					xOffsets.push_back(0);
				for (int i = ((!Parent && NumChars == 0) ? 1 : 0); i < value.size(); i++)
				{
					float calcWordSpacing = isspace(value[i]) ? wordSpacing : 0;
					if (i >= xOffsets.size())
					{
						xOffsets.push_back(spacing + calcWordSpacing);
					}
					else
					{
						xOffsets[i] += spacing + calcWordSpacing;
					}
				}
			}

			//baselineShift‘›≤ª µœ÷
			float yPos = Current.y();
			for (int i = 0; i < xAnchors.size() - 1; i++)
			{
				FlushPath();
				_xAnchor = xAnchors[i] + (xOffsets.size() > i ? xOffsets[i] : 0);
				EnsurePath();
				yPos = (yAnchors.size() > i ? yAnchors[i] : yPos) + (yOffsets.size() > i ? yOffsets[i] : 0);
				DrawStringOnCurrPath(value[i], font, base::PointF(_xAnchor, yPos), fontBaselineHeight);
			}
		}

		
		SPtr<RenderPath> BaselinePath;//null
		base::PointF Current;
		SPtr<UITextBase> Element;
		float LetterSpacingAdjust;
		int NumChars;
		TextDrawingState* Parent;
		SPtr<RenderContext> Renderer;
		float StartOffserAdjust;		

	private:
		void EnsurePath()
		{
			if (!_currPath)
			{

			}
		}
		void GetValues(int maxCount, const SPtr<AttributeFloatCollection>& collection, std::vector<float>& results)
		{
			TextDrawingState* currState = this;
			int charCount = 0;
			results.clear();
			int resultCount = 0;
			while (currState)
			{
				charCount += currState->NumChars;
				int collectionSize = collection->GetCount();
				for (int i = charCount; i < maxCount + charCount && i < collectionSize; i++)
				{
					results.push_back(collection->at(i));
				}

				if (results.size() > resultCount)
				{
					maxCount -= results.size() - resultCount;
					charCount += results.size() - resultCount;
					resultCount = results.size();
				}

				if (maxCount < 1)
					return;
				currState = currState->Parent;
			}
		}
		float _xAnchor;
		float _authorPathLength;//0

		SPtr<RenderPathBuilder> _currPath;
	};

	void SetPath(TextDrawingState* state);
	void SetPath(TextDrawingState* state, bool doMeasurements);

	SPtr<AttributeFloatCollection> x_;
	SPtr<AttributeFloatCollection> y_;
	SPtr<AttributeFloatCollection> dx_;
	SPtr<AttributeFloatCollection> dy_;

	std::wstring contents_;
	SPtr<RenderPath> renderPath_;
};