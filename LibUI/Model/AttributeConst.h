#pragma once


enum AttributeStrokeLineJoin
{
	StrokeLineJoinMilter = 0,
	StrokeLineJoinRound,
	StrokeLineJoinBevel,
};

enum AttributeStrokeLineCap
{
	StrokeLineCapFlat = 0,
	StrokeLineCapRound,
	StrokeLineCapSquare,
};

enum AttributeTextAnchor
{
	TextAnchorStart = 0,
	TextAnchorMiddle,
	TextAnchorEnd,
};

enum AttributeTextLengthAdjust
{
	TextLengthAdjustSpacing = 0,
	TextLengthAdjustSpacingAndGlyphs,
};

enum AttributeTextDecoration
{
	TextDecorationNone = 1,
	TextDecorationUnderline = 2,
	TextDecorationOverline = 4,
	TextDecorationLineThrough = 8,
	TextDecorationBlink = 16
};

enum AttributeFontWeight
{
	FontWeight100 = 1,
	FontWeight200 = 2,
	FontWeight300 = 4,
	FontWeight400 = 8,
	FontWeight500 = 16,
	FontWeight600 = 32,
	FontWeight700 = 64,
	FontWeight800 = 128,
	FontWeight900 = 256,

	FontWeightNormal = FontWeight400,
	FontWeightBold = FontWeight700,
	FontWeightBolder = 512,
	FontWeightLighter = 1024,
};

enum AttributeFontStyle
{
	FontStyleNormal = 1,
	FontStyleOblique = 2,
	FontStyleItalic = 4
};