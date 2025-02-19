#include "ProfileDetailsWidget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include "icc/IccProfile.h"

ProfileDetailsWidget::ProfileDetailsWidget(QWidget* const parent) : QWidget{ parent }
{
	QGroupBox* const header_details = new QGroupBox{ "Header", this };
	{
		table_widget = new QTableWidget{ header_details };
		{
			table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
			table_widget->verticalHeader()->setVisible(false);
			table_widget->setColumnCount(2);
			table_widget->setRowCount(0);

			table_widget->setHorizontalHeaderLabels({ "Field", "Contents" });
		}

		QVBoxLayout* const header_layout = new QVBoxLayout{ header_details };
		header_layout->addWidget(table_widget);
	}

	QHBoxLayout* const layout = new QHBoxLayout{ this };
	layout->addWidget(header_details);
}

void ProfileDetailsWidget::load_profile(const IccProfile& profile)
{
	table_widget->clearContents();

	const IccFileHeader& header = profile.get_header();
	table_widget->setRowCount(7);

	table_widget->setItem(0, 0, new QTableWidgetItem{ "Profile size" });
	table_widget->setItem(0, 1, new QTableWidgetItem{ QString{ "%1" }.arg(header.get_profile_size()) });

	table_widget->setItem(1, 0, new QTableWidgetItem{ "Preferred CMM" });
	table_widget->setItem(1, 1, new QTableWidgetItem{ QString::fromStdString(header.get_preferred_cmm_type_display()) });

	table_widget->setItem(2, 0, new QTableWidgetItem{ "Profile version" });
	table_widget->setItem(2, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_version_display()) });

	table_widget->setItem(3, 0, new QTableWidgetItem{ "Profile/device class" });
	table_widget->setItem(3, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_device_class_display()) });

	table_widget->setItem(4, 0, new QTableWidgetItem{ "Data colour space" });
	table_widget->setItem(4, 1, new QTableWidgetItem{ QString::fromStdString(header.get_data_color_space_display()) });

	table_widget->setItem(5, 0, new QTableWidgetItem{ "PCS" });
	table_widget->setItem(5, 1, new QTableWidgetItem{ QString::fromStdString(header.get_pcs_display()) });

	table_widget->setItem(6, 0, new QTableWidgetItem{ "Date and time" });
	table_widget->setItem(6, 1, new QTableWidgetItem{ QString::fromStdString(header.get_date_time_display()) });
}
