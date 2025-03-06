#include "ProfileDetailsWidget.h"

#include <set>

#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QList>
#include <QMessageBox>
#include <QSplitter>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableWidgetSelectionRange>
#include <QVBoxLayout>

#include "core/ExitAssert.h"
#include "icc/IccDataType.h"
#include "icc/IccFileTagEntry.h"
#include "icc/IccProfile.h"
#include "icctypes/IccMultiLocalizedUnicodeType.h"
#include "icctypes/IccTextType.h"
#include "icctypes/IccXyzType.h"

#include "IccMultiLocalizedUnicodeTypeDetailsWidget.h"
#include "IccTextTypeDetailsWidget.h"
#include "IccXyzTypeDetailsWidget.h"
#include "Util.h"

ProfileDetailsWidget::ProfileDetailsWidget(QWidget* const parent) : QWidget{ parent }
{
	QSplitter* const splitter = new QSplitter{ Qt::Vertical, this };

	QWidget* const top_row = new QWidget{ splitter };
	{
		QGroupBox* const header_details = new QGroupBox{ "Header", top_row };
		{
			header_table_widget = new QTableWidget{ header_details };

			header_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
			header_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
			header_table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
			header_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
			header_table_widget->horizontalHeader()->setStretchLastSection(true);
			header_table_widget->verticalHeader()->setVisible(false);
			header_table_widget->setColumnCount(2);
			header_table_widget->setRowCount(0);

			header_table_widget->setHorizontalHeaderLabels({ "Field", "Contents" });

			QVBoxLayout* const header_layout = new QVBoxLayout{ header_details };
			header_layout->addWidget(header_table_widget);
		}

		QGroupBox* const tags_details = new QGroupBox{ "Tags", top_row };
		{
			tags_table_widget = new QTableWidget{ tags_details };

			tags_table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
			tags_table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
			tags_table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
			tags_table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
			tags_table_widget->horizontalHeader()->setStretchLastSection(true);
			tags_table_widget->verticalHeader()->setVisible(false);
			tags_table_widget->setColumnCount(3);
			tags_table_widget->setRowCount(0);

			tags_table_widget->setHorizontalHeaderLabels({ "Tag", "Type", "Size" });

			connect(tags_table_widget, &QTableWidget::itemSelectionChanged, this, &ProfileDetailsWidget::tag_selection_changed);

			QVBoxLayout* const tags_layout = new QVBoxLayout{ tags_details };
			tags_layout->addWidget(tags_table_widget);
		}

		QHBoxLayout* const top_layout = new QHBoxLayout{ top_row };
		top_layout->setContentsMargins(0, 0, 0, 0);
		top_layout->addWidget(header_details);
		top_layout->addWidget(tags_details);
	}

	data_group = new QGroupBox{ "Data", splitter };
	data_group->setMinimumHeight(200);
	{
		QVBoxLayout* const data_layout = new QVBoxLayout{ data_group };
		data_layout->setContentsMargins(0, 0, 0, 0);
	}

	QVBoxLayout* const layout = new QVBoxLayout{ this };
	layout->addWidget(splitter);
}

void ProfileDetailsWidget::load_profile(const IccProfile& profile)
{
	header_table_widget->clearContents();

	// Header view
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

	// Tags view
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

		const std::optional<IccDataType> opt_type = IccDataTypeFuncs::get_type_by_tag(sig_str, profile.icc_v4());
		if (opt_type)
		{
			tags_table_widget->setItem(i, 1, new QTableWidgetItem{ QString::fromStdString(IccDataTypeFuncs::to_string(*opt_type)) });
		}
		else
		{
			tags_table_widget->setItem(i, 1, new QTableWidgetItem{ "Unknown" });
		}
	}

	loaded_profile = std::make_shared<IccProfile>(profile);
}

std::optional<int> ProfileDetailsWidget::get_selected_tag_row() const
{
	const QList<QTableWidgetSelectionRange> selections = tags_table_widget->selectedRanges();
	if (selections.size() == 0)
	{
		return std::nullopt;
	}
	const QTableWidgetSelectionRange the_selection = selections.first();
	EXIT_ASSERT(the_selection.rowCount() == 1, "Only one tag row can be selected");
	return the_selection.bottomRow();
}

std::string ProfileDetailsWidget::get_tag_signature(const int row) const
{
	QTableWidgetItem* const selected_tag_item = tags_table_widget->item(row, 0);
	EXIT_ASSERT(selected_tag_item != nullptr, "Selected item cannot be nullptr");
	return selected_tag_item->text().toStdString();
}

void ProfileDetailsWidget::clear_data_layout()
{
	while (QLayoutItem* const this_item = data_group->layout()->takeAt(0))
	{
		delete this_item->widget();
		delete this_item;
	}
}

void ProfileDetailsWidget::tag_selection_changed()
{
	EXIT_ASSERT(loaded_profile, "A profile must be loaded when selecting a tag");
	clear_data_layout();

	const std::optional<int> selected_row = get_selected_tag_row();
	if (!selected_row)
	{
		return;
	}

	// Every type here MUST appear in the below switch
	static const std::set<IccDataType> viewable_types = {
		IccDataType::multiLocalizedUnicodeType,
		IccDataType::textType,
		IccDataType::xyzType,
	};

	const std::string selected_tag_signature = get_tag_signature(*selected_row);
	const std::optional<IccDataType> selected_type = IccDataTypeFuncs::get_type_by_tag(selected_tag_signature, loaded_profile->icc_v4());
	if (!selected_type || viewable_types.count(*selected_type) == 0)
	{
		return;
	}

	const std::span<const char> bytes = loaded_profile->get_body().get_tag_bytes(selected_tag_signature);

	switch (*selected_type)
	{
		case IccDataType::multiLocalizedUnicodeType:
		{
			if (!IccMultiLocalizedUnicodeType::is_valid(bytes))
			{
				QMessageBox::warning(this, "Invalid data", "This tag contains invalid 'mluc' data and cannot be loaded");
				return;
			}
			const IccMultiLocalizedUnicodeType mluc_type{ bytes };
			IccMultiLocalizedUnicodeTypeDetailsWidget* const details_widget = new IccMultiLocalizedUnicodeTypeDetailsWidget{ mluc_type, this };
			data_group->layout()->addWidget(details_widget);
			return;
		}
		case IccDataType::textType:
		{
			if (!IccTextType::is_valid(bytes))
			{
				QMessageBox::warning(this, "Invalid data", "This tag contains invalid 'text' data and cannot be loaded");
				return;
			}
			const IccTextType text_type{ bytes };
			IccTextTypeDetailsWidget* const details_widget = new IccTextTypeDetailsWidget{ text_type, this };
			data_group->layout()->addWidget(details_widget);
			return;
		}
		case IccDataType::xyzType:
		{
			if (!IccXyzType::is_valid(bytes))
			{
				QMessageBox::warning(this, "Invalid data", "This tag contains invalid 'xyz ' data and cannot be loaded");
				return;
			}
			const IccXyzType xyz_type{ bytes };
			IccXyzTypeDetailsWidget* const details_widget = new IccXyzTypeDetailsWidget{ xyz_type, this };
			data_group->layout()->addWidget(details_widget);
			return;
		}
		default:
			EXIT_ASSERT(false, "Selected type has no GUI");
	}
}
