#pragma once
#include <QObject>
#include <QSignalSpy>

class WeatherDataSourceTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    
    void testConstructor();
    void testApiKeyValidation();
    void testCityNameValidation();
    void testUnitsChange();
    void testSameValues();
    
    void cleanup();
    void cleanupTestCase();

private:
    QString createValidApiKey() const;
    QString createValidCityName() const;
};