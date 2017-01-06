#include "programupdatergithub.h"

ProgramUpdaterGithub::ProgramUpdaterGithub(QObject *parent) : ProgramUpdater("https://api.github.com/repos/hubnerp/return/releases/latest", parent)
{
    //
}

void ProgramUpdaterGithub::UpdateProgram()
{
    // TODO - move the dialog part to GUI
    // if there is a newer version, ask the user if he wants to update
    //  display a dialog with new version number and question: "do you want to download new version" and yes or no buttons
    //  if user clicks yes, open broswer with download url
    //   get download url from program updater (or url can be obtain as argument of function which displayes dialog)
    //  if user clicks no, do nothing

    // if there is no new version, do nothing
}

void ProgramUpdaterGithub::ExtractLatestVersionInfo(const QByteArray &arrUrlContent)
{
    QJsonDocument oJsonDoc = QJsonDocument::fromJson(arrUrlContent);
    if(!oJsonDoc.isNull())
    {
        if(oJsonDoc.isObject())
        {
            QJsonObject oJsonObject = oJsonDoc.object();
            SetLatestVersion(oJsonObject["tag_name"].toString());
        }
        else
        {
            qDebug() << "not an object";
        }
    }
    else
    {
        qDebug() << "invalid json";
    }
}
