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
	void menu_util_convert_color_clicked();
};
