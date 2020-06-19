#ifndef OFFLINETRACK_H
#define OFFLINETRACK_H

#include <QDockWidget>

namespace Ui {
class offlinetrack;
}

class OfflineTrack : public QDockWidget
{
    Q_OBJECT

public:
    explicit OfflineTrack(QWidget *parent = nullptr);
    ~OfflineTrack();

private:
    Ui::offlinetrack *uiOfflineTrack;
};

#endif // OFFLINETRACK_H
