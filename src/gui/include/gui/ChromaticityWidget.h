#pragma once

#include <memory>

#include <QObject>
#include <QWidget>

class QImage;
class QPaintEvent;
class QSize;

class ChromaticityWidget : public QWidget
{
	Q_OBJECT

public:
	ChromaticityWidget(QWidget* parent = nullptr);

	virtual QSize minimumSizeHint() const override;
	virtual QSize sizeHint() const override;

protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	std::unique_ptr<QImage> background_image;
};
