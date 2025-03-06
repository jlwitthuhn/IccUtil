#pragma once

#include <string>

#include <QObject>
#include <QWidget>

class IccTextType;

class IccTextTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccTextTypeDetailsWidget(const IccTextType& text_type, QWidget* parent = nullptr);
};
