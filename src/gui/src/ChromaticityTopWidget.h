#pragma once

#include <QObject>
#include <QWidget>

class QCheckBox;

class IccProfile;
class XyChromaticity;

class ChromaticityDiagramWidget;

class ChromaticityTopWidget : public QWidget
{
	Q_OBJECT

public:
	ChromaticityTopWidget(QWidget* parent = nullptr);

	void set_icc_profile(const IccProfile& profile);

private:
	void display_options_changed();

	QCheckBox* rgb_gamut_check = nullptr;
	QCheckBox* white_point_check = nullptr;
	ChromaticityDiagramWidget* chroma_widget = nullptr;
};
