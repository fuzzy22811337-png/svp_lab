#include <QTest>
#include <QSignalSpy>
#include "weather_data_test.hpp"
#include "src/data/datasource/weather_data_source.hpp"

void WeatherDataSourceTest::initTestCase() { }

void WeatherDataSourceTest::init() { }

QString WeatherDataSourceTest::createValidApiKey() const {
    //рандомный набор
    return "abc123def456ghi789jkl012mno345pqr678stu901";
}

QString WeatherDataSourceTest::createValidCityName() const {
    return "Moscow";
}

void WeatherDataSourceTest::testApiKeyValidation() {
    WeatherDataSource dataSource;
    QSignalSpy keyErrorSpy(&dataSource, &WeatherDataSource::keyErrorOccurred);
    QSignalSpy keyValidSpy(&dataSource, &WeatherDataSource::keyValidationPassed);
    
    // Тест 1: Пустой ключ
    dataSource.setApiKey("");
    QCOMPARE(keyErrorSpy.count(), 1);
    
    // Тест 2: Валидный ключ
    QString validKey = createValidApiKey();
    dataSource.setApiKey(validKey);
    QCOMPARE(keyValidSpy.count(), 1);
    
    // Тест 3: Ключ с недопустимыми символами
    dataSource.setApiKey("invalid-key!");
    QCOMPARE(keyErrorSpy.count(), 2);
    
    // Тест 4: Слишком длинный ключ
    QString longKey = QString(200, 'a');
    dataSource.setApiKey(longKey);
    QCOMPARE(keyErrorSpy.count(), 3);
}

void WeatherDataSourceTest::testCityNameValidation() {
    WeatherDataSource dataSource;
    QSignalSpy cityErrorSpy(&dataSource, &WeatherDataSource::cityErrorOccurred);
    QSignalSpy cityValidSpy(&dataSource, &WeatherDataSource::cityValidationPassed);
    
    // Тест 1: Пустой город
    dataSource.setCityName("");
    QCOMPARE(cityErrorSpy.count(), 1);
    
    // Тест 2: Валидный город
    dataSource.setCityName("London");
    QCOMPARE(cityValidSpy.count(), 1);
    
    // Тест 3: Город с пробелом
    dataSource.setCityName("New York");
    QCOMPARE(cityValidSpy.count(), 2);
    
    // Тест 4: Город с дефисом
    dataSource.setCityName("St-Petersburg");
    QCOMPARE(cityValidSpy.count(), 3);
    
    // Тест 5: Недопустимые символы
    dataSource.setCityName("Москва123");
    QCOMPARE(cityErrorSpy.count(), 2);
    
    // Тест 6: Слишком длинное название
    QString longCity = QString(60, 'a');
    dataSource.setCityName(longCity);
    QCOMPARE(cityErrorSpy.count(), 3);
}

void WeatherDataSourceTest::testSameValues() {
    WeatherDataSource dataSource;

    // Устанавливаем валидные значения
    dataSource.setApiKey(createValidApiKey());
    dataSource.setCityName(createValidCityName());

    QSignalSpy keyMessageSpy(&dataSource, &WeatherDataSource::weatherKeyMessage);
    QSignalSpy cityMessageSpy(&dataSource, &WeatherDataSource::weatherCityMessage);

    // Устанавливаем те же самые значения
    dataSource.setApiKey(createValidApiKey());
    dataSource.setCityName(createValidCityName());
    
    // Проверяем, что сигналы "уже валидны" были отправлены
    QCOMPARE(keyMessageSpy.count(), 1);
    QCOMPARE(cityMessageSpy.count(), 1);
    
    QString keyMessage = keyMessageSpy.first().first().toString();
    QString cityMessage = cityMessageSpy.first().first().toString();
    
    QVERIFY(keyMessage.contains("already valid"));
    QVERIFY(cityMessage.contains("already valid"));
}

void WeatherDataSourceTest::cleanup() { }

void WeatherDataSourceTest::cleanupTestCase() {
}