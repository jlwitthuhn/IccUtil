#include "MainWindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "ChromaticityWidget.h"
#include "ConvertColorWidget.h"
#include "Util.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow{ parent }
{
	setWindowTitle("IccUtil");

	QMenuBar* const menu_bar = new QMenuBar{ this };
	{
		QMenu* const file_menu = new QMenu{ "File", menu_bar };
		{
			QAction* const open_action = new QAction{ "Open ICC Profile...", file_menu };

			QAction* const exit_action = new QAction{ "Exit", file_menu };
			connect(exit_action, &QAction::triggered, this, &QMainWindow::close);

			file_menu->addAction(open_action);
			file_menu->addSeparator();
			file_menu->addAction(exit_action);
		}

		QMenu* const util_menu = new QMenu{ "Utilities", menu_bar };
		{
			QAction* const convert_color_action = new QAction{ "Convert color...", util_menu };
			connect(convert_color_action, &QAction::triggered, this, &MainWindow::menu_util_convert_color_clicked);

			util_menu->addAction(convert_color_action);
		}

		menu_bar->addMenu(file_menu);
		menu_bar->addMenu(util_menu);
	}
	setMenuBar(menu_bar);

	ChromaticityWidget* const chroma_widget = new ChromaticityWidget{ this };
	setCentralWidget(chroma_widget);
}

void MainWindow::menu_util_convert_color_clicked()
{
	util::present_application_modal_widget(new ConvertColorWidget{ this });
}
