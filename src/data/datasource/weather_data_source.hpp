#pragma once
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "weather_model.hpp"

class WeatherDataSource : public QObject {
    Q_OBJECT

public:
    explicit WeatherDataSource (QObject *parent = nullptr);
    ~WeatherDataSource() override = default;

    void requestWeatherData();

    void setCityName(const QString &cityName);
    void setApiKey(const QString &apiKey);

    void isMetric(bool isMetric);

signals:
    void weatherDataReceived(const WeatherModel &model, bool isMetric);

    void errorOccurred(const QString &errorMessage);
    void cityErrorOccurred(const QString &errorMessage);
    void keyErrorOccurred(const QString &errorMessage);

    void weatherDataMessage(const QString &message);
    void weatherCityMessage(const QString &message);
    void weatherKeyMessage(const QString &message);

    void cityValidationPassed(const QString &successMessage);
    void keyValidationPassed(const QString &successMessage);

private slots:
    void onWeatherDataReceived(QNetworkReply *reply);

private:
    bool validateApiKeyFormat(const QString &apiKey);
    bool validateCityNameFormat(const QString &cityName);
    void handleParseReply(QNetworkReply *reply);
    void handleServerReply(QNetworkReply *reply);
    void cleanupReply(QNetworkReply *reply);

    QNetworkAccessManager *m_networkManager = nullptr;
    QNetworkReply *m_currentReply = nullptr;

    QString m_apiKey = "";
    QString m_units = "metric";
    QString m_cityName = "Moscow";

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};