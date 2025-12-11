#include "repository.hpp"
#include <QDebug>

Repository::Repository(WeatherDataSource *datasource, QObject *parent):
    QObject(parent),
    m_datasource(datasource)
{
    if (!m_datasource) {
        qWarning() << "Repository: DataSource is null!";
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
    /*if (!m_datasource) {
        emit weatherRequestCompleted(false, "DataSource not initialized");
        return;
    }*/

    // Делегируем запрос DataSource
    emit weatherRequestStarted();
    m_datasource->requestWeatherData();

    //qDebug() << "Repository: Weather request completed successfully";
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

    /*if (m_datasource) {
        m_lastCityName = cityName; // Сохраняем для отслеживания
        m_datasource->setCityName(cityName);
    }*/
}


void Repository::handleWeatherData(const WeatherModel &model) {
    // Сохраняем данные
    m_currentWeather = model;

    //model.print();

    // Эмитируем сигнал для UI
    emit weatherDataReceivedSignal(model);
    emit weatherRequestCompleted(true, "Weather data received successfully");
    emit dataChanged();

    emit infoMessage(QString("Weather data for %1 received").arg(model.getCityName()));
}



void Repository::handleKeyValidationPassed(const QString &successMessage) {
    //qDebug() << "Repository: API key validation passed:" << successMessage;
    m_apiKeyValid = true;
    emit apiKeyValidationResult(true, successMessage);
    updateRequestButtonStatus();
    emit infoMessage("API key is valid and saved");
}

void Repository::handleKeyErrorOccurred(const QString &errorMessage) {
    //qDebug() << "Repository: API key error:" << errorMessage;
    m_apiKeyValid = false;
    emit apiKeyValidationResult(false, errorMessage);
    updateRequestButtonStatus();
    emit infoMessage("API key error: " + errorMessage);
}

void Repository::handleWeatherKeyMessage(const QString &message) {
    //qDebug() << "Repository: API key message:" << message;
    // Информационные сообщения об API ключе
    // Например: "API key changed from old to new"
    emit infoMessage("API: " + message);
}



void Repository::handleCityValidationPassed(const QString &successMessage) {
    //qDebug() << "Repository: City validation passed:" << successMessage;
    m_cityNameValid = true;
    emit cityNameValidationResult(true, successMessage);
    updateRequestButtonStatus();
    emit infoMessage("City name is valid and saved");
}


void Repository::handleCityErrorOccurred(const QString &errorMessage) {
    //qDebug() << "Repository: City error:" << errorMessage;
    m_cityNameValid = false;
    emit cityNameValidationResult(false, errorMessage);
    updateRequestButtonStatus();
    emit infoMessage("City error: " + errorMessage);
}

void Repository::handleWeatherCityMessage(const QString &message) {
    //qDebug() << "Repository: API key message:" << message;
    // Информационные сообщения об API ключе
    // Например: "API key changed from old to new"
    emit infoMessage("API: " + message);
}



void Repository::handleErrorOccurred(const QString &errorMessage) {
    //qDebug() << "Repository: General error:" << errorMessage;
    m_requestInProgress = false;

    // Общие ошибки (не связанные с валидацией)
    emit weatherRequestCompleted(false, errorMessage);
    emit infoMessage("Error: " + errorMessage);
}

void Repository::handleWeatherMessage(const QString &message) {
    //qDebug() << "Repository: General message:" << message;
    // Общие информационные сообщения
    emit infoMessage(message);
}



void Repository::updateRequestButtonStatus() {
    // Логика на основе внутреннего состояния
    if (m_apiKeyValid && m_cityNameValid) {
        emit infoMessage("Ready to fetch weather");
    } else {
        // Показываем, чего именно не хватает
        QString status = "Waiting for: ";
        if (!m_apiKeyValid) status += "API key validation. ";
        if (!m_cityNameValid) status += "City name validation.";
        emit infoMessage(status);
    }
}
