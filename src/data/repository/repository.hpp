#pragma once

#include <QObject>
#include <QString>
#include "weather_data_source.hpp"
#include "weather_model.hpp"

class Repository : public QObject {
    Q_OBJECT

public:
    explicit Repository(QObject *parent = nullptr);
    ~Repository() override = default;

    void requestWeatherData();

    void setApiKey(const QString &apiKey);
    void setCityName(const QString &cityName);
    void isMetric(bool isMetric);

signals:
    void keyValidationResult(bool isValid, const QString &message);
    void cityValidationResult(bool isValid, const QString &message);

    void weatherErrorResult(const QString &message);
    void infoMessage(const QString &message);

    void weatherDataReceived(const WeatherModel &model, bool isMetric);

    void weatherRequestStarted();
    void weatherRequestCompleted(bool success, const QString &message);

private slots:
    void onKeyValidationPassed(const QString &successMessage);
    void onKeyErrorOccurred(const QString &errorMessage);
    void onKeyMessage(const QString &message);

    void onCityValidationPassed(const QString &successMessage);
    void onCityErrorOccurred(const QString &errorMessage);
    void onCityMessage(const QString &message);

    void onWeatherDataReceived(const WeatherModel &model, bool isMetric);

    void onWeatherErrorOccurred(const QString &errorMessage);
    void onWeatherMessage(const QString &message);

private:
    void updateRequestButtonStatus();

    WeatherDataSource *m_datasource = nullptr;
    WeatherModel m_currentWeather;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};