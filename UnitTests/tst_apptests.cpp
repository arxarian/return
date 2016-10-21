#include <QString>
#include <QtTest>

class AppTests : public QObject
{
    Q_OBJECT

public:
    AppTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void FirstTestCase();
};

AppTests::AppTests()
{
}

void AppTests::initTestCase()
{
}

void AppTests::cleanupTestCase()
{
}

void AppTests::FirstTestCase()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(AppTests)

#include "tst_apptests.moc"
