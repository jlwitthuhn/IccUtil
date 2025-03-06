#include "ConvertColorWidget.h"

#include <cstdint>

#include <Qt>
#include <QComboBox>
#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QVariant>
#include <QVBoxLayout>

#include "color/ColorConverter.h"
#include "color/RgbFloatColor.h"
#include "color/XyChromaticity.h"
#include "color/XyyFloatColor.h"
#include "color/XyzFloatColor.h"
#include "core/ExitAssert.h"

namespace
{
	enum class ConversionType : std::uint8_t
	{
		XY_TO_SRGB,
		XYZ_TO_SRGB,
	};

	enum class ConversionInput : std::uint8_t
	{
		XY,
		XYZ,
	};

	ConversionInput input_from_type(const ConversionType type)
	{
		switch (type)
		{
			case ConversionType::XY_TO_SRGB:
				return ConversionInput::XY;
			case ConversionType::XYZ_TO_SRGB:
				return ConversionInput::XYZ;
			default:
				EXIT_ASSERT(false, "Invalid ConversionType in input_from_type");
		}
	}
}

ConvertColorWidget::ConvertColorWidget(QWidget* const parent) : QWidget{ parent }
{
	QVBoxLayout* const layout = new QVBoxLayout{ this };

	QWidget* const type_widget = new QWidget{ this };
	{
		QHBoxLayout* const type_layout = new QHBoxLayout{ type_widget };
		type_layout->setContentsMargins(0, 0, 0, 0);
		
		QLabel* const type_label = new QLabel{ "Convert: ", type_widget };

		type_combo = new QComboBox{ type_widget };
		type_combo->addItem("xy to sRGB", QVariant{ static_cast<int>(ConversionType::XY_TO_SRGB) });
		type_combo->addItem("XYZ to sRGB", QVariant{ static_cast<int>(ConversionType::XYZ_TO_SRGB) });
		connect(type_combo, &QComboBox::currentIndexChanged, this, &ConvertColorWidget::update_color_input);

		type_layout->addWidget(type_label);
		type_layout->addWidget(type_combo);
		type_layout->setStretch(1, 10);
	}

	color_input_widget = new QWidget{ this };
	update_color_input();

	QPushButton* const convert_button = new QPushButton{ "Convert", this };
	connect(convert_button, &QPushButton::clicked, this, &ConvertColorWidget::pressed_convert);

	text_edit = new QTextEdit{ this };
	text_edit->setReadOnly(true);

	layout->addWidget(type_widget);
	layout->addWidget(color_input_widget);
	layout->addWidget(convert_button);
	layout->addWidget(text_edit);
}

void ConvertColorWidget::pressed_convert()
{
	text_edit->clear();

	const QVariant type_var = type_combo->currentData(Qt::UserRole);
	const ConversionType type = static_cast<ConversionType>(type_var.toInt());

	switch (type)
	{
		case ConversionType::XY_TO_SRGB:
		{
			const std::vector<double> in_vec = get_color_inputs();
			EXIT_ASSERT(in_vec.size() == 2, "xy input must be size 2")
			const double in_x = in_vec[0];
			const double in_y = in_vec[1];

			const XyChromaticity chroma{ in_x, in_y };
			text_edit->append(QString{ "Input (xy): %1, %2" }.arg(in_x).arg(in_y));

			const XyyFloatColor xyy_color = ColorConverter::to_xyy(chroma);
			text_edit->append(QString{ "xyY: %1, %2, %3" }.arg(xyy_color.x).arg(xyy_color.y).arg(xyy_color.Y));

			const XyzFloatColor xyz_color = ColorConverter::to_xyz(xyy_color);
			text_edit->append(QString{ "XYZ: %1, %2, %3" }.arg(xyz_color.x).arg(xyz_color.y).arg(xyz_color.z));

			const RgbFloatColor rgb_color = ColorConverter::to_srgb(xyz_color);
			text_edit->append(QString{ "sRGB: %1, %2, %3" }.arg(rgb_color.r).arg(rgb_color.g).arg(rgb_color.b));

			break;
		}
		case ConversionType::XYZ_TO_SRGB:
		{
			const std::vector<double> in_vec = get_color_inputs();
			EXIT_ASSERT(in_vec.size() == 3, "XYZ input must be size 3")
			const double in_x = in_vec[0];
			const double in_y = in_vec[1];
			const double in_z = in_vec[2];

			const XyzFloatColor xyz_color{
				static_cast<float>(in_x),
				static_cast<float>(in_y),
				static_cast<float>(in_z)
			};
			text_edit->append(QString{ "Input (XYZ): %1, %2, %3" }.arg(xyz_color.x).arg(xyz_color.y).arg(xyz_color.z));

			const RgbFloatColor rgb_color = ColorConverter::to_srgb(xyz_color);
			text_edit->append(QString{ "sRGB: %1, %2, %3" }.arg(rgb_color.r).arg(rgb_color.g).arg(rgb_color.b));

			break;
		}
		default:
			EXIT_ASSERT(false, "Invalid conversion type in ConvertColorWidget::pressed_convert()");
	}
}

