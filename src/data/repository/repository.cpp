#include "repository.hpp"

Repository::Repository(WeatherDataSource *datasource, QObject *parent):
    QObject(parent),
    m_datasource(datasource)
{
    if (!m_datasource) {
        return;
    }

    // Подключаем сигналы от DataSource
    connect(m_datasource, &WeatherDataSource::weatherDataReceived,
        this, &Repository::handleWeatherData);

    connect(m_datasource, &WeatherDataSource::keyValidationPassed,
        this, &Repository::handleKeyValidationPassed);
    connect(m_datasource, &WeatherDataSource::cityValidationPassed,
        this, &Repository::handleCityValidationPassed);

    connect(m_datasource, &WeatherDataSource::weatherDataMessage,
        this, &Repository::handleWeatherMessage);
    connect(m_datasource, &WeatherDataSource::weatherKeyMessage,
        this, &Repository::handleWeatherKeyMessage);
    connect(m_datasource, &WeatherDataSource::weatherCityMessage,
        this, &Repository::handleWeatherCityMessage);

    connect(m_datasource, &WeatherDataSource::errorOccurred,
        this, &Repository::handleErrorOccurred);
    connect(m_datasource, &WeatherDataSource::keyErrorOccurred,
        this, &Repository::handleKeyErrorOccurred);
    connect(m_datasource, &WeatherDataSource::cityErrorOccurred,
        this, &Repository::handleCityErrorOccurred);
}

void Repository::fetchWeatherData() {
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


void Repository::handleWeatherData(const WeatherModel &model, bool isMetric) {
    m_currentWeather = model;

    // Эмитируем сигнал для UI
    emit weatherDataReceivedSignal(model, isMetric);
    emit weatherRequestCompleted(true, "Weather data received successfully");
    //emit dataChanged();

    emit infoMessage(QString("Weather data for %1 received").arg(model.getCityName()));
}

void Repository::handleKeyValidationPassed(const QString &successMessage) {
    m_apiKeyValid = true;
    emit apiKeyValidationResult(true, successMessage);
    updateRequestButtonStatus();
}

void Repository::handleKeyErrorOccurred(const QString &errorMessage) {
    m_apiKeyValid = false;
    emit apiKeyValidationResult(false, errorMessage);
    updateRequestButtonStatus();
}

void Repository::handleWeatherKeyMessage(const QString &message) {
    emit infoMessage("API key: " + message);
}


void Repository::handleCityValidationPassed(const QString &successMessage) {
    m_cityNameValid = true;
    emit cityNameValidationResult(true, successMessage);
    updateRequestButtonStatus();
}

void Repository::handleCityErrorOccurred(const QString &errorMessage) {
    m_cityNameValid = false;
    emit cityNameValidationResult(false, errorMessage);
    updateRequestButtonStatus();
}

void Repository::handleWeatherCityMessage(const QString &message) {
    emit infoMessage("City name: " + message);
}


void Repository::handleErrorOccurred(const QString &errorMessage) {
    // Общие ошибки (не связанные с валидацией)
    emit weatherRequestCompleted(false, errorMessage);
    emit weatherErrorMessage("Response Error: " + errorMessage);
}

void Repository::handleWeatherMessage(const QString &message) {
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
