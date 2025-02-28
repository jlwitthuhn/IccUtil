#pragma once

#include <QObject>
#include <QWidget>

class QCheckBox;

class XyChromaticity;

class ChromaticityDiagramWidget;

class ChromaticityTopWidget : public QWidget
{
	Q_OBJECT

public:
	ChromaticityTopWidget(QWidget* parent = nullptr);

	void set_rgb_gamut(const XyChromaticity& r, const XyChromaticity& g, const XyChromaticity& b);

private:
	void display_gamut_check_state_changed();

	QCheckBox* rgb_gamut_check = nullptr;
	ChromaticityDiagramWidget* chroma_widget = nullptr;
};
