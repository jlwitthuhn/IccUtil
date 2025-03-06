#include "IccTextTypeDetailsWidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>

#include "icctypes/IccTextType.h"

IccTextTypeDetailsWidget::IccTextTypeDetailsWidget(const IccTextType& text_type, QWidget* const parent) : QWidget { parent }
{
	setWindowTitle("Text");

	QTextEdit* const text_edit = new QTextEdit{ this };
	text_edit->setReadOnly(true);
	text_edit->setText(QString::fromStdString(text_type.get_string()));

	QVBoxLayout* const layout = new QVBoxLayout{ this };
	layout->addWidget(text_edit);
}
