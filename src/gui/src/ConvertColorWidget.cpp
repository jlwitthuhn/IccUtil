#include "ConvertColorWidget.h"

#include <QComboBox>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include "color/ColorConverter.h"
#include "color/RgbColor.h"
#include "color/XyChromaticity.h"
#include "color/XyyFloatColor.h"
#include "color/XyzFloatColor.h"

enum class ConversionType
{
	XY_TO_SRGB,
};

ConvertColorWidget::ConvertColorWidget(QWidget* const parent) : QWidget{ parent }
{
	QVBoxLayout* const layout = new QVBoxLayout{ this };

	QWidget* const input_widget = new QWidget{ this };
	{
		QHBoxLayout* const input_layout = new QHBoxLayout{ input_widget };
		
		QLabel* const type_label = new QLabel{ "Convert: ", input_widget};

		QComboBox* const type_combo = new QComboBox{ input_widget };
		type_combo->addItem("xy to sRGB", QVariant{ static_cast<int>(ConversionType::XY_TO_SRGB) });

		input_layout->addWidget(type_label);
		input_layout->addWidget(type_combo);
		input_layout->setStretch(1, 10);
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

	const XyyFloatColor xyy_color = ColorConverter::to_xyy(chroma);
	text_edit->append(QString{ "xyY: %1, %2, %3" }.arg(xyy_color.x).arg(xyy_color.y).arg(xyy_color.Y));

	const XyzFloatColor xyz_color = ColorConverter::to_xyz(xyy_color);
	text_edit->append(QString{ "XYZ: %1, %2, %3" }.arg(xyz_color.x).arg(xyz_color.y).arg(xyz_color.z));

	const RgbColor<float> rgb_color = ColorConverter::to_srgb(xyz_color);
	text_edit->append(QString{ "sRGB: %1, %2, %3" }.arg(rgb_color.r).arg(rgb_color.g).arg(rgb_color.b));
}
