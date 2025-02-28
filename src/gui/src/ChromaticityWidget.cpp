#include "ChromaticityWidget.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <optional>
#include <vector>

#include <QColorSpace>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPointF>
#include <QSize>

#include "color/ColorConverter.h"
#include "color/RgbFloatColor.h"
#include "color/SpectralLocus.h"
#include "color/XyChromaticity.h"
#include "color/XyyFloatColor.h"
#include "color/XyzFloatColor.h"
#include "math/Triangle.h"
#include "math/Vector.h"

constexpr std::size_t CURVE_POINTS = 150;

constexpr int BITMAP_SIZE = 1024;

// Maps from a 1024x1024 space covering (0,0) to (1,1) to a shifted space where the shape is centered
// Some outputs will be outside the range (0, 1023) even for valid inputs
Vector<int, 2> xy_pixel_to_display_pixel(const int x, const int y)
{
	const int x2 = static_cast<int>(0.15 * BITMAP_SIZE) + x;
	const int y2 = static_cast<int>(0.90 * BITMAP_SIZE) - y;
	return Vector<int, 2>{ x2, y2 };
}

// Same as above but for floats in the range (0, 1)
Vector<float, 2> xy_to_display(const float x, const float y)
{
	const float x2 = 0.15 + x;
	const float y2 = 0.90 - y;
	return Vector<float, 2>{ x2, y2 };
}

static std::unique_ptr<QImage> generate_background(const int width, const int height)
{
	std::unique_ptr<QImage> result = std::make_unique<QImage>(width, height, QImage::Format_RGB888);
	result->setColorSpace(QColorSpace{ QColorSpace::SRgb });
	result->fill(Qt::gray);

	std::array<QPointF, CURVE_POINTS> draw_curve_points;
	std::array<XyChromaticity, CURVE_POINTS> curve_chroma;
	for (std::size_t i = 0; i < draw_curve_points.size(); i++)
	{
		const SpectralLocus spectral_locus;
		const float WAVELENGTH_MIN = spectral_locus.get_lo_bound();
		const float WAVELENGTH_MAX = spectral_locus.get_hi_bound();

		const double wavelength = WAVELENGTH_MIN + (WAVELENGTH_MAX - WAVELENGTH_MIN) * i / (CURVE_POINTS - 1.0);
		const std::optional<XyzFloatColor> opt_color = spectral_locus.color_from_wavelength(wavelength);
		if (opt_color)
		{
			const XyChromaticity chroma = ColorConverter::to_xy(*opt_color);
			curve_chroma[i] = chroma;
			draw_curve_points[i] = QPointF{ (chroma.x + 0.15) * BITMAP_SIZE, (0.9 - chroma.y) * BITMAP_SIZE };
		}
		else
		{
			return nullptr;
		}
	}

	std::vector<Triangle<double>> triangles;
	{
		std::size_t index_begin = 0;
		std::size_t index_end = curve_chroma.size() - 1;
		while (true)
		{
			const std::size_t remaining = index_end - index_begin;
			if (remaining == 0 || remaining == 1)
			{
				// The two indexed points are either neighbors or the same point
				// Either way, there is nothing left to triangulate
				break;
			}

			if (remaining > 2)
			{
				// Find the first and last two vertices, and create two triangles formed as a quad between them
				const XyChromaticity& c1 = curve_chroma[index_begin];
				const XyChromaticity& c2 = curve_chroma[index_begin + 1];
				const XyChromaticity& c3 = curve_chroma[index_end];
				const XyChromaticity& c4 = curve_chroma[index_end - 1];
				const Vector<double, 2> p1{ c1.x, c1.y };
				const Vector<double, 2> p2{ c2.x, c2.y };
				const Vector<double, 2> p3{ c3.x, c3.y };
				const Vector<double, 2> p4{ c4.x, c4.y };
				triangles.push_back(Triangle{ p1, p2, p3 });
				triangles.push_back(Triangle{ p3, p4, p2 });
			}
			else
			{
				// Only 3 points left, draw one triangle instead of two
				const XyChromaticity& c1 = curve_chroma[index_begin];
				const XyChromaticity& c2 = curve_chroma[index_begin + 1];
				const XyChromaticity& c3 = curve_chroma[index_end];
				const Vector<double, 2> p1{ c1.x, c1.y };
				const Vector<double, 2> p2{ c2.x, c2.y };
				const Vector<double, 2> p3{ c3.x, c3.y };
				triangles.push_back(Triangle{ p1, p2, p3 });
			}

			index_begin++;
			index_end--;
		}
	}

	for (int x = 0; x < BITMAP_SIZE; x++)
	{
		const double x_double = static_cast<double>(x) / (BITMAP_SIZE - 1);
		for (int y = 0; y < BITMAP_SIZE; y++)
		{
			const double y_double = static_cast<double>(y) / (BITMAP_SIZE - 1);
			const Vector<double, 2> pos{ x_double, y_double };

			for (const Triangle<double>& triangle : triangles)
			{
				if (triangle.contains(pos))
				{
					const Vector<int, 2> xy_pixel = xy_pixel_to_display_pixel(x, y);
					const XyChromaticity chroma{ x_double, y_double };
					const XyyFloatColor color_xyy = ColorConverter::to_xyy(chroma);
					const XyzFloatColor color_xyz = ColorConverter::to_xyz(color_xyy);
					const RgbFloatColor color_rgb = ColorConverter::to_srgb(color_xyz, true);
					result->setPixelColor(xy_pixel.x(), xy_pixel.y(), QColor::fromRgb(color_rgb.r_byte(), color_rgb.g_byte(), color_rgb.b_byte()));
					break;
				}
			}
		}
	}

	QPen edge_pen;
	edge_pen.setColor(Qt::black);
	edge_pen.setWidth(5);

	QPainter painter{ result.get() };
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(edge_pen);
	painter.drawPolygon(draw_curve_points.data(), static_cast<int>(draw_curve_points.size()));

	return std::move(result);
}

