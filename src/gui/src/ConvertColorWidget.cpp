#include "ConvertColorWidget.h"

#include <QComboBox>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include "color/RgbColor.h"
#include "color/SimpleColorConverter.h"
#include "color/XyChromaticity.h"
#include "color/XyzFloatColor.h"

ConvertColorWidget::ConvertColorWidget(QWidget* const parent) : QWidget{ parent }
{
	QVBoxLayout* const layout = new QVBoxLayout{ this };

	QWidget* const input_widget = new QWidget{ this };
	{
		QFormLayout* const input_layout = new QFormLayout{ input_widget };
		
		QComboBox* const src_combo = new QComboBox{ input_widget };
		src_combo->addItem("xy");

		QComboBox* const dst_combo = new QComboBox{ input_widget };
		dst_combo->addItem("sRGB");

		input_layout->addRow("From:", src_combo);
		input_layout->addRow("To:", dst_combo);
	}

	QWidget* const color_widget = new QWidget{ this };
	{
		QHBoxLayout* const color_layout = new QHBoxLayout{ color_widget };

		QLabel* const in1_label = new QLabel{ "x:", color_widget };
		in1_edit = new QLineEdit{ color_widget };
		in1_edit->setValidator(new QDoubleValidator{ in1_edit });

		QLabel* const in2_label = new QLabel{ "y:", color_widget };
		in2_edit = new QLineEdit{ color_widget };
		in2_edit->setValidator(new QDoubleValidator{ in2_edit });

		color_layout->addWidget(in1_label);
		color_layout->addWidget(in1_edit);
		color_layout->addWidget(in2_label);
		color_layout->addWidget(in2_edit);
	}

	QPushButton* const convert_button = new QPushButton{ "Convert", this };
	connect(convert_button, &QPushButton::clicked, this, &ConvertColorWidget::pressed_convert);

	text_edit = new QTextEdit{ this };
	text_edit->setReadOnly(true);

	layout->addWidget(input_widget);
	layout->addWidget(color_widget);
	layout->addWidget(convert_button);
	layout->addWidget(text_edit);
}

void ConvertColorWidget::pressed_convert()
{
	text_edit->clear();

	const double in_x = in1_edit->text().toDouble();
	const double in_y = in2_edit->text().toDouble();

	const XyChromaticity chroma{ in_x, in_y };
	text_edit->append(QString{ "Input (xy): %1, %2" }.arg(in_x).arg(in_y));

	const XyzFloatColor xyz_color{ chroma };
	text_edit->append(QString{ "XYZ: %1, %2, %3" }.arg(xyz_color.x).arg(xyz_color.y).arg(xyz_color.z));

	const RgbColor<float> rgb_color = SimpleColorConverter::to_srgb(xyz_color);
	text_edit->append(QString{ "sRGB: %1, %2, %3" }.arg(rgb_color.r).arg(rgb_color.g).arg(rgb_color.b));
}