void ConvertColorWidget::update_color_input()
{
	QWidget* const old_color_input = color_input_widget;
	color_input_widget = new QWidget{ this };
	QHBoxLayout* const layout = new QHBoxLayout{ color_input_widget };
	layout->setContentsMargins(0, 0, 0, 0);

	const QVariant type_var = type_combo->currentData(Qt::UserRole);
	const ConversionType type = static_cast<ConversionType>(type_var.toInt());
	switch (input_from_type(type))
	{
		case ConversionInput::XY:
		{
			QLabel* const x_label = new QLabel{ "x:", color_input_widget };
			QLineEdit* const x_edit = new QLineEdit{ color_input_widget };
			x_edit->setValidator(new QDoubleValidator{ x_edit });
			x_edit->setPlaceholderText("0.0");
			x_edit->setPlaceholderText("0.0");

			QLabel* const y_label = new QLabel{ "y:", color_input_widget };
			QLineEdit* const y_edit = new QLineEdit{ color_input_widget };
			y_edit->setValidator(new QDoubleValidator{ y_edit });
			y_edit->setPlaceholderText("0.0");

			get_color_inputs = [x_edit, y_edit]() -> std::vector<double> {
				std::vector<double> result;
				result.resize(2);
				result[0] = x_edit->text().toDouble();
				result[1] = y_edit->text().toDouble();
				return result;
			};

			layout->addWidget(x_label);
			layout->addWidget(x_edit);
			layout->addWidget(y_label);
			layout->addWidget(y_edit);
			break;
		}
		case ConversionInput::XYZ:
		{
			QLabel* const x_label = new QLabel{ "X:", color_input_widget };
			QLineEdit* const x_edit = new QLineEdit{ color_input_widget };
			x_edit->setValidator(new QDoubleValidator{ x_edit });
			x_edit->setPlaceholderText("0.0");

			QLabel* const y_label = new QLabel{ "Y:", color_input_widget };
			QLineEdit* const y_edit = new QLineEdit{ color_input_widget };
			y_edit->setValidator(new QDoubleValidator{ y_edit });
			y_edit->setPlaceholderText("0.0");

			QLabel* const z_label = new QLabel{ "Z:", color_input_widget };
			QLineEdit* const z_edit = new QLineEdit{ color_input_widget };
			z_edit->setValidator(new QDoubleValidator{ z_edit });
			z_edit->setPlaceholderText("0.0");

			get_color_inputs = [x_edit, y_edit, z_edit]() -> std::vector<double> {
				std::vector<double> result;
				result.resize(3);
				result[0] = x_edit->text().toDouble();
				result[1] = y_edit->text().toDouble();
				result[2] = z_edit->text().toDouble();
				return result;
				};

			layout->addWidget(x_label);
			layout->addWidget(x_edit);
			layout->addWidget(y_label);
			layout->addWidget(y_edit);
			layout->addWidget(z_label);
			layout->addWidget(z_edit);
			break;
		}
		default:
			EXIT_ASSERT(false, "Invalid conversion type in ConvertColorWidget::update_color_input()");
	}

	this->layout()->replaceWidget(old_color_input, color_input_widget);
	delete old_color_input;
}