#include "gui/MainWindow.h"
#include "theme/DarkTheme.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char** argv)
{
	QCoreApplication::setApplicationName("IccUtil");
	QCoreApplication::setOrganizationName("IccUtil");

	QApplication app{ argc, argv };

	DarkTheme::apply_theme();

	MainWindow* const main_window = new MainWindow{};
	main_window->show();

	return app.exec();
}
