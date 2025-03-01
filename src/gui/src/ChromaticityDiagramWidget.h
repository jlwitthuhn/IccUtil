#pragma once

#include <memory>

#include <QLineF>
#include <QList>
#include <QObject>
#include <QWidget>

class QImage;
class QPaintEvent;
class QSize;

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

protected:
	virtual void paintEvent(QPaintEvent* event) override;

	void repaint_final_image();

private:
	std::unique_ptr<QImage> background_image;
	std::unique_ptr<QImage> final_image;

	bool rgb_gamut_enabled = false;
	QList<QLineF> rgb_gamut_points;

	bool requires_repaint = false;
};
