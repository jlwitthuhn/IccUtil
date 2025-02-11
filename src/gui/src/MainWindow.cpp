#include "MainWindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "ChromaticityWidget.h"

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

		menu_bar->addMenu(file_menu);
	}
	setMenuBar(menu_bar);

	ChromaticityWidget* const chroma_widget = new ChromaticityWidget{ this };
	setCentralWidget(chroma_widget);
}
