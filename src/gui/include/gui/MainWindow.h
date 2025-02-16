#pragma once

#include <array>

#include <QMainWindow>
#include <QWidget>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

protected:
	void menu_file_open_icc_file_clicked();
	void menu_util_convert_color_clicked();
};
