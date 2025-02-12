#pragma once

#include <type_traits>

#include <QWidget>

namespace util
{
	template <class Base, class Derived>
	concept IsBaseOf = std::is_base_of<Base, Derived>::value;

    template <typename T>
	requires IsBaseOf<QWidget, T>
    T* present_application_modal_widget(T* const the_widget)
    {
		the_widget->setAttribute(Qt::WA_DeleteOnClose);
		the_widget->setWindowModality(Qt::ApplicationModal);
		the_widget->setWindowFlags(Qt::Window);

		the_widget->show();

		return the_widget;
    }
}
