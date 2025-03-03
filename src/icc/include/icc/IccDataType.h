#pragma once

#include <optional>
#include <string>

enum class IccDataType
{
	chromaticityType,
	cicpType,
	colorantOrderType,
	colorantTableType,
	curveVariable,
	dateTimeType,
	dictType,
	lutVariable,
	measurementType,
	multiProcessElementsType,
	multiLocalizedUnicodeType,
	namedColor2Type,
	profileSequenceDescType,
	profileSequenceIdentifierType,
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
};

namespace IccDataTypeFuncs
{
	std::string to_string(IccDataType input);
	std::optional<IccDataType> get_type_by_tag(const std::string& tag, bool v4);
}
