#pragma once

#include <QObject>
#include <QWidget>

class IccSignatureType;

class IccSignatureTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccSignatureTypeDetailsWidget(const IccSignatureType& sig, QWidget* parent = nullptr);
};
