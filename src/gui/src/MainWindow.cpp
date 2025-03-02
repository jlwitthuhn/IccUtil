#include "MainWindow.h"

#include <cstddef>
#include <vector>

#include <QAction>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include "core/BuildInfo.h"
#include "icc/IccProfile.h"

#include "ChromaticityTopWidget.h"
#include "ConvertColorWidget.h"
#include "ProfileDetailsWidget.h"
#include "Util.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow{ parent }
{
	setWindowTitle("IccUtil");

	QMenuBar* const menu_bar = new QMenuBar{ this };
	{
		QMenu* const file_menu = new QMenu{ "File", menu_bar };
		{
			QAction* const open_action = new QAction{ "Open ICC Profile...", file_menu };
			connect(open_action, &QAction::triggered, this, &MainWindow::menu_file_open_icc_file_clicked);

			QAction* const exit_action = new QAction{ "Exit", file_menu };
			connect(exit_action, &QAction::triggered, this, &QMainWindow::close);

			file_menu->addAction(open_action);
			file_menu->addSeparator();
			file_menu->addAction(exit_action);
		}

		QMenu* const view_menu = new QMenu{ "View", menu_bar };
		{
			QAction* const chromaticity_action = new QAction{ "Chromaticity diagram...", view_menu };
			connect(chromaticity_action, &QAction::triggered, this, &MainWindow::menu_view_chromaticity_clicked);

			view_menu->addAction(chromaticity_action);
		}

		QMenu* const util_menu = new QMenu{ "Utilities", menu_bar };
		{
			QAction* const convert_color_action = new QAction{ "Convert color...", util_menu };
			connect(convert_color_action, &QAction::triggered, this, &MainWindow::menu_util_convert_color_clicked);

			util_menu->addAction(convert_color_action);
		}

		QMenu* const about_menu = new QMenu{ "About", menu_bar };
		{
			QAction* const github_action = new QAction{ "Visit repository on Github", about_menu };
			connect(github_action, &QAction::triggered, []() {
				QDesktopServices::openUrl(QUrl{ "https://github.com/jlwitthuhn/IccUtil" });
			});

			QMenu* const build_info_menu = new QMenu{ "Build info", about_menu };
			{
				if (const std::optional<std::string> git_hash = BuildInfo::git_short_hash())
				{
					QAction* const git_hash_action = new QAction{ "Git: " + QString::fromStdString(*git_hash), build_info_menu};
					build_info_menu->addAction(git_hash_action);
				}

				QAction* const compiler_action = new QAction{ "Compiler: " + QString::fromStdString(BuildInfo::compiler_version()), build_info_menu };
				QAction* const date_action = new QAction{ "Build date: " + QString::fromStdString(BuildInfo::build_date()), build_info_menu };

				build_info_menu->addAction(compiler_action);
				build_info_menu->addAction(date_action);
			}

			about_menu->addAction(github_action);
			about_menu->addMenu(build_info_menu);
		}

		menu_bar->addMenu(file_menu);
		menu_bar->addMenu(view_menu);
		menu_bar->addMenu(util_menu);
		menu_bar->addMenu(about_menu);
	}
	setMenuBar(menu_bar);

	profile_details_widget = new ProfileDetailsWidget{ this };
	setCentralWidget(profile_details_widget);
	resize(750, 600);
}

void MainWindow::menu_file_open_icc_file_clicked()
{
	const QString path = QFileDialog::getOpenFileName(this, "Select ICC Profile");
	QFile icc_file{ path };
	const bool open_success = icc_file.open(QIODevice::ReadOnly);
	if (!open_success)
	{
		QMessageBox message_box;
		message_box.setIcon(QMessageBox::Critical);
		message_box.setText("Failed to open file");
		message_box.exec();
		return;
	}

	constexpr std::int64_t MAX_FILE_SIZE = 1024 * 1024 * 32;
	if (icc_file.bytesAvailable() > MAX_FILE_SIZE)
	{
		QMessageBox message_box;
		message_box.setIcon(QMessageBox::Critical);
		message_box.setText("File is too large, must be under 32MB");
		message_box.exec();
		return;
	}

	const QByteArray q_bytes = icc_file.readAll();
	const std::vector<char> bytes{ q_bytes.begin(), q_bytes.end() };
	const Result<IccProfile> maybe_profile = IccProfile::from_bytes(bytes);
	if (!maybe_profile)
	{
		QMessageBox message_box;
		message_box.setIcon(QMessageBox::Critical);
		message_box.setText(QString{ "Failed to load profile: %1" }.arg(QString::fromStdString(maybe_profile.error().message)));
		message_box.exec();
		return;
	}

	profile_details_widget->load_profile(maybe_profile.get());
}

void MainWindow::menu_view_chromaticity_clicked()
{
	ChromaticityTopWidget* const chromaticity_widget = new ChromaticityTopWidget{ this };
	if (auto profile = profile_details_widget->get_profile())
	{
		chromaticity_widget->set_icc_profile(*profile);
	}
	util::present_application_modal_widget(chromaticity_widget);
}

void MainWindow::menu_util_convert_color_clicked()
{
	util::present_application_modal_widget(new ConvertColorWidget{ this });
}
