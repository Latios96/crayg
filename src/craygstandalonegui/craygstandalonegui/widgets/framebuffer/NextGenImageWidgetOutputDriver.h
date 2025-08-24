#pragma once
#include "NextGenImageWidget.h"
#include "outputdrivers/NextGenOutputDriver.h"

#include <unordered_set>

namespace crayg {

class NextGenImageWidgetOutputDriver : public QObject, public NextGenOutputDriver {
    Q_OBJECT
  public:
    explicit NextGenImageWidgetOutputDriver(NextGenImageWidget &nextGenImageWidget)
        : nextGenImageWidget(nextGenImageWidget) {
        connect(this, &NextGenImageWidgetOutputDriver::initialized, this,
                &NextGenImageWidgetOutputDriver::processInitialize);
        connect(this, &NextGenImageWidgetOutputDriver::tileStarted, this,
                &NextGenImageWidgetOutputDriver::processTileStarted);
        connect(this, &NextGenImageWidgetOutputDriver::allChannelsInTileUpdated, this,
                &NextGenImageWidgetOutputDriver::processAllChannelsInTileUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::channelInTileUpdated, this,
                &NextGenImageWidgetOutputDriver::processChannelInTileUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::tileFinished, this,
                &NextGenImageWidgetOutputDriver::processTileFinished);
        connect(this, &NextGenImageWidgetOutputDriver::allChannelsUpdated, this,
                &NextGenImageWidgetOutputDriver::processAllChannelsUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::channelUpdated, this,
                &NextGenImageWidgetOutputDriver::processChannelUpdated);
    }

    void initialize(const FilmSpec &filmSpec) override;
    void startTile(const Tile &tile) override;
    void updateAllChannelsInTile(const Tile &tile) override;
    void updateChannelInTile(const Tile &tile, const std::string &channelName) override;
    void finishTile(const Tile &tile) override;
    void updateAllChannels() override;
    void updateChannel(const std::string &channelName) override;
    void updateImageMetadata() override;

  signals:
    void initialized();
    void tileStarted(Tile tile);
    void allChannelsInTileUpdated(Tile tile);
    void channelInTileUpdated(Tile tile, std::string channelName);
    void tileFinished(Tile tile);
    void allChannelsUpdated();
    void channelUpdated(std::string channelName);
    void imageMetadataUpdated();

  public slots:
    void processInitialize();
    void processTileStarted(Tile tile);
    void processAllChannelsInTileUpdated(Tile tile);
    void processChannelInTileUpdated(Tile tile, std::string channelName);
    void processTileFinished(Tile tile);
    void processAllChannelsUpdated();
    void processChannelUpdated(std::string channelName);
    void processCurrentChannelChanged(std::string newChannel);

  private:
    std::string currentChannel = "color";
    void updateDisplayBuffer();
    void updateDisplayBuffer(const Tile &tile);
    NextGenImageWidget &nextGenImageWidget;
    std::unordered_set<Tile> activeTiles;
};

}