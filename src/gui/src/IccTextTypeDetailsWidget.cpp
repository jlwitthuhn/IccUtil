#include "IccTextTypeDetailsWidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>

#include "icctypes/IccTextType.h"

IccTextTypeDetailsWidget::IccTextTypeDetailsWidget(const std::string& tag_name, const IccTextType& text_type, QWidget* const parent) : QWidget { parent }
{
	setWindowTitle("Text");

	QLineEdit* const tag_name_edit = new QLineEdit{ QString::fromStdString(tag_name), this };
	tag_name_edit->setReadOnly(true);

	QTextEdit* const text_edit = new QTextEdit{ this };
	text_edit->setReadOnly(true);
	text_edit->setText(QString::fromStdString(text_type.get_string()));

	QFormLayout* const layout = new QFormLayout{ this };
	layout->addRow("Tag:", tag_name_edit);
	layout->addRow("Text:", text_edit);
}
