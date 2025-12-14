#pragma once
#include <QObject>

class WeatherModelTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    
    void testDefaultModel();
    void testSettersAndGetters();
    
    void cleanup();
    void cleanupTestCase();
};