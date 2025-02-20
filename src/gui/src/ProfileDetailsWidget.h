#pragma once

#include <QObject>
#include <QWidget>

class QTableWidget;

class IccProfile;

class ProfileDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	ProfileDetailsWidget(QWidget* parent = nullptr);

	void load_profile(const IccProfile& profile);

protected:
	QTableWidget* header_table_widget = nullptr;
};
