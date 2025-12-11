#pragma once
#include <QObject>

class WeatherModelTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void init();
    
    void testDefaultConstructor();
    void testSettersAndGetters();
    void testMultipleValues();
    void testCopyValues();
    
    void cleanup();
    void cleanupTestCase();
};