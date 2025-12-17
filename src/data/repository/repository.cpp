#include "repository.hpp"

Repository::Repository(QObject *parent):
    QObject(parent),
    m_datasource(new WeatherDataSource()) {

    // Подключаем сигналы от DataSource
    connect(m_datasource, &WeatherDataSource::weatherDataReceived,
        this, &Repository::onWeatherDataReceived);

    connect(m_datasource, &WeatherDataSource::keyValidationPassed,
        this, &Repository::onKeyValidationPassed);
    connect(m_datasource, &WeatherDataSource::cityValidationPassed,
        this, &Repository::onCityValidationPassed);

    connect(m_datasource, &WeatherDataSource::weatherMessage,
        this, &Repository::onWeatherMessage);
    connect(m_datasource, &WeatherDataSource::keyMessage,
        this, &Repository::onKeyMessage);
    connect(m_datasource, &WeatherDataSource::cityMessage,
        this, &Repository::onCityMessage);

    connect(m_datasource, &WeatherDataSource::weatherErrorOccurred,
        this, &Repository::onWeatherErrorOccurred);
    connect(m_datasource, &WeatherDataSource::keyErrorOccurred,
        this, &Repository::onKeyErrorOccurred);
    connect(m_datasource, &WeatherDataSource::cityErrorOccurred,
        this, &Repository::onCityErrorOccurred);
}

void Repository::requestWeatherData() {
    // Делегируем запрос DataSource
    emit weatherRequestStarted();
    m_datasource->requestWeatherData();

}


void Repository::isMetric(bool isMetric) {
    if (m_datasource) {
        m_datasource->isMetric(isMetric);
    }
};

void Repository::setApiKey(const QString &apiKey) {
    if (m_datasource) {
        m_datasource->setApiKey(apiKey);
    }
};

void Repository::setCityName(const QString &cityName) {
    if (m_datasource) {
        m_datasource->setCityName(cityName);
    }
}


void Repository::onWeatherDataReceived(const WeatherModel &model, bool isMetric) {
    m_currentWeather = model;

    // Эмитируем сигнал для UI
    emit weatherDataReceived(model, isMetric);
    emit weatherRequestCompleted(true, "Weather data received successfully");
    //emit dataChanged();

    emit infoMessage(QString("Weather data for %1 received").arg(model.getCityName()));
}

void Repository::onKeyValidationPassed(const QString &successMessage) {
    m_apiKeyValid = true;
    emit keyValidationResult(true, successMessage);
    updateRequestButtonStatus();
}

void Repository::onKeyErrorOccurred(const QString &errorMessage) {
    m_apiKeyValid = false;
    emit keyValidationResult(false, errorMessage);
    updateRequestButtonStatus();
}

void Repository::onKeyMessage(const QString &message) {
    emit infoMessage("API key: " + message);
}


void Repository::onCityValidationPassed(const QString &successMessage) {
    m_cityNameValid = true;
    emit cityValidationResult(true, successMessage);
    updateRequestButtonStatus();
}

void Repository::onCityErrorOccurred(const QString &errorMessage) {
    m_cityNameValid = false;
    emit cityValidationResult(false, errorMessage);
    updateRequestButtonStatus();
}

void Repository::onCityMessage(const QString &message) {
    emit infoMessage("City name: " + message);
}


void Repository::onWeatherErrorOccurred(const QString &errorMessage) {
    // Общие ошибки (не связанные с валидацией)
    emit weatherRequestCompleted(false, errorMessage);
    emit weatherErrorResult("Response Error: " + errorMessage);
}

void Repository::onWeatherMessage(const QString &message) {
    // Общие информационные сообщения
    emit infoMessage(message);
}


void Repository::updateRequestButtonStatus() {
    // Логика на основе внутреннего состояния
    if (m_apiKeyValid && m_cityNameValid) {
        emit infoMessage("Ready to fetch weather");
    } else if ((m_apiKeyValid && !m_cityNameValid) || (!m_apiKeyValid && m_cityNameValid)) {
        // Показываем, чего именно не хватает
        QString status = "Waiting for: ";
        if (!m_apiKeyValid) status += "API key validation";
        if (!m_cityNameValid) status += "City name validation";
        emit infoMessage(status);
    }
}
