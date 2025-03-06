#pragma once

#include <string>

#include <QObject>
#include <QWidget>

#include "icctypes/IccMultiLocalizedUnicodeType.h"

class QListWidget;
class QTextEdit;

class IccMultiLocalizedUnicodeTypeDetailsWidget : public QWidget
{
	Q_OBJECT

public:
	IccMultiLocalizedUnicodeTypeDetailsWidget(const IccMultiLocalizedUnicodeType& value, QWidget* parent = nullptr);

private:
	void handle_lang_list_item_changed();

	QListWidget* lang_list_widget = nullptr;
	QTextEdit* content_text_edit = nullptr;

	IccMultiLocalizedUnicodeType data;
};
