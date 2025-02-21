#include "IccDataType.h"

std::string IccDataTypeFuncs::to_string(const IccDataType input)
{
	switch (input)
	{
		case IccDataType::chromaticityType:
			return "Chromaticity";
		case IccDataType::cicpType:
			return "Coding-independent code points";
		case IccDataType::colorantOrderType:
			return "Colorant order";
		case IccDataType::colorantTableType:
			return "Colorant table";
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
		case IccDataType::multiProcessElementsType:
			return "Multi process elements";
		case IccDataType::multiLocalizedUnicodeType:
			return "Multi-localized unicode";
		case IccDataType::namedColor2Type:
			return "Named color2";
		case IccDataType::profileSequenceDescType:
			return "Profile sequence description";
		case IccDataType::profileSequenceIdentifierType:
			return "Profile sequence ID";
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
		default:
			return "Unknown type";
	}
}

std::optional<IccDataType> IccDataTypeFuncs::get_type_by_tag(const std::string& tag)
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
	else if (tag == "cprt")
	{
		return IccDataType::multiLocalizedUnicodeType;
	}
	else if (tag == "dmnd")
	{
		return IccDataType::multiLocalizedUnicodeType;
	}
	else if (tag == "dmdd")
	{
		return IccDataType::multiLocalizedUnicodeType;
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
	else if (tag == "meta")
	{
		return IccDataType::dictType;
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
	else if (tag == "rig0")
	{
		return IccDataType::signatureType;
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
		return IccDataType::multiLocalizedUnicodeType;
	}
	else if (tag == "pseq")
	{
		return IccDataType::profileSequenceDescType;
	}
	else if (tag == "psid")
	{
		return IccDataType::profileSequenceIdentifierType;
	}
	else if (tag == "rXYZ")
	{
		return IccDataType::xyzType;
	}
	else if (tag == "rTRC")
	{
		return IccDataType::curveVariable;
	}
	else if (tag == "rig2")
	{
		return IccDataType::signatureType;
	}
	else if (tag == "tech")
	{
		return IccDataType::signatureType;
	}
	else if (tag == "vued")
	{
		return IccDataType::multiLocalizedUnicodeType;
	}
	else if (tag == "view")
	{
		return IccDataType::viewingConditionsType;
	}
	// 'bkpt' is not part of the v2 standard but a lot of v2 profiles include it
	else if (tag == "bkpt")
	{
		return IccDataType::xyzType;
	}
	else
	{
		return std::nullopt;
	}
}
