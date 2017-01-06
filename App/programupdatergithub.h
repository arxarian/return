#ifndef PROGRAMUPDATERGITHUB_H
#define PROGRAMUPDATERGITHUB_H

#include <QObject>

#include "programupdater.h"

class ProgramUpdaterGithub : public ProgramUpdater
{
    Q_OBJECT

public:
    explicit ProgramUpdaterGithub(QObject *parent = 0);
    void UpdateProgram();

    // ProgramUpdater interface
private slots:
    void ExtractLatestVersionInfo(const QByteArray &arrUrlContent) override;
};

#endif // PROGRAMUPDATERGITHUB_H
