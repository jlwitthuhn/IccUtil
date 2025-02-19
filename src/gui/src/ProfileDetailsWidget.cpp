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
	table_widget->setRowCount(14);

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

	table_widget->setItem(7, 0, new QTableWidgetItem{ "Signature" });
	table_widget->setItem(7, 1, new QTableWidgetItem{ QString::fromStdString(header.get_signature_display()) });

	table_widget->setItem(8, 0, new QTableWidgetItem{ "Primary platform" });
	table_widget->setItem(8, 1, new QTableWidgetItem{ QString::fromStdString(header.get_primary_platform_display()) });

	table_widget->setItem(9, 0, new QTableWidgetItem{ "Profile flags" });
	table_widget->setItem(9, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_flags_display()) });

	table_widget->setItem(10, 0, new QTableWidgetItem{ "Device manufacturer" });
	table_widget->setItem(10, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_manufacturer_display()) });

	table_widget->setItem(11, 0, new QTableWidgetItem{ "Device model" });
	table_widget->setItem(11, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_model_display()) });

	table_widget->setItem(12, 0, new QTableWidgetItem{ "Device attributes" });
	table_widget->setItem(12, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_attributes_display()) });

	table_widget->setItem(13, 0, new QTableWidgetItem{ "Rendering intent" });
	table_widget->setItem(13, 1, new QTableWidgetItem{ QString::fromStdString(header.get_rendering_intent_display()) });
}
