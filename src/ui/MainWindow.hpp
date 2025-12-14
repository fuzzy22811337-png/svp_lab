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
    void onApiKeyValidationResult(bool isValid, const QString &message);
    void onCityNameValidationResult(bool isValid, const QString &message);
    void onWeatherErrorNetworkResult(const QString &message);

    void onWeatherDataReceived(const WeatherModel &model, bool isMetric);

    void onWeatherRequestStarted();
    void onWeatherRequestCompleted(bool success, const QString &message);

    void onInfoMessage(const QString &message);

private:
    void setupConnections();
    void showWeatherInfo(const WeatherModel &model, bool isMetric);
    void closeWeatherInfo();

    WeatherDataSource *m_dataSource;
    Repository *m_repository;
    FirstPage *m_firstPage;
    WeatherInfoDialog *m_weatherDialog;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};