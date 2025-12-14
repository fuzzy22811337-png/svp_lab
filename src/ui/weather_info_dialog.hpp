#pragma once

#include <QDialog>
#include "weather_model.hpp"

class QLabel;
class QPushButton;
class QFrame;
class QGroupBox;

class WeatherInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit WeatherInfoDialog(const WeatherModel &weatherModel, bool isMetric, QWidget *parent = nullptr);
    ~WeatherInfoDialog() override = default;

private:
    void setupUI(const WeatherModel &weatherModel, bool isMetric);

    // UI элементы
    QLabel *m_titleLabel;
    QFrame *m_separator;
    QGroupBox *m_weatherGroupBox;

    // Погодные данные
    QLabel *m_cityLabel;
    QLabel *m_temperatureLabel;
    QLabel *m_descriptionLabel;
    QLabel *m_pressureLabel;
    QLabel *m_windSpeedLabel;

    // Кнопка закрытия
    QPushButton *m_closeButton;

    // Информация о системе измерений
    bool m_isMetric;
};