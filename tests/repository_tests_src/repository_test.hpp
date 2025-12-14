#pragma once
#include <QObject>
#include <QSignalSpy>

class RepositoryTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    
    void testConstructor();
    void testIsMetric();
    void testSetApiKey();
    void testSetCityName();
    void testSignals();

    void cleanup();
    void cleanupTestCase();

private:
    QString createValidApiKey() const;
    QString createValidCityName() const;
};