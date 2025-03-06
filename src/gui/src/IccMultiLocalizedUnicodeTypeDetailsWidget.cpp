#include "IccMultiLocalizedUnicodeTypeDetailsWidget.h"

#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include <Qt>
#include <QtTypes>
#include <QListWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QString>
#include <QTextEdit>
#include <QVariant>
#include <QVBoxLayout>

IccMultiLocalizedUnicodeTypeDetailsWidget::IccMultiLocalizedUnicodeTypeDetailsWidget(const IccMultiLocalizedUnicodeType& value, QWidget* const parent) :
	QWidget{ parent },
	data{ value }
{
	setWindowTitle("Localized Unicode String");
	QHBoxLayout* const layout = new QHBoxLayout{ this };

	{
		QGroupBox* const lang_group = new QGroupBox{ "Language", this };
		{
			lang_list_widget = new QListWidget{ lang_group };
			connect(lang_list_widget, &QListWidget::currentItemChanged, this, &IccMultiLocalizedUnicodeTypeDetailsWidget::handle_lang_list_item_changed);

			QVBoxLayout* const lang_group_layout = new QVBoxLayout{ lang_group };
			lang_group_layout->addWidget(lang_list_widget);
		}

		layout->addWidget(lang_group, 1);
	}
	{
		QGroupBox* const message_group = new QGroupBox{ "Message", this };
		{
			content_text_edit = new QTextEdit{ message_group };
			content_text_edit->setReadOnly(true);

			QVBoxLayout* const message_group_layout = new QVBoxLayout{ message_group };
			message_group_layout->addWidget(content_text_edit);
		}

		layout->addWidget(message_group, 3);
	}

	for (std::uint32_t i = 0; i < value.record_count(); i++)
	{
		const IccMultiLocalizedUnicodeRecord record = value.get_record(i);
		const std::string lang_pair = std::format("{}-{}", record.lang, record.country);
		QListWidgetItem* const lang_pair_item = new QListWidgetItem{ QString::fromStdString(lang_pair) };
		lang_pair_item->setData(Qt::UserRole, QVariant{ i });
		lang_list_widget->addItem(lang_pair_item);
	}
}

void IccMultiLocalizedUnicodeTypeDetailsWidget::handle_lang_list_item_changed()
{
	QListWidgetItem* const selected_item = lang_list_widget->currentItem();
	const std::uint32_t index = static_cast<std::uint32_t>(selected_item->data(Qt::UserRole).toInt());
	const IccMultiLocalizedUnicodeRecord record = data.get_record(index);
	const std::vector<char16_t> string = data.get_string(record);
	static_assert(sizeof(ushort) == sizeof(std::uint16_t));
	const QString result = QString::fromUtf16(string.data(), string.size());
	content_text_edit->setText(result);
}
