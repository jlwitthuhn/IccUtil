#pragma once

#include <functional>
#include <vector>

#include <QObject>
#include <QWidget>

class QComboBox;
class QTextEdit;

class ConvertColorWidget : public QWidget
{
	Q_OBJECT

public:
	ConvertColorWidget(QWidget* parent = nullptr);

protected:
	void pressed_convert();
	void update_color_input();

	std::function<std::vector<double>()> get_color_inputs;

	QComboBox* type_combo = nullptr;
	QWidget* color_input_widget = nullptr;
	QTextEdit* text_edit = nullptr;
};
