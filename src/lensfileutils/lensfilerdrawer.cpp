#include "Logger.h"
#include "basics/Color.h"
#include "scene/camera/realistic/CameraLens.h"
#include "scene/camera/realistic/ExitPupilCalculator.h"
#include "scene/camera/realistic/LensSurface.h"
#include "scene/camera/realistic/Wavelengths.h"
#include "scene/camera/realistic/lensio/LensFileReaderFactory.h"
#include "utils/CraygMain.h"
#include <cairo-svg.h>
#include <iostream>

namespace crayg {

struct CameraLensRendererOptions {
    bool drawReferenceSphere;
    bool drawRays;
    bool drawChromaticRays;
};

class CameraLensRenderer {
  public:
    explicit CameraLensRenderer(CameraLens &cameraLens, const CameraLensRendererOptions &cameraLensRendererOptions)
        : cameraLens(cameraLens), cameraLensRendererOptions(cameraLensRendererOptions) {
    }

    std::string render() {
        // todo use stream instead
        std::string filename = "image.svg";

        auto surface = cairo_svg_surface_create(filename.c_str(), WIDTH, HEIGHT);
        auto cr = cairo_create(surface);

        cairo_scale(cr, SCALE, SCALE);
        cairo_translate(cr, WIDTH / SCALE - 2, HEIGHT / SCALE / 2);
        cairo_set_line_width(cr, SCALE / WIDTH);

        drawOpticalAxis(cr);
        drawFilmPlane(cr);

        for (auto &element : cameraLens.surfaces) {
            if (element.isAperture()) {
                drawAperture(cr, element);
                continue;
            }
            switch (element.geometry) {
                // todo support all supported geometrys
            case LensGeometry::SPHERICAL:
                drawSphericalLens(cr, element);
                break;

            case LensGeometry::ASPHERICAL:
                drawAsphericalLens(cr, element, cameraLens.asphericCoefficients[*element.asphericCoefficientsIndex]);
                break;
            }
        }

        drawRays(cr);

        cairo_show_page(cr);
        cairo_surface_flush(surface);
        cairo_surface_finish(surface);
        cairo_surface_destroy(surface);

        std::cout << "Wrote SVG file \"" << filename << "\"" << std::endl;

        return "";
    }

    void drawOpticalAxis(cairo_t *cr) const {

        cairo_move_to(cr, -WIDTH / SCALE, 0);
        cairo_line_to(cr, 0, 0);
        cairo_stroke(cr);
    }

    void drawFilmPlane(cairo_t *cr) const {
        const float filmHeight = 1.5f; // Arri Alexa 35 4.6K 16:9
        cairo_move_to(cr, 0, -filmHeight / 2);
        cairo_line_to(cr, 0, filmHeight / 2);
        cairo_stroke(cr);
    }

    void drawAperture(cairo_t *cr, const LensSurface &lensElement) const {
        cairo_move_to(cr, -cameraLens.getSurfaceCenter(lensElement), lensElement.apertureRadius);
        cairo_line_to(cr, -cameraLens.getSurfaceCenter(lensElement), lensElement.apertureRadius + 1.5);
        cairo_stroke(cr);

        cairo_move_to(cr, -cameraLens.getSurfaceCenter(lensElement), -lensElement.apertureRadius);
        cairo_line_to(cr, -cameraLens.getSurfaceCenter(lensElement), -lensElement.apertureRadius - 1.5);
        cairo_stroke(cr);
    }

    void drawSphericalLens(cairo_t *cr, const LensSurface &lensElement) {
        const float curvatureRadius = std::abs(lensElement.curvatureRadius);
        float alpha = std::asin((lensElement.apertureRadius * 2) / (2 * curvatureRadius));
        float start = -alpha;
        float end = alpha;
        float arcCenter = -cameraLens.getSurfaceCenter(lensElement) - curvatureRadius;
        if (lensElement.curvatureRadius > 0) {
            start = -alpha + M_PI;
            end = alpha + M_PI;
            arcCenter = -cameraLens.getSurfaceCenter(lensElement) + curvatureRadius;
        }
        cairo_arc(cr, arcCenter, 0, curvatureRadius, start, end);
        cairo_stroke(cr);
    }