ChromaticityWidget::ChromaticityWidget(QWidget* const parent) : QWidget{ parent }
{
	background_image = generate_background(BITMAP_SIZE, BITMAP_SIZE);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QSize ChromaticityWidget::minimumSizeHint() const
{
	return QSize{ 256, 256 };
}

QSize ChromaticityWidget::sizeHint() const
{
	return QSize{ 512, 512 };
}

void ChromaticityWidget::set_rgb_gamut(const XyChromaticity& r, const XyChromaticity& g, const XyChromaticity& b)
{
	const Vector<float, 2> r_vec = xy_to_display(r.x, r.y) * BITMAP_SIZE;
	const Vector<float, 2> g_vec = xy_to_display(g.x, g.y) * BITMAP_SIZE;
	const Vector<float, 2> b_vec = xy_to_display(b.x, b.y) * BITMAP_SIZE;

	const QPointF r_point{ r_vec.x(), r_vec.y() };
	const QPointF g_point{ g_vec.x(), g_vec.y() };
	const QPointF b_point{ b_vec.x(), b_vec.y() };

	rgb_gamut_points.clear();
	rgb_gamut_points.push_back(QLineF{ r_point, g_point });
	rgb_gamut_points.push_back(QLineF{ g_point, b_point });
	rgb_gamut_points.push_back(QLineF{ r_point, b_point });

	requires_repaint = true;
}

void ChromaticityWidget::paintEvent(QPaintEvent* event)
{
	if (requires_repaint)
	{
		repaint_final_image();
	}
	const auto render_image = [this](const QImage& image)
	{
		const QSize full_size = size();
		const int side_length = std::min(full_size.width(), full_size.height());
		int x_offset = 0;
		int y_offset = 0;
		if (full_size.width() > full_size.height())
		{
			x_offset = (full_size.width() - full_size.height()) / 2;
		}
		if (full_size.height() > full_size.width())
		{
			y_offset = (full_size.height() - full_size.width()) / 2;
		}
		QPainter painter{ this };
		painter.setRenderHint(QPainter::SmoothPixmapTransform);
		const QRect draw_rect{ x_offset, y_offset, side_length, side_length };
		painter.drawImage(draw_rect, image);
	};

	if (final_image)
	{
		render_image(*final_image);
	}
	else if (background_image)
	{
		render_image(*background_image);
	}
}

void ChromaticityWidget::repaint_final_image()
{
	final_image = std::make_unique<QImage>(*background_image);

	QPainter painter{ final_image.get() };
	painter.setRenderHint(QPainter::Antialiasing);

	QPen gamut_border_pen;
	gamut_border_pen.setColor(Qt::black);
	gamut_border_pen.setWidth(3);

	painter.setPen(gamut_border_pen);
	painter.drawLines(rgb_gamut_points);
}
