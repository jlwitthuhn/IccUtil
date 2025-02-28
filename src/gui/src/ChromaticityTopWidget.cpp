#include "ChromaticityTopWidget.h"

#include <Qt> // for QCheckState
#include <QCheckBox>
#include <QToolBar>
#include <QVBoxLayout>

#include "core/ExitAssert.h"

#include "ChromaticityDiagramWidget.h"

ChromaticityTopWidget::ChromaticityTopWidget(QWidget* parent) : QWidget(parent)
{
	QVBoxLayout* const layout = new QVBoxLayout{ this };
	layout->setContentsMargins(0, 0, 0, 0);

	{
		QToolBar* const toolbar = new QToolBar{ this };

		rgb_gamut_check = new QCheckBox{ "Display profile gamut", toolbar};
		rgb_gamut_check->setEnabled(false);
		connect(rgb_gamut_check, &QCheckBox::checkStateChanged, this, &ChromaticityTopWidget::display_gamut_check_state_changed);

		toolbar->addWidget(rgb_gamut_check);

		layout->addWidget(toolbar);
	}

	chroma_widget = new ChromaticityDiagramWidget{ this };
	layout->addWidget(chroma_widget);
}

void ChromaticityTopWidget::set_rgb_gamut(const XyChromaticity& r, const XyChromaticity& g, const XyChromaticity& b)
{
	EXIT_ASSERT(chroma_widget != nullptr, "Chromaticity widget must exist when setting gamut");
	EXIT_ASSERT(rgb_gamut_check != nullptr, "RGB gamut checkbox must exist when setting gamut");
	chroma_widget->set_rgb_gamut(r, g, b);
	rgb_gamut_check->setEnabled(true);
	rgb_gamut_check->setChecked(true);
}

void ChromaticityTopWidget::display_gamut_check_state_changed()
{
	const Qt::CheckState state = rgb_gamut_check->checkState();
	chroma_widget->enable_rgb_gamut(state == Qt::Checked);
}