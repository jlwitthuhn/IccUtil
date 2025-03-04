#pragma once

#include <optional>
#include <string>

enum class IccDataType
{
	chromaticityType,
	curveVariable,
	dateTimeType,
	dictType,
	lutVariable,
	measurementType,
	namedColor2Type,
	profileSequenceDescType,
	responseCurveSet16Type,
	s15Fixed16ArrayType,
	signatureType,
	textType,
	viewingConditionsType,
	xyzType,
	// v2-only below
	crdInfoType,
	dataType,
	deviceSettingsType,
	namedColorType,
	screeningType,
	textDescriptionType,
	ucrbgType,
	// v4-only
	cicpType,
	colorantOrderType,
	colorantTableType,
	multiLocalizedUnicodeType,
	multiProcessElementsType,
	profileSequenceIdentifierType,
};

namespace IccDataTypeFuncs
{
	std::string to_string(IccDataType input);
	std::optional<IccDataType> get_type_by_tag(const std::string& tag, bool v4);
}
