#include "weather_data_source.hpp"

WeatherDataSource::WeatherDataSource(QObject *parent):
    QObject(parent),
    m_networkManager(new QNetworkAccessManager(this)) {

    connect(
        m_networkManager,&QNetworkAccessManager::finished,
        this, &WeatherDataSource:: onWeatherDataReceived
    );
}


void WeatherDataSource::requestWeatherData() {
    if (m_apiKey.isEmpty() || !m_apiKeyValid) {
        emit(weatherErrorOccurred(
            "Cannot request weather data: API key not set or invalid"
        ));
        return;
    }

    if (m_cityName.isEmpty() || !m_cityNameValid) {
        emit(weatherErrorOccurred(
            "Cannot request weather data: City name not set or invalid"
        ));
        return;
    }

    QString api_url = QString(
        "https://api.openweathermap.org/data/2.5/weather?q=%1&units=%2&appid=%3&lang=en"
    ).arg(m_cityName)
    .arg(m_units)
    .arg(m_apiKey);
    QUrl url (api_url);

    emit weatherMessage(
        api_url
    );

    QNetworkRequest req(url);

    m_networkManager->get(req);
}


void WeatherDataSource::onWeatherDataReceived(QNetworkReply *reply) {
    handleServerReply(reply);

    handleCleanupReply(reply);
}


void WeatherDataSource::setCityName(const QString &cityName) {

    if (cityName == m_cityName && m_cityNameValid) {
        emit cityMessage(
            "City name unchanged and already valid"
        );
        return;
    }

    if (!validateCityFormat(cityName))
        return;

    QString oldCity = m_cityName;
    m_cityName = cityName;

    emit cityMessage(
        QString( "City changed from %1 to %2")
        .arg(oldCity)
        .arg(m_cityName)
    );
}

void WeatherDataSource::setApiKey(const QString &apiKey)
{
    if (apiKey == m_apiKey && m_apiKeyValid) {
        emit keyMessage(
            "API key unchanged and already valid"
        );
        return;
    }

    QString cleanedKey = apiKey.trimmed();

    // Валидация формата API ключа
    if (!validateKeyFormat(cleanedKey))
        return;

    QString oldKey = m_apiKey;
    m_apiKey = cleanedKey;

    emit keyMessage(
        QString("API key changed from %1 to *****%2")
        .arg(oldKey.isEmpty() ? "empty" : "****" + oldKey.right(6))
        .arg(m_apiKey.right(6))
    );
}

void WeatherDataSource::isMetric(bool isMetric) {
    isMetric ? m_units = "metric": m_units = "imperial";
    emit weatherMessage(
        QString("Units of measurement: Units changed to %1 and already valid")
        .arg(m_units)
    );
}