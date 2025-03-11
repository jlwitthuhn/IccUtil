#pragma once

#include <QObject>
#include <QWidget>

class IccTextDescriptionType;

class IccTextDescriptionTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccTextDescriptionTypeDetailsWidget(const IccTextDescriptionType& text_desc, QWidget* parent = nullptr);
};