    void drawAsphericalLens(cairo_t *cr, const LensSurface &lensElement,
                            const AsphericCoefficients &asphericCoefficients) {
        // todo properly implement this
        // todo handle convex / concave elements
        const int steps = 100;
        const float housingRadius = lensElement.apertureRadius;
        const float stepSize = housingRadius * 2.f / steps;
        float currentHeight = -housingRadius;
        for (int i = 0; i < steps; i++) {
            const float x =
                evaluateAsphericalSurface({0, currentHeight}, lensElement.curvatureRadius, asphericCoefficients);
            cairo_line_to(cr, -cameraLens.getSurfaceCenter(lensElement) + x, currentHeight);
            currentHeight += stepSize;
        }
        cairo_stroke(cr);
    }

    void drawRays(cairo_t *cr) {
        std::vector<std::pair<float, Color>> wavelengths;
        if (cameraLensRendererOptions.drawChromaticRays) {
            wavelengths.push_back({WavelengthsRgb::R, Color::createRed()});
            wavelengths.push_back({WavelengthsRgb::G, Color::createGreen()});
            wavelengths.push_back({WavelengthsRgb::B, Color::createBlue()});
        } else {
            wavelengths.emplace_back(FraunhoferLines::SODIUM.wavelength, Color::createBlack());
        }

        NullTaskReporter nullTaskReporter;
        ExitPupilCalculator exitPupilCalculator(cameraLens, 5, {}, nullTaskReporter);
        auto exitPupil = exitPupilCalculator.calculate();

        for (auto &wavelength : wavelengths) {
            cairo_set_source_rgba(cr, std::get<1>(wavelength).r, std::get<1>(wavelength).g, std::get<1>(wavelength).b,
                                  1);
            const int steps = 1;
            const float housingRadius = exitPupil.pupilBounds[0].getHeight() / 2 - 0.1f;
            const float stepSize = housingRadius * 2.f / steps;
            float currentHeight = -housingRadius;

            for (int step = 0; step <= steps; step++) {
                const auto pupilSample = exitPupil.samplePupil({0, 0}, 3.5);
                const auto pointOnPupil = Vector3f(0, currentHeight, cameraLens.getLastSurface().center);
                const Ray ray = {{0, 0, 0}, (pointOnPupil).normalize()};
                auto points = cameraLens.traceAndRecordFromFilmToWorld(ray, std::get<0>(wavelength));
                for (int i = 0; i < points.size(); i++) {
                    Vector3f &recordedPoint = points[i];
                    if (!i) {
                        cairo_move_to(cr, recordedPoint.z, recordedPoint.y);
                        continue;
                    }
                    cairo_line_to(cr, recordedPoint.z, recordedPoint.y);
                }
                cairo_stroke(cr);
                currentHeight += stepSize;
            }
        }
    }

  private:
    constexpr static const float WIDTH = 1600;
    constexpr static const float HEIGHT = 800;
    constexpr static const float SCALE = 80;

    CameraLens &cameraLens;
    CameraLensRendererOptions cameraLensRendererOptions;
};

int craygMain(int argc, char *argv[]) {

    // const std::string lensFilePath = "C:\\workspace\\crayg\\resources\\lensfiles\\EdmundOpticsAsphere.fx";
    const std::string lensFilePath = "C:\\workspace\\crayg\\resources\\lensfiles\\double-gauss-angenieux-50mm.fx";
    auto reader = LensFileReaderFactory::createLensFileReader(lensFilePath);
    auto cameraLens = std::make_unique<CameraLens>(reader->readFile(lensFilePath));
    cameraLens->focusLens(1000); // todo move elements during drawing
    // cameraLens->focusLens(cameraLens->metadata.closestFocalDistance+1);
    Logger::info("cameraLens->surfacesOffset {}", cameraLens->getSurfacesOffset());

    CameraLensRendererOptions cameraLensRendererOptions;
    cameraLensRendererOptions.drawChromaticRays = true;
    CameraLensRenderer cameraLensRenderer(*cameraLens, cameraLensRendererOptions);
    cameraLensRenderer.render();

    return 0;
}
}

int main(int argc, char *argv[]) {
    CRAYG_MAIN_IMPL;
}