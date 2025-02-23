#pragma once

#include <memory>
#include <optional>

#include <QObject>
#include <QWidget>

#include "icc/IccProfile.h"

class QPushButton;
class QTableWidget;

class ProfileDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	ProfileDetailsWidget(QWidget* parent = nullptr);

	void load_profile(const IccProfile& profile);

protected:
	std::optional<int> get_selected_tag_row() const;
	std::string get_tag_signature(int row) const;

	// Slots
	void clicked_view_details();
	void tag_selection_changed();

	QTableWidget* header_table_widget = nullptr;
	QTableWidget* tags_table_widget = nullptr;
	QPushButton* view_tag_details_button = nullptr;

	std::unique_ptr<IccProfile> loaded_profile;
};
