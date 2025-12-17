#pragma once

#include <QMainWindow>
#include "first_page.hpp"
#include "repository.hpp"
#include "weather_info_dialog.hpp"
#include "weather_data_source.hpp"

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    // Слоты для обработки сигналов репозитория
    void onKeyValidationResult(bool isValid, const QString &message);
    void onCityValidationResult(bool isValid, const QString &message);
    void onWeatherErrorResult(const QString &message);

    void onWeatherDataReceived(const WeatherModel &model, bool isMetric);

    void onWeatherRequestStarted();
    void onWeatherRequestCompleted(bool success, const QString &message);

    void onInfoMessage(const QString &message);

private:
    void setupConnections();
    void showWeatherInfo(const WeatherModel &model, bool isMetric);
    void closeWeatherInfo();

    Repository *m_repository;
    FirstPage *m_firstPage;
    WeatherInfoDialog *m_weatherDialog = nullptr;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};