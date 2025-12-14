#include <QTest>
#include <QSignalSpy>
#include "weather_model_test.hpp"
#include "src/data/model/weather_model.hpp"

void WeatherModelTest::initTestCase() { }

void WeatherModelTest::init() { }

void WeatherModelTest::testDefaultModel() {
    WeatherModel model;
    
    QCOMPARE(model.getTemperature(), 0.0);
    QCOMPARE(model.getDescription(), QString(""));
    QCOMPARE(model.getWindSpeed(), 0.0);
    QCOMPARE(model.getPressure(), 0.0);
    QCOMPARE(model.getCityName(), QString(""));
}

void WeatherModelTest::testSettersAndGetters() {
    WeatherModel model;
    
    // Тестируем температуру
    model.setTemperature(25.5);
    QCOMPARE(model.getTemperature(), 25.5);
    
    model.setTemperature(-10.0);
    QCOMPARE(model.getTemperature(), -10.0);
    
    // Тестируем описание
    model.setDescription("Clear sky");
    QCOMPARE(model.getDescription(), QString("Clear sky"));
    
    // Тестируем скорость ветра
    model.setWindSpeed(15.3);
    QCOMPARE(model.getWindSpeed(), 15.3);
    
    // Тестируем давление
    model.setPressure(1013.25);
    QCOMPARE(model.getPressure(), 1013.25);
    
    // Тестируем город
    model.setCityName("Moscow");
    QCOMPARE(model.getCityName(), QString("Moscow"));
}

void WeatherModelTest::cleanup() { }

void WeatherModelTest::cleanupTestCase() { }