#include <QApplication>
#include <QCoreApplication>
#include <QTimer>

#include "gui/MainWindow.h"
#include "theme/DarkTheme.h"

int main(int argc, char** argv)
{
	QCoreApplication::setApplicationName("IccUtil");
	QCoreApplication::setOrganizationName("IccUtil");

	QApplication app{ argc, argv };

	DarkTheme::apply_theme();

	// Create window after application is running
	QTimer::singleShot(1, nullptr, []() {
		MainWindow* const main_window = new MainWindow{};
		main_window->show();
	});

	return app.exec();
}
