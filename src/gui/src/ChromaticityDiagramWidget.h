#pragma once

#include <memory>

#include <QImage>
#include <QLineF>
#include <QList>
#include <QObject>
#include <QWidget>

class XyChromaticity;

class ChromaticityDiagramWidget : public QWidget
{
	Q_OBJECT

public:
	ChromaticityDiagramWidget(QWidget* parent = nullptr);

	virtual QSize minimumSizeHint() const override;
	virtual QSize sizeHint() const override;

	void enable_rgb_gamut(bool enabled);
	void set_rgb_gamut(const XyChromaticity& r, const XyChromaticity& g, const XyChromaticity& b);

	void enable_white_point(bool enabled);
	void set_white_point(const XyChromaticity& wtpt);

protected:
	virtual void paintEvent(QPaintEvent* event) override;

	void repaint_final_image();

private:
	std::unique_ptr<QImage> background_image;
	std::unique_ptr<QImage> final_image;

	bool rgb_gamut_enabled = false;
	QList<QLineF> rgb_gamut_points;

	bool white_point_enabled = false;
	QList<QLineF> white_point_lines;

	bool requires_repaint = false;
};
