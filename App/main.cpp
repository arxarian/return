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
  e) ok - kontext menu na pravé kliknutí (možnost Really Exit, add 5 minutes, open)
  w) ok - saving data in QSettings
  h)      update over internet
  i) ok - tolerance - např. stisknutí klávesy nezastaví cooldown (zastaví, pokud není nucená pauza)
  j)      okénko pro test reporty a feedback over internet a donate (paypal, bitcoin, ...)
  k)      hezčí a nativní grafika
  m)      run at startup checkbox - http://stackoverflow.com/questions/9534415/run-application-on-startup (C:\Users\hubnerp\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup)
  o)      event driven
  p)      sound signalisation (on rest time, on the start of work period)
  q)      united graphics
  r)      little numbers of times?
  q) in - menu
  u)      better name
  v) ok - always on top
  x)      bug in tolerance setting (it counts plus one, does it still?)
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
