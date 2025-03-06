#include "IccXyzTypeDetailsWidget.h"

#include <cstdlib>

#include <QAbstractItemView>
#include <QHeaderView>
#include <QList>
#include <QString>
#include <QTableWidget>
#include <QVBoxLayout>

#include "icctypes/IccXyzNumber.h"

IccXyzTypeDetailsWidget::IccXyzTypeDetailsWidget(const IccXyzType& value, QWidget* const parent) :
	QWidget{ parent }
{
	QTableWidget* const table_widget = new QTableWidget{ this };
	table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table_widget->setSelectionBehavior(QAbstractItemView::SelectRows);
	table_widget->setSelectionMode(QAbstractItemView::SingleSelection);
	table_widget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table_widget->horizontalHeader()->setStretchLastSection(true);
	table_widget->verticalHeader()->setVisible(false);
	table_widget->setColumnCount(5);
	table_widget->setRowCount(static_cast<int>(value.get_xyz_number_count()));
	table_widget->setHorizontalHeaderLabels({ "Index", "X", "Y", "Z", "" });

	for (std::size_t i = 0; i < value.get_xyz_number_count(); i++)
	{
		const IccXyzNumber xyz_number = value.get_xyz_number(i);
		table_widget->setItem(static_cast<int>(i), 0, new QTableWidgetItem{ QString::number(i) });
		table_widget->setItem(static_cast<int>(i), 1, new QTableWidgetItem{ QString::number(xyz_number.x()) });
		table_widget->setItem(static_cast<int>(i), 2, new QTableWidgetItem{ QString::number(xyz_number.y()) });
		table_widget->setItem(static_cast<int>(i), 3, new QTableWidgetItem{ QString::number(xyz_number.z()) });
	}

	QVBoxLayout* const layout = new QVBoxLayout{ this };
	layout->addWidget(table_widget);
}
