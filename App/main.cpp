#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("ar_projects");
    QCoreApplication::setApplicationName("StopNotebook");

    Widget w;
    w.show();

    return a.exec();
}

/**
  předloha umožňuje nastavit čas práce, nastavit čas přestávky, vybrat zvuk, změnit barvu záhlaví, zakázat změny nastavení (celkově nebo pokud se blíží čas přestávky)

  a) ok - volitelný čas práce 0 - xx minut
  b) ok - volitelný čas přestávky
  c) ok - schovat do tray baru, obnovit z traybaru
  d)      neprodávat to za $25
  e) in - kontext menu na pravé kliknutí (možnost Really Exit, add 5 minutes, open)
  f)      nezaměřovat to přímo na RSI, ale jsou i jiné problémy (např. protáhnout si nohy, zakroutit hlavou => vybízí to k sepsání několika tipů (nechtěl jsem napsat něco jiného?))
  g)      grafy - grafy čeho? Využití myši, pravé nebo levé klávesnice? Není to zbytečně složité? Nebude to děsit uživatele?
  h)      update over internet
  i) ok - tolerance - např. stisknutí klávesy nezastaví cooldown (zastaví, pokud není nucená pauza)
          -pokud je idle pod toleranci, idle se neustále resetuje. Je to dobře? Definovat?
  j)      okénko pro test reporty a feedback over internet a donate (paypal, bitcoin, ...)
  k)      hezčí a nativní grafika
  l)      měření celkového času u počítače? Měřit počet period? Do kdy? Resetovat na požádání? Na úspání počítače?
  m)      run at startup checkbox - http://stackoverflow.com/questions/9534415/run-application-on-startup (C:\Users\hubnerp\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup)
  n)      translations
  o)      event driven
  p)      sound signalisation
  q)      united graphics
  r)      little numbers of times?
  q)      menu
  u)      better name
  v)      always on top
  w) ok - saving data in QSettings
  x)      bug in tolerance setting (it counts plus one)
  y)      info about running in tray system
  w)      resetuje se bez pipani pri prekroceni worktime
  */

// http://doc.qt.io/qt-5/qtwidgets-desktop-systray-example.html
// http://doc.qt.io/qt-4.8/activeqt-dotnet.html
// http://doc.qt.io/qt-5/activeqt-index.html
