#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ar_projects");
    QCoreApplication::setApplicationName("StopNotebook");

    MainWindow w;
    w.show();

    return a.exec();
}

/**
  předloha umožňuje nastavit čas práce, nastavit čas přestávky, vybrat zvuk, změnit barvu záhlaví, zakázat změny nastavení (celkově nebo pokud se blíží čas přestávky)

  a) ok - volitelný čas práce 0 - xx minut
  b) ok - volitelný čas přestávky
  c) ok - schovat do tray baru, obnovit z traybaru
  d)      about (version info, author name, home page, ect)
  e) ok - kontext menu na pravé kliknutí (možnost Really Exit, add 5 minutes, open)
  w) ok - saving data in QSettings
  h)      update over internet (check at least)
  i) ok - tolerance - např. stisknutí klávesy nezastaví cooldown (zastaví, pokud není nucená pauza)
  j)      okénko pro test reporty a feedback over internet a donate (paypal, bitcoin, ...)
  k)      hezčí a nativní grafika (a udělat něco s tím zvětšením aplikace, např. lépe navázat na sebe prvky nebo to rovnou zakázat)
  m) ok - run at startup checkbox
  o)      event driven
  p)      sound signalisation (on rest time, on the start of work period)
  q)      united graphics
  r)      little numbers of times?
  q) in - menu
  u)      better name
  v) ok - always on top
  y)      info about running in tray system
  z)      write unit tests

  aa)     versioning - http://www.openguru.com/2009/11/qt-best-way-to-set-application-version.html
  ab)     neprodávat to za $25
  ac)     nezaměřovat to přímo na RSI, ale jsou i jiné problémy (např. protáhnout si nohy, zakroutit hlavou => vybízí to k sepsání několika tipů (nechtěl jsem napsat něco jiného?))
  ad)     grafy - grafy čeho? Využití myši, pravé nebo levé klávesnice? Není to zbytečně složité? Nebude to děsit uživatele? Statistika (pocet period)
  ae)     translations
  af)     měření celkového času u počítače? Měřit počet period? Do kdy? Resetovat na požádání? Na úspání počítače?
  */

// http://doc.qt.io/qt-5/qtwidgets-desktop-systray-example.html
// http://doc.qt.io/qt-4.8/activeqt-dotnet.html
// http://doc.qt.io/qt-5/activeqt-index.html
