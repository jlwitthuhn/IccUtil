#include "ChromaticityTopWidget.h"

#include <Qt> // for QCheckState
#include <QCheckBox>
#include <QToolBar>
#include <QVBoxLayout>

#include "color/ColorConverter.h"
#include "color/XyChromaticity.h"
#include "color/XyzFloatColor.h"
#include "core/ExitAssert.h"
#include "icc/IccFileBody.h"
#include "icc/IccProfile.h"
#include "icctypes/IccXyzNumber.h"
#include "icctypes/IccXyzType.h"

#include "ChromaticityDiagramWidget.h"

ChromaticityTopWidget::ChromaticityTopWidget(QWidget* parent) : QWidget(parent)
{
	setWindowTitle("Chromaticity");
	QVBoxLayout* const layout = new QVBoxLayout{ this };
	layout->setContentsMargins(0, 0, 0, 0);

	{
		QToolBar* const toolbar = new QToolBar{ this };

		rgb_gamut_check = new QCheckBox{ "Display profile gamut", toolbar };
		rgb_gamut_check->setEnabled(false);
		connect(rgb_gamut_check, &QCheckBox::checkStateChanged, this, &ChromaticityTopWidget::display_options_changed);
		toolbar->addWidget(rgb_gamut_check);

		white_point_check = new QCheckBox{ "Display white point", toolbar };
		white_point_check->setEnabled(false);
		connect(white_point_check, &QCheckBox::checkStateChanged, this, &ChromaticityTopWidget::display_options_changed);
		toolbar->addWidget(white_point_check);

		layout->addWidget(toolbar);
	}

	chroma_widget = new ChromaticityDiagramWidget{ this };
	layout->addWidget(chroma_widget);

	display_options_changed();
}

void ChromaticityTopWidget::set_icc_profile(const IccProfile& profile)
{
	std::optional<XyChromaticity> r_xy;
	std::optional<XyChromaticity> g_xy;
	std::optional<XyChromaticity> b_xy;
	std::optional<XyChromaticity> wtpt_xy;
	for (std::uint32_t i = 0; i < profile.get_body().get_tag_count(); i++)
	{
		const IccFileTagEntry entry = profile.get_body().get_tag(i);
		const std::array<char, 4>  sig_array = entry.get_signature();
		const std::string sig{ sig_array.begin(), sig_array.end() };
		if (sig == "rXYZ")
		{
			const std::span<const char> tag_bytes = profile.get_body().get_tag_bytes(i);
			if (IccXyzType::is_valid(tag_bytes) == false)
			{
				break;
			}
			const IccXyzType icc_xyz_type{ tag_bytes };
			if (icc_xyz_type.get_xyz_number_count() != 1)
			{
				break;
			}
			const IccXyzNumber icc_xyz = icc_xyz_type.get_xyz_number(0);
			const XyzFloatColor xyz_color{
				static_cast<float>(icc_xyz.x()),
				static_cast<float>(icc_xyz.y()),
				static_cast<float>(icc_xyz.z())
			};
			r_xy = ColorConverter::to_xy(xyz_color);
		}
		else if (sig == "gXYZ")
		{
			const std::span<const char> tag_bytes = profile.get_body().get_tag_bytes(i);
			if (IccXyzType::is_valid(tag_bytes) == false)
			{
				break;
			}
			const IccXyzType icc_xyz_type{ tag_bytes };
			if (icc_xyz_type.get_xyz_number_count() != 1)
			{
				break;
			}
			const IccXyzNumber icc_xyz = icc_xyz_type.get_xyz_number(0);
			const XyzFloatColor xyz_color{
				static_cast<float>(icc_xyz.x()),
				static_cast<float>(icc_xyz.y()),
				static_cast<float>(icc_xyz.z())
			};
			g_xy = ColorConverter::to_xy(xyz_color);
		}
		else if (sig == "bXYZ")
		{
			const std::span<const char> tag_bytes = profile.get_body().get_tag_bytes(i);
			if (IccXyzType::is_valid(tag_bytes) == false)
			{
				break;
			}
			const IccXyzType icc_xyz_type{ tag_bytes };
			if (icc_xyz_type.get_xyz_number_count() != 1)
			{
				break;
			}
			const IccXyzNumber icc_xyz = icc_xyz_type.get_xyz_number(0);
			const XyzFloatColor xyz_color{
				static_cast<float>(icc_xyz.x()),
				static_cast<float>(icc_xyz.y()),
				static_cast<float>(icc_xyz.z())
			};
			b_xy = ColorConverter::to_xy(xyz_color);
		}
		else if (sig == "wtpt")
		{
			const std::span<const char> tag_bytes = profile.get_body().get_tag_bytes(i);
			if (IccXyzType::is_valid(tag_bytes) == false)
			{
				break;
			}
			const IccXyzType icc_xyz_type{ tag_bytes };
			if (icc_xyz_type.get_xyz_number_count() != 1)
			{
				break;
			}
			const IccXyzNumber icc_xyz = icc_xyz_type.get_xyz_number(0);
			const XyzFloatColor xyz_color{
				static_cast<float>(icc_xyz.x()),
				static_cast<float>(icc_xyz.y()),
				static_cast<float>(icc_xyz.z())
			};
			wtpt_xy = ColorConverter::to_xy(xyz_color);
		}
	}
	if (r_xy && g_xy && b_xy)
	{
		chroma_widget->set_rgb_gamut(*r_xy, *g_xy, *b_xy);
		rgb_gamut_check->setEnabled(true);
		rgb_gamut_check->setChecked(true);
	}
	if (wtpt_xy)
	{
		chroma_widget->set_white_point(*wtpt_xy);
		white_point_check->setEnabled(true);
		white_point_check->setChecked(true);
	}
	display_options_changed();
}

void ChromaticityTopWidget::display_options_changed()
{
	const Qt::CheckState gamut_state = rgb_gamut_check->checkState();
	chroma_widget->enable_rgb_gamut(gamut_state == Qt::Checked);
	const Qt::CheckState wtpt_state = white_point_check->checkState();
	chroma_widget->enable_white_point(wtpt_state == Qt::Checked);
}
