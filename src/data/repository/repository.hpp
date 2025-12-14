#pragma once

#include <QObject>
#include <QString>
#include "weather_data_source.hpp"
#include "weather_model.hpp"

class Repository : public QObject {
    Q_OBJECT

public:
    explicit Repository(WeatherDataSource *datasource, QObject *parent = nullptr);
    ~Repository() override = default;

    void fetchWeatherData();

    void setApiKey(const QString &apiKey);
    void setCityName(const QString &cityName);
    void isMetric(bool isMetric);

signals:
    void apiKeyValidationResult(bool isValid, const QString &message);
    void cityNameValidationResult(bool isValid, const QString &message);

    void weatherErrorMessage(const QString &message);
    void infoMessage(const QString &message);

    void weatherDataReceivedSignal(const WeatherModel &model, bool isMetric);

    void weatherRequestStarted();
    void weatherRequestCompleted(bool success, const QString &message);

private slots:
    void handleKeyValidationPassed(const QString &successMessage);
    void handleKeyErrorOccurred(const QString &errorMessage);
    void handleWeatherKeyMessage(const QString &message);

    void handleCityValidationPassed(const QString &successMessage);
    void handleCityErrorOccurred(const QString &errorMessage);
    void handleWeatherCityMessage(const QString &message);

    void handleWeatherData(const WeatherModel &model, bool isMetric);

    void handleErrorOccurred(const QString &errorMessage);
    void handleWeatherMessage(const QString &message);

private:
    void updateRequestButtonStatus();

    WeatherDataSource *m_datasource = nullptr;
    WeatherModel m_currentWeather;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};