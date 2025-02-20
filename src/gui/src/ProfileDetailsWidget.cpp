#include "ProfileDetailsWidget.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include "icc/IccDataType.h"
#include "icc/IccFileTagEntry.h"
#include "icc/IccProfile.h"

ProfileDetailsWidget::ProfileDetailsWidget(QWidget* const parent) : QWidget{ parent }
{
	QGroupBox* const header_details = new QGroupBox{ "Header", this };
	{
		header_table_widget = new QTableWidget{ header_details };

		header_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		header_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		header_table_widget->horizontalHeader()->setStretchLastSection(true);
		header_table_widget->verticalHeader()->setVisible(false);
		header_table_widget->setColumnCount(2);
		header_table_widget->setRowCount(0);

		header_table_widget->setHorizontalHeaderLabels({ "Field", "Contents" });

		QVBoxLayout* const header_layout = new QVBoxLayout{ header_details };
		header_layout->addWidget(header_table_widget);
	}

	QGroupBox* const tags_details = new QGroupBox{ "Tags", this };
	{
		tags_table_widget = new QTableWidget{ tags_details };

		tags_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
		tags_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		tags_table_widget->horizontalHeader()->setStretchLastSection(true);
		tags_table_widget->verticalHeader()->setVisible(false);
		tags_table_widget->setColumnCount(3);
		tags_table_widget->setRowCount(0);

		tags_table_widget->setHorizontalHeaderLabels({ "Tag", "Type", "Size" });

		QVBoxLayout* const tags_layout = new QVBoxLayout{ tags_details };
		tags_layout->addWidget(tags_table_widget);
	}

	QHBoxLayout* const layout = new QHBoxLayout{ this };
	layout->addWidget(header_details);
	layout->addWidget(tags_details);
}

void ProfileDetailsWidget::load_profile(const IccProfile& profile)
{
	header_table_widget->clearContents();

	// Header view
	{
		const IccFileHeader& header = profile.get_header();
		header_table_widget->setRowCount(17);

		header_table_widget->setItem(0, 0, new QTableWidgetItem{ "Profile size" });
		header_table_widget->setItem(0, 1, new QTableWidgetItem{ QString{ "%1" }.arg(header.get_profile_size()) });

		header_table_widget->setItem(1, 0, new QTableWidgetItem{ "Preferred CMM" });
		header_table_widget->setItem(1, 1, new QTableWidgetItem{ QString::fromStdString(header.get_preferred_cmm_type_display()) });

		header_table_widget->setItem(2, 0, new QTableWidgetItem{ "Profile version" });
		header_table_widget->setItem(2, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_version_display()) });

		header_table_widget->setItem(3, 0, new QTableWidgetItem{ "Profile/device class" });
		header_table_widget->setItem(3, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_device_class_display()) });

		header_table_widget->setItem(4, 0, new QTableWidgetItem{ "Data colour space" });
		header_table_widget->setItem(4, 1, new QTableWidgetItem{ QString::fromStdString(header.get_data_color_space_display()) });

		header_table_widget->setItem(5, 0, new QTableWidgetItem{ "PCS" });
		header_table_widget->setItem(5, 1, new QTableWidgetItem{ QString::fromStdString(header.get_pcs_display()) });

		header_table_widget->setItem(6, 0, new QTableWidgetItem{ "Date and time" });
		header_table_widget->setItem(6, 1, new QTableWidgetItem{ QString::fromStdString(header.get_date_time_display()) });

		header_table_widget->setItem(7, 0, new QTableWidgetItem{ "Signature" });
		header_table_widget->setItem(7, 1, new QTableWidgetItem{ QString::fromStdString(header.get_signature_display()) });

		header_table_widget->setItem(8, 0, new QTableWidgetItem{ "Primary platform" });
		header_table_widget->setItem(8, 1, new QTableWidgetItem{ QString::fromStdString(header.get_primary_platform_display()) });

		header_table_widget->setItem(9, 0, new QTableWidgetItem{ "Profile flags" });
		header_table_widget->setItem(9, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_flags_display()) });

		header_table_widget->setItem(10, 0, new QTableWidgetItem{ "Device manufacturer" });
		header_table_widget->setItem(10, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_manufacturer_display()) });

		header_table_widget->setItem(11, 0, new QTableWidgetItem{ "Device model" });
		header_table_widget->setItem(11, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_model_display()) });

		header_table_widget->setItem(12, 0, new QTableWidgetItem{ "Device attributes" });
		header_table_widget->setItem(12, 1, new QTableWidgetItem{ QString::fromStdString(header.get_device_attributes_display()) });

		header_table_widget->setItem(13, 0, new QTableWidgetItem{ "Rendering intent" });
		header_table_widget->setItem(13, 1, new QTableWidgetItem{ QString::fromStdString(header.get_rendering_intent_display()) });

		header_table_widget->setItem(14, 0, new QTableWidgetItem{ "Illuminant" });
		header_table_widget->setItem(14, 1, new QTableWidgetItem{ QString::fromStdString(header.get_illuminant_xyz_display()) });

		header_table_widget->setItem(15, 0, new QTableWidgetItem{ "Profile creator signature" });
		header_table_widget->setItem(15, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_creator_signature_display()) });

		header_table_widget->setItem(16, 0, new QTableWidgetItem{ "Profile ID" });
		header_table_widget->setItem(16, 1, new QTableWidgetItem{ QString::fromStdString(header.get_profile_id_display()) });
	}

	// Tags view
	{
		const IccFileBody& body = profile.get_body();
		const std::uint32_t tag_count = body.get_tag_count();
		tags_table_widget->setRowCount(tag_count);

		for (std::uint32_t i = 0; i < tag_count; i++)
		{
			const IccFileTagEntry entry = body.get_tag(i);
			const std::array<char, 4> sig = entry.get_signature();
			const std::string sig_str{ sig.begin(), sig.end() };
			tags_table_widget->setItem(i, 0, new QTableWidgetItem{ QString::fromStdString(sig_str) });
			tags_table_widget->setItem(i, 2, new QTableWidgetItem{ QString{ "%1" }.arg(entry.get_size()) });

			const std::optional<IccDataType> opt_type = IccDataTypeFuncs::get_type_by_tag(sig_str);
			if (opt_type)
			{
				tags_table_widget->setItem(i, 1, new QTableWidgetItem{ QString::fromStdString(IccDataTypeFuncs::to_string(*opt_type)) });
			}
			else
			{
				tags_table_widget->setItem(i, 1, new QTableWidgetItem{ "Unknown" });
			}
		}
	}
}
