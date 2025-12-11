#pragma once

#include <QObject>
#include "weather_data_source.hpp"
#include "weather_model.hpp"

class Repository : public QObject {
    Q_OBJECT

public:
    explicit Repository(WeatherDataSource *datasource, QObject *parent = nullptr);

    // Основной метод для получения погоды
    void fetchWeatherData();

    // Управление источником данных
    void setApiKey(const QString &apiKey);
    void setCityName(const QString &cityName);
    void isMetric(bool isMetric);

signals:
    void apiKeyValidationResult(bool isValid, const QString &message);
    void cityNameValidationResult(bool isValid, const QString &message);

    void weatherDataReceivedSignal(const WeatherModel &model);

    void weatherRequestStarted();
    void weatherRequestCompleted(bool success, const QString &message);

    void infoMessage(const QString &message);

    void dataChanged();

private slots:
    // Обработчики для API ключа
    void handleKeyValidationPassed(const QString &successMessage);
    void handleKeyErrorOccurred(const QString &errorMessage);
    void handleWeatherKeyMessage(const QString &message);

    // Обработчики для города
    void handleCityValidationPassed(const QString &successMessage);
    void handleCityErrorOccurred(const QString &errorMessage);
    void handleWeatherCityMessage(const QString &message);

    // Общие обработчики
    void handleWeatherData(const WeatherModel &model);
    void handleErrorOccurred(const QString &errorMessage);
    void handleWeatherMessage(const QString &message);


private:
    void updateRequestButtonStatus();

    WeatherDataSource *m_datasource = nullptr;
    WeatherModel m_currentWeather;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
    bool m_requestInProgress;
};