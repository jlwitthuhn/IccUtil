#pragma once

#include <string>

#include <QObject>
#include <QWidget>

#include "icctypes/IccXyzType.h"

class IccXyzTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccXyzTypeDetailsWidget(const std::string& tag_name, const IccXyzType& value, QWidget* parent = nullptr);
};
