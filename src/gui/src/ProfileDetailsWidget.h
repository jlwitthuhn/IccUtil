#pragma once

#include <memory>
#include <optional>
#include <string>

#include <QObject>
#include <QWidget>

class QGroupBox;
class QLineEdit;
class QTableWidget;

class IccProfile;

class ProfileDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	ProfileDetailsWidget(QWidget* parent = nullptr);

	void load_profile(const QString& path, const IccProfile& profile);
	std::shared_ptr<IccProfile> get_profile() const { return loaded_profile; }

protected:
	std::optional<int> get_selected_tag_row() const;
	std::string get_tag_signature(int row) const;

	void clear_data_layout();

	// Slots
	void tag_selection_changed();

	QLineEdit* file_path_edit = nullptr;
	QGroupBox* data_group = nullptr;
	QTableWidget* header_table_widget = nullptr;
	QTableWidget* tags_table_widget = nullptr;

	std::shared_ptr<IccProfile> loaded_profile;
};
