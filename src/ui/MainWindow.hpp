#pragma once

#include <QMainWindow>
#include "first_page.hpp"
#include "repository.hpp"
#include "weather_info_dialog.hpp"
#include "weather_data_source.hpp"
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onApiKeyValidationResult(bool isValid, const QString &message);
    void onCityNameValidationResult(bool isValid, const QString &message);

    void onWeatherDataReceived(const WeatherModel &model);

    void onWeatherRequestStarted();
    void onWeatherRequestCompleted(bool success, const QString &message);

    void onInfoMessage(const QString &message);

private:
    void setupConnections();
    void showWeatherInfo(const WeatherModel &model, bool isMetric);
    void closeWeatherInfo();

    FirstPage *m_firstPage;
    WeatherDataSource *m_dataSource;
    Repository *m_repository;
    WeatherInfoDialog *m_weatherDialog;

    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;
};