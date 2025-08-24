#include "NextGenImageWidgetOutputDriver.h"

#include "FrameBufferDrawUtils.h"
#include "crayg/foundation/areaiterators/AreaIterators.h"
#include "image/ColorConversion.h"
#include "utils/StopWatch.h"

namespace crayg {

void NextGenImageWidgetOutputDriver::initialize(const FilmSpec &filmSpec) {
    NextGenOutputDriver::initialize(filmSpec);
    emit initialized();
}

void NextGenImageWidgetOutputDriver::startTile(const Tile &tile) {
    NextGenOutputDriver::startTile(tile);
    emit tileStarted(tile);
}

void NextGenImageWidgetOutputDriver::updateAllChannelsInTile(const Tile &tile) {
    NextGenOutputDriver::updateAllChannelsInTile(tile);
    emit allChannelsInTileUpdated(tile);
}

void NextGenImageWidgetOutputDriver::updateChannelInTile(const Tile &tile, const std::string &channelName) {
    NextGenOutputDriver::updateChannelInTile(tile, channelName);
    emit channelInTileUpdated(tile, channelName);
}

void NextGenImageWidgetOutputDriver::finishTile(const Tile &tile) {
    NextGenOutputDriver::finishTile(tile);
    emit tileFinished(tile);
}

void NextGenImageWidgetOutputDriver::updateAllChannels() {
    NextGenOutputDriver::updateAllChannels();
    emit allChannelsUpdated();
}

void NextGenImageWidgetOutputDriver::updateChannel(const std::string &channelName) {
    NextGenOutputDriver::updateChannel(channelName);
    emit channelUpdated(channelName);
}

void NextGenImageWidgetOutputDriver::updateImageMetadata() {
    emit imageMetadataUpdated();
}

void NextGenImageWidgetOutputDriver::processInitialize() {
    nextGenImageWidget.initBuffer(film->getFilmSpec().resolution);
}

void NextGenImageWidgetOutputDriver::processTileStarted(Tile imageTile) {
    activeTiles.insert(imageTile);
    FrameBufferDrawUtils::drawTile(nextGenImageWidget.displayBuffer, imageTile);
    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(nextGenImageWidget.displayBuffer,
                                                     film->getFilmSpec().regionToRender);
    nextGenImageWidget.update();
}

void NextGenImageWidgetOutputDriver::processAllChannelsInTileUpdated(Tile imageTile) {
    updateDisplayBuffer(imageTile);
}

void NextGenImageWidgetOutputDriver::processChannelInTileUpdated(Tile imageTile, std::string channelName) {
    if (channelName != currentChannel) {
        return;
    }
    updateDisplayBuffer(imageTile);
}

void NextGenImageWidgetOutputDriver::processTileFinished(Tile imageTile) {
    activeTiles.erase(imageTile);
    updateDisplayBuffer(imageTile);
}

void NextGenImageWidgetOutputDriver::processAllChannelsUpdated() {
    updateDisplayBuffer();
}

void NextGenImageWidgetOutputDriver::processChannelUpdated(std::string channelName) {
    if (channelName != currentChannel) {
        return;
    }
    updateDisplayBuffer();
}

void NextGenImageWidgetOutputDriver::processCurrentChannelChanged(std::string newChannel) {
    currentChannel = newChannel;
    updateDisplayBuffer();
}

void NextGenImageWidgetOutputDriver::updateDisplayBuffer() {
    Resolution filmResolution = film->getFilmSpec().resolution;
    updateDisplayBuffer(Tile({0, 0}, filmResolution.getWidth(), filmResolution.getHeight()));
}

void NextGenImageWidgetOutputDriver::updateDisplayBuffer(const Tile &imageTile) {
    auto bufferVariantPtr = film->getBufferVariantPtrByName(currentChannel);
    if (!bufferVariantPtr) {
        return;
    }

    std::visit(
        [&imageTile, this](auto buf) {
            for (auto pixel : AreaIterators::scanlines(imageTile)) {
                const Vector2i globalPosition = pixel + imageTile.getPosition();
                Color color = buf->getColor(globalPosition);
                if (ColorConversion::channelNeedsLinearToSRgbConversion(currentChannel)) {
                    color = ColorConversion::linearToSRGB(color);
                }
                const auto rgbValues = color.getRgbValues();
                nextGenImageWidget.displayBuffer.setPixelColor(
                    globalPosition.x, globalPosition.y,
                    QColor::fromRgb(std::get<0>(rgbValues), std::get<1>(rgbValues), std::get<2>(rgbValues)));
            }
        },
        *bufferVariantPtr);

    for (auto &tile : activeTiles) {
        FrameBufferDrawUtils::drawTile(nextGenImageWidget.displayBuffer, tile);
    }
    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(nextGenImageWidget.displayBuffer,
                                                     film->getFilmSpec().regionToRender);
    nextGenImageWidget.update();
}

}