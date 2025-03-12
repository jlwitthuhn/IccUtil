#include "IccSignatureTypeDetailsWidget.h"

#include <QFormLayout>
#include <QLineEdit>

#include "icctypes/IccSignatureType.h"

IccSignatureTypeDetailsWidget::IccSignatureTypeDetailsWidget(const IccSignatureType& sig, QWidget* const parent) : QWidget { parent }
{
	QLineEdit* const line_edit = new QLineEdit{ this };
	line_edit->setReadOnly(true);
	line_edit->setText(QString::fromStdString(sig.get_signature_str()));

	QFormLayout* const layout = new QFormLayout{ this };
	layout->addRow("Signature", line_edit);
}
