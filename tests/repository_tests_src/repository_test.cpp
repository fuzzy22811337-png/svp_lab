#include <QTest>
#include <QSignalSpy>
#include <QCoreApplication>
#include "repository_test.hpp"
#include "src/data/repository/repository.hpp"

void RepositoryTest::initTestCase() {
}

void RepositoryTest::init() {
    // Инициализация перед каждым тестом
}

QString RepositoryTest::createValidApiKey() const {
    return "tgdgcdgyu7uuieyeuhiutestapikey1234567890abcdef";
}

QString RepositoryTest::createValidCityName() const {
    return "Berlin";
}

void RepositoryTest::testConstructor() {
    // Создаем тестовый data source
    WeatherDataSource* dataSource = new WeatherDataSource();

    {
        Repository repo(dataSource);

        // Проверяем, что репозиторий создан
        QVERIFY(&repo != nullptr);
    }

    // Data source будет удален вместе с репозиторием
}

void RepositoryTest::testSetApiKey() {
    WeatherDataSource* dataSource = new WeatherDataSource();
    Repository repo(dataSource);

    QSignalSpy keyValidationSpy(&repo, &Repository::keyValidationResult);
    QSignalSpy infoMessageSpy(&repo, &Repository::infoMessage);

    // Устанавливаем валидный API ключ
    QString validKey = createValidApiKey();
    repo.setApiKey(validKey);

    // Обрабатываем события для передачи сигналов
    QCoreApplication::processEvents();

    // Проверяем сигналы
    QTRY_COMPARE(keyValidationSpy.count(), 1);
    QVERIFY(infoMessageSpy.count() >= 1);

    // Проверяем, что сигнал говорит об успешной валидации
    QList<QVariant> arguments = keyValidationSpy.first();
    QVERIFY(arguments.at(0).toBool()); // isValid == true
}

void RepositoryTest::testSetCityName() {
    WeatherDataSource* dataSource = new WeatherDataSource();
    Repository repo(dataSource);

    QSignalSpy cityValidationSpy(&repo, &Repository::cityValidationResult);
    QSignalSpy infoMessageSpy(&repo, &Repository::infoMessage);

    // Устанавливаем валидный город
    QString validCity = createValidCityName();
    repo.setCityName(validCity);

    // Обрабатываем события для передачи сигналов
    QCoreApplication::processEvents();

    // Проверяем сигналы
    QTRY_COMPARE(cityValidationSpy.count(), 1);
    QVERIFY(infoMessageSpy.count() >= 1);

    // Проверяем, что сигнал говорит об успешной валидации
    QList<QVariant> arguments = cityValidationSpy.first();
    QVERIFY(arguments.at(0).toBool()); // isValid == true
}

void RepositoryTest::testIsMetric() {
    WeatherDataSource* dataSource = new WeatherDataSource();
    Repository repo(dataSource);

    QSignalSpy infoMessageSpy(&repo, &Repository::infoMessage);

    // Тестируем метрическую систему
    repo.isMetric(true);

    // Тестируем имперскую систему
    repo.isMetric(false);

    // Обрабатываем события
    QCoreApplication::processEvents();

    // Должны быть информационные сообщения
    QVERIFY(infoMessageSpy.count() >= 1);
}

void RepositoryTest::testSignals() {
    WeatherDataSource* dataSource = new WeatherDataSource();
    Repository repo(dataSource);

    // Создаем шпионов для всех сигналов
    QSignalSpy apiKeySpy(&repo, &Repository::keyValidationResult);
    QSignalSpy citySpy(&repo, &Repository::cityValidationResult);
    QSignalSpy errorSpy(&repo, &Repository::weatherErrorResult);
    QSignalSpy infoSpy(&repo, &Repository::infoMessage);

    // Устанавливаем валидные данные
    repo.setApiKey(createValidApiKey());
    repo.setCityName(createValidCityName());

    // Обрабатываем события
    QCoreApplication::processEvents();

    // Проверяем, что сигналы валидации были отправлены
    QTRY_COMPARE(apiKeySpy.count(), 1);
    QTRY_COMPARE(citySpy.count(), 1);
    QTRY_COMPARE(errorSpy.count(), 0);
    // Проверяем информационные сообщения
    QVERIFY(infoSpy.count() > 0);
}

void RepositoryTest::cleanup() { }

void RepositoryTest::cleanupTestCase() { }