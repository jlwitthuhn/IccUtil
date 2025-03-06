#include <functional>
#include <string>

#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QString>
#include <QTimer>

#include "core/ExitAssert.h"
#include "gui/MainWindow.h"
#include "theme/DarkTheme.h"

static void assert_failed(const std::string& message)
{
	QMessageBox::critical(nullptr, "Error: Assert Failed", QString::fromStdString(message));
}

int main(int argc, char** argv)
{
	QCoreApplication::setApplicationName("IccUtil");
	QCoreApplication::setOrganizationName("IccUtil");

	const QApplication app{ argc, argv };

	DarkTheme::apply_theme();

	// Create window after application is running
	QTimer::singleShot(1, nullptr, []() {
		ExitAssert::set_assert_callback(assert_failed);
		MainWindow* const main_window = new MainWindow{};
		main_window->show();
	});

	return app.exec();
}
