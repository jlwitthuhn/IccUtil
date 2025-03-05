#pragma once

#include <string>

#include <QObject>
#include <QWidget>

class IccTextType;

class IccTextTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccTextTypeDetailsWidget(const std::string& tag_name, const IccTextType& text_type, QWidget* parent = nullptr);
};
