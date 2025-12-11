#include "weather_data_source.hpp"

void WeatherDataSource::handleParseReply(QNetworkReply *reply) {
    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject obj = doc.object();

    WeatherModel model = WeatherModel();

    QJsonObject objMain = obj["main"].toObject();
    model.setTemperature(objMain["temp"].toDouble());
    model.setPressure(objMain["pressure"].toDouble());

    QJsonArray weatherArray = obj["weather"].toArray();
    QJsonObject objWeather = weatherArray.first().toObject();
    model.setDescription(objWeather["description"].toString());
    model.setIconCode(objWeather["icon"].toString());

    QJsonObject objWind = obj["wind"].toObject();
    model.setWindSpeed(objWind["speed"].toDouble());

    model.setCityName(obj["name"].toString());

    emit weatherDataReceived(model);
}


void WeatherDataSource::handleServerResponse(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        handleParseReply(reply);
        return;
    }

    // Читаем ответ
    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (doc.isNull() || !doc.isObject()) {
        emit errorOccurred("Invalid JSON response from server");
        return;
    }

    QJsonObject obj = doc.object();

    // Проверяем код ответа OpenWeather API
    if (obj.contains("cod")) {
        int code = obj["cod"].toInt();

        // Ошибка от API
        QString errorMessage;
        QString errorDescription;

        switch(code) {
            case 200:
                handleParseReply(reply);
            case 400:
                errorMessage = "Bad Request";
                errorDescription = "Please check for typos and ensure all required query parameters are present";
                /*m_apiKeyValid = false;
                m_cityNameValid = false;*/
                break;
            case 401:
                errorMessage = "Unauthorized. Invalid API key";
                errorDescription = "Please check your API key";
                //m_apiKeyValid = false;
                break;
            case 403:
                errorMessage = "Forbidden. API access restricted";
                errorDescription = "Please use a supported endpoint or upgrade your plan";
                break;
            case 404:
                errorMessage = QString("City '%1' not found").arg(m_cityName);
                errorDescription = "Please check the city name";
                //m_cityNameValid = false;
                break;
            case 429:
                errorMessage = "API rate limit exceeded";
                errorDescription = "Please try again later";
                break;
            case 500:
            case 502:
            case 503:
            case 504:
                errorMessage = "Server error";
                errorDescription = "Please try again later";
                break;
            default:
                if (obj.contains("message")) {
                    errorMessage = QString("API Error %1: %2").arg(code).arg(obj["message"].toString());
                } else {
                    errorMessage = QString("API Error %1").arg(code);
                }
        }

        emit errorOccurred(errorMessage);
        emit weatherDataMessage(errorDescription);

    } else {
        emit errorOccurred("Strange answer (without cod)");
        emit weatherDataMessage("Please try again");
    }
}