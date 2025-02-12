#pragma once

#include <QObject>
#include <QWidget>

class QLineEdit;
class QTextEdit;

class ConvertColorWidget : public QWidget
{
	Q_OBJECT

public:
	ConvertColorWidget(QWidget* parent = nullptr);

protected:
	void pressed_convert();

	QLineEdit* in1_edit = nullptr;
	QLineEdit* in2_edit = nullptr;
	QTextEdit* text_edit = nullptr;
};
