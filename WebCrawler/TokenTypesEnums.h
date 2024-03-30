#pragma once


enum HTMLTokenTypes
{
	HTMLTokenTypeNone,
	HTMLTokenTypePlainText,
	HTMLTokenTypeSingleQuotes,
	HTMLTokenTypeDoubleQuotes,
	HTMLTokenTypeSlash,
	HTMLTokenTypeLeftAngleBracket,
	HTMLTokenTypeRightAngleBracket,
	HTMLTokenTypeEqualsSign,
	HTMLTokenTypeOther,
	HTMLTokenTypeCount
};

enum URLTokenTypes
{
	URLTokenTypeNone,
	URLTokenTypeIntconst,
	URLTokenTypeXalphas,
	URLTokenTypeSemicolon,
	URLTokenTypePeriod,
	URLTokenTypeQuotes,
	URLTokenTypeColon,
	URLTokenTypeSlash,
	URLTokenTypeDoubleSlash,
	URLTokenTypeOther,
	URLTokenTypeCount
};