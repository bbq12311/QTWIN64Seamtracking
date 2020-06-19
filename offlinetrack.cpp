#include "offlinetrack.h"
#include "ui_offlinetrack.h"

OfflineTrack::OfflineTrack(QWidget *parent) :
    QDockWidget(parent),
    uiOfflineTrack(new Ui::offlinetrack)
{
    uiOfflineTrack->setupUi(this);
}

OfflineTrack::~OfflineTrack()
{
    delete uiOfflineTrack;
}
