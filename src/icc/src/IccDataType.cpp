#include "IccDataType.h"

std::string IccDataTypeFuncs::to_string(const IccDataType input)
{
	switch (input)
	{
		case IccDataType::chromaticityType:
			return "Chromaticity";
		case IccDataType::curveVariable:
			return "Curve";
		case IccDataType::dateTimeType:
			return "Date/time";
		case IccDataType::dictType:
			return "Dictionary";
		case IccDataType::lutVariable:
			return "Lookup table";
		case IccDataType::measurementType:
			return "Measurement";
		case IccDataType::namedColor2Type:
			return "Named color 2";
		case IccDataType::profileSequenceDescType:
			return "Profile sequence description";
		case IccDataType::responseCurveSet16Type:
			return "Response curve set16";
		case IccDataType::s15Fixed16ArrayType:
			return "s15fixed16 array";
		case IccDataType::signatureType:
			return "Signature";
		case IccDataType::textType:
			return "Text";
		case IccDataType::viewingConditionsType:
			return "Viewing conditions";
		case IccDataType::xyzType:
			return "XYZ color";
		// V2
		case IccDataType::crdInfoType:
			return "CRD info";
		case IccDataType::dataType:
			return "Data";
		case IccDataType::deviceSettingsType:
			return "Device settings";
		case IccDataType::namedColorType:
			return "Named color";
		case IccDataType::screeningType:
			return "Screening params";
		case IccDataType::textDescriptionType:
			return "Text description";
		case IccDataType::ucrbgType:
			return "UCRBG";
		// V4
		case IccDataType::cicpType:
			return "Coding-independent code points";
		case IccDataType::colorantOrderType:
			return "Colorant order";
		case IccDataType::colorantTableType:
			return "Colorant table";
		case IccDataType::multiLocalizedUnicodeType:
			return "Multi-localized unicode";
		case IccDataType::multiProcessElementsType:
			return "Multi process elements";
		case IccDataType::profileSequenceIdentifierType:
			return "Profile sequence ID";
		default:
			return "Unknown type";
	}
}

std::optional<IccDataType> IccDataTypeFuncs::get_type_by_tag(const std::string& tag, const bool v4)
{
	if (tag == "A2B0")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "A2B1")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "A2B2")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "bXYZ")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "bTRC")
	{
		return IccDataType::curveVariable;
	}
	else if (tag == "B2A0")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "B2A1")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "B2A2")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "calt")
	{
		return IccDataType::dateTimeType;
	}
	else if (tag == "targ")
	{
		return IccDataType::textType;
	}
	else if (tag == "chad")
	{
		return IccDataType::s15Fixed16ArrayType;
	}
	else if (tag == "chrm")
	{
		return IccDataType::chromaticityType;
	}
	else if (tag == "cprt")
	{
		return v4 ? IccDataType::multiLocalizedUnicodeType : IccDataType::textType;
	}
	else if (tag == "dmnd")
	{
		return v4 ? IccDataType::multiLocalizedUnicodeType : IccDataType::textDescriptionType;
	}
	else if (tag == "dmdd")
	{
		return v4 ? IccDataType::multiLocalizedUnicodeType : IccDataType::textDescriptionType;
	}
	else if (tag == "gamt")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "kTRC")
	{
		return IccDataType::curveVariable;
	}
	else if (tag == "gXYZ")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "gTRC")
	{
		return IccDataType::curveVariable;
	}
	else if (tag == "lumi")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "meas")
	{
		return IccDataType::measurementType;
	}
	else if (tag == "wtpt")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "ncl2")
	{
		return IccDataType::namedColor2Type;
	}
	else if (tag == "resp")
	{
		return IccDataType::responseCurveSet16Type;
	}
	else if (tag == "pre0")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "pre1")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "pre2")
	{
		return IccDataType::lutVariable;
	}
	else if (tag == "desc")
	{
		return v4 ? IccDataType::multiLocalizedUnicodeType : IccDataType::textDescriptionType;
	}
	else if (tag == "pseq")
	{
		return IccDataType::profileSequenceDescType;
	}
	else if (tag == "rXYZ")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "rTRC")
	{
		return IccDataType::curveVariable;
	}
	else if (tag == "tech")
	{
		return IccDataType::signatureType;
	}
	else if (tag == "vued")
	{
		return v4 ? IccDataType::multiLocalizedUnicodeType : IccDataType::textDescriptionType;
	}
	else if (tag == "view")
	{
		return IccDataType::viewingConditionsType;
	}
	// Below tags are in v2 but not v4
	else if (tag == "crdi")
	{
		return IccDataType::crdInfoType;
	}
	else if (tag == "devs")
	{
		return IccDataType::deviceSettingsType;
	}
	else if (tag == "bkpt")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "ncol")
	{
		return IccDataType::namedColorType;
	}
	else if (tag == "psd0")
	{
		return IccDataType::dataType;
	}
	else if (tag == "psd1")
	{
		return IccDataType::dataType;
	}
	else if (tag == "psd2")
	{
		return IccDataType::dataType;
	}
	else if (tag == "psd3")
	{
		return IccDataType::dataType;
	}
	else if (tag == "ps2s")
	{
		return IccDataType::dataType;
	}
	else if (tag == "ps2i")
	{
		return IccDataType::dataType;
	}
	else if (tag == "scrd")
	{
		return IccDataType::textDescriptionType;
	}
	else if (tag == "scrn")
	{
		return IccDataType::screeningType;
	}
	else if (tag == "bfd ")
	{
		return IccDataType::ucrbgType;
	}
	// V4-only
	else if (tag == "B2D0")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "B2D1")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "B2D2")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "B2D3")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "cicp")
	{
		return IccDataType::cicpType;
	}
	else if (tag == "clro")
	{
		return IccDataType::colorantOrderType;
	}
	else if (tag == "clrt")
	{
		return IccDataType::colorantTableType;
	}
	else if (tag == "clot")
	{
		return IccDataType::colorantTableType;
	}
	else if (tag == "ciis")
	{
		return IccDataType::signatureType;
	}
	else if (tag == "D2B0")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "D2B1")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "D2B2")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "D2B3")
	{
		return IccDataType::multiProcessElementsType;
	}
	else if (tag == "meta")
	{
		return IccDataType::dictType;
	}
	else if (tag == "psid")
	{
		return IccDataType::profileSequenceIdentifierType;
	}
	else if (tag == "rig0")
	{
		return IccDataType::signatureType;
	}
	else if (tag == "rig2")
	{
		return IccDataType::signatureType;
	}
	else
	{
		return std::nullopt;
	}
}
