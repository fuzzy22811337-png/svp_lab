#include <QTest>
#include <QSignalSpy>
#include "weather_model_test.hpp"
#include "src/data/model/weather_model.hpp"

void WeatherModelTest::initTestCase() {
}

void WeatherModelTest::init() {
    // Инициализация перед каждым тестом
}

void WeatherModelTest::testDefaultConstructor() {
    WeatherModel model;
    
    QCOMPARE(model.getTemperature(), 0.0);
    QCOMPARE(model.getDescription(), QString(""));
    QCOMPARE(model.getWindSpeed(), 0.0);
    QCOMPARE(model.getPressure(), 0.0);
    QCOMPARE(model.getCityName(), QString(""));
    QCOMPARE(model.getIconCode(), QString(""));
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
    
    // Тестируем иконку
    model.setIconCode("01d");
    QCOMPARE(model.getIconCode(), QString("01d"));
}

void WeatherModelTest::testMultipleValues() {
    WeatherModel model;
    
    model.setTemperature(-5.5);
    model.setDescription("Snow");
    model.setWindSpeed(10.5);
    model.setPressure(980.0);
    model.setCityName("New York");
    model.setIconCode("13d");
    
    QCOMPARE(model.getTemperature(), -5.5);
    QCOMPARE(model.getDescription(), QString("Snow"));
    QCOMPARE(model.getWindSpeed(), 10.5);
    QCOMPARE(model.getPressure(), 980.0);
    QCOMPARE(model.getCityName(), QString("New York"));
    QCOMPARE(model.getIconCode(), QString("13d"));
}

void WeatherModelTest::testCopyValues() {
    WeatherModel model1;
    model1.setTemperature(20.0);
    model1.setCityName("London");
    
    // Создаем второй объект и копируем значения через сеттеры
    WeatherModel model2;
    model2.setTemperature(model1.getTemperature());
    model2.setCityName(model1.getCityName());
    
    QCOMPARE(model2.getTemperature(), model1.getTemperature());
    QCOMPARE(model2.getCityName(), model1.getCityName());
}

void WeatherModelTest::cleanup() {
    // Очистка после каждого теста
}

void WeatherModelTest::cleanupTestCase() {
}