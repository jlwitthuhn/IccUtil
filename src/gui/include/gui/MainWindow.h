#pragma once

#include <QMainWindow>
#include <QObject>

class QWidget;

class ProfileDetailsWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

protected:
	void menu_file_open_icc_file_clicked();
	void menu_view_chromaticity_clicked();
	void menu_util_convert_color_clicked();

	ProfileDetailsWidget* profile_details_widget = nullptr;
};
