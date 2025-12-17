#include <QRegularExpression>
#include "weather_data_source.hpp"

bool WeatherDataSource::validateKeyFormat(const QString &apiKey) {
    m_apiKeyValid = false;

    if (apiKey.isEmpty()) {
        emit(keyErrorOccurred(
            "API key cannot be empty"
        ));
        return false;
    }

    if (apiKey.length() < 30) {
        emit(keyErrorOccurred(
            QString("API key too short (minimum 30 characters): %1 characters")
            .arg(apiKey.length())
        ));
        return false;
    }

    if (apiKey.length() > 100) {
        emit(keyErrorOccurred(
            QString("API key too long (maximum 100 characters): %1 characters")
            .arg(apiKey.length())
        ));
        return false;
    }

    // Проверка на допустимые символы (буквы, цифры, некоторые спецсимволы)
    static const QRegularExpression regex("^[A-Za-z0-9]+$");
    if (!regex.match(apiKey).hasMatch()) {
        emit keyErrorOccurred(
            "API key contains invalid characters"
        );
        emit keyMessage(
            "Should contain only letters and numbers"
        );
        return false;
    }

    m_apiKeyValid = true;
    emit(keyValidationPassed(
        "API key format validation passed"
    ));
    return true;
}


bool WeatherDataSource::validateCityFormat(const QString &cityName) {
    m_cityNameValid = false;

    if (cityName.isEmpty()) {
        emit cityErrorOccurred(
            "City name cannot be empty"
        );
        return false;
    }

    // Проверка: только английские буквы, цифры, пробелы и дефисы
    static const QRegularExpression regex("^[A-Za-z]+(?:[.,\\s\\-'][A-Za-z]+)*$");
    if (!regex.match(cityName).hasMatch()) {
        emit cityErrorOccurred(
           "Invalid city name format"
        );
        emit cityMessage(
            "Should contain only English letters, spaces(cannot be at the beginning or end), hyphens and apostrophes"
        );
        return false;
    }

    if (cityName.length() > 50) {
        emit cityErrorOccurred(
            QString("City name too long (max 50 characters): %1")
            .arg(cityName)
        );
        return false;
    }

    m_cityNameValid = true;
    emit(cityValidationPassed(
        "City name format validation passed"
    ));
    return true;
}