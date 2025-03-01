#include "DarkTheme.h"

#include <QApplication>
#include <QPalette>
#include <QStyle>

void DarkTheme::apply_theme()
{
	QApplication::setStyle("Fusion");
	QApplication::setPalette(QApplication::style()->standardPalette());

	QPalette main_palette;

	const char* const color_background = "#303030";
	const char* const color_background_alt = "#202020";
	const char* const color_background_input = "#202020";
	const char* const color_text = "#FFFFFF";
	const char* const color_text_alt = "#DDDDDD";
	const char* const color_text_disabled = "#BBBBBB";

	main_palette.setColor(QPalette::Active, QPalette::Window, color_background);
	main_palette.setColor(QPalette::Active, QPalette::WindowText, color_text);
	main_palette.setColor(QPalette::Active, QPalette::Base, color_background_input);
	main_palette.setColor(QPalette::Active, QPalette::AlternateBase, color_background_alt);
	main_palette.setColor(QPalette::Active, QPalette::ToolTipBase, "#FFFFFF");
	main_palette.setColor(QPalette::Active, QPalette::ToolTipText, "#000000");
	main_palette.setColor(QPalette::Active, QPalette::PlaceholderText, color_text_disabled);
	main_palette.setColor(QPalette::Active, QPalette::Text, color_text);
	main_palette.setColor(QPalette::Active, QPalette::Button, color_background);
	main_palette.setColor(QPalette::Active, QPalette::ButtonText, color_text);
	main_palette.setColor(QPalette::Active, QPalette::BrightText, color_text_alt);

	main_palette.setColor(QPalette::Inactive, QPalette::Window, color_background);
	main_palette.setColor(QPalette::Inactive, QPalette::WindowText, color_text);
	main_palette.setColor(QPalette::Inactive, QPalette::Base, color_background_input);
	main_palette.setColor(QPalette::Inactive, QPalette::AlternateBase, color_background_alt);
	main_palette.setColor(QPalette::Inactive, QPalette::ToolTipBase, "#FFFFFF");
	main_palette.setColor(QPalette::Inactive, QPalette::ToolTipText, "#000000");
	main_palette.setColor(QPalette::Inactive, QPalette::PlaceholderText, color_text_disabled);
	main_palette.setColor(QPalette::Inactive, QPalette::Text, color_text);
	main_palette.setColor(QPalette::Inactive, QPalette::Button, color_background);
	main_palette.setColor(QPalette::Inactive, QPalette::ButtonText, color_text);
	main_palette.setColor(QPalette::Inactive, QPalette::BrightText, color_text_alt);

	main_palette.setColor(QPalette::Disabled, QPalette::Window, color_background);
	main_palette.setColor(QPalette::Disabled, QPalette::WindowText, color_text_disabled);
	main_palette.setColor(QPalette::Disabled, QPalette::Base, color_background);
	main_palette.setColor(QPalette::Disabled, QPalette::AlternateBase, color_background_alt);
	main_palette.setColor(QPalette::Disabled, QPalette::ToolTipBase, "#FFFFFF");
	main_palette.setColor(QPalette::Disabled, QPalette::ToolTipText, "#000000");
	main_palette.setColor(QPalette::Disabled, QPalette::PlaceholderText, color_text_disabled);
	main_palette.setColor(QPalette::Disabled, QPalette::Text, color_text_disabled);
	main_palette.setColor(QPalette::Disabled, QPalette::Button, color_background);
	main_palette.setColor(QPalette::Disabled, QPalette::ButtonText, color_text_disabled);
	main_palette.setColor(QPalette::Disabled, QPalette::BrightText, color_text_alt);

	QPalette menu_palette{ main_palette };

	menu_palette.setColor(QPalette::Active, QPalette::Base, color_background_alt);
	menu_palette.setColor(QPalette::Inactive, QPalette::Base, color_background_alt);
	menu_palette.setColor(QPalette::Disabled, QPalette::Base, color_background_alt);

	QPalette menu_bar_palette{ main_palette };

	menu_bar_palette.setColor(QPalette::Active, QPalette::Window, color_background_alt);
	menu_bar_palette.setColor(QPalette::Inactive, QPalette::Window, color_background_alt);
	menu_bar_palette.setColor(QPalette::Disabled, QPalette::Window, color_background_alt);

	QApplication::setPalette(main_palette);
	QApplication::setPalette(menu_palette, "QMenu");
	QApplication::setPalette(menu_bar_palette, "QMenuBar");
}
