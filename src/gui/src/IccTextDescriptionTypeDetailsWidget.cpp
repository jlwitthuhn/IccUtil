#include "IccTextDescriptionTypeDetailsWidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>

#include "icc/Util.h"
#include "icctypes/IccTextDescriptionType.h"

IccTextDescriptionTypeDetailsWidget::IccTextDescriptionTypeDetailsWidget(const IccTextDescriptionType& text_desc, QWidget* const parent) : QWidget{ parent }
{
	QTextEdit* const ascii_text_edit = new QTextEdit{ this };
	ascii_text_edit->setReadOnly(true);
	ascii_text_edit->setText(QString::fromStdString(text_desc.get_ascii_string()));

	QLineEdit* unicode_lang_edit = nullptr;
	if (text_desc.get_unicode_lang() > 0)
	{
		unicode_lang_edit = new QLineEdit{ this };
		unicode_lang_edit->setReadOnly(true);
		unicode_lang_edit->setText(QString::number(text_desc.get_unicode_lang()));
	}

	QTextEdit* unicode_text_edit = nullptr;
	if (text_desc.get_unicode_count() > 0)
	{
		const std::vector<char16_t> unicode_str = text_desc.get_unicode_string();
		unicode_text_edit = new QTextEdit{ this };
		unicode_text_edit->setReadOnly(true);
		unicode_text_edit->setText(QString::fromUtf16(unicode_str.data(), unicode_str.size()));
	}

	QLineEdit* script_code_edit = nullptr;
	if (text_desc.get_script_code_code() > 0)
	{
		script_code_edit = new QLineEdit{ this };
		script_code_edit->setReadOnly(true);
		script_code_edit->setText(QString::number(text_desc.get_script_code_code()));
	}

	QTextEdit* mac_profile_text_edit = nullptr;
	if (text_desc.get_mac_desc_count() > 0)
	{
		const std::vector<char> mac_string = text_desc.get_mac_desc_string();
		const std::string formatted_string = util::format_hex(std::span{ mac_string });
		mac_profile_text_edit = new QTextEdit{ this };
		mac_profile_text_edit->setReadOnly(true);
		mac_profile_text_edit->setText(QString::fromStdString(formatted_string));
	}

	QFormLayout* const layout = new QFormLayout{ this };
	layout->addRow("ASCII", ascii_text_edit);
	if (unicode_lang_edit)
	{
		layout->addRow("Unicode lang", unicode_lang_edit);
	}
	if (unicode_text_edit)
	{
		layout->addRow("Unicode", unicode_text_edit);
	}
	if (script_code_edit)
	{
		layout->addRow("Script code", script_code_edit);
	}
	if (mac_profile_text_edit)
	{
		layout->addRow("Mac", mac_profile_text_edit);
	}
}
