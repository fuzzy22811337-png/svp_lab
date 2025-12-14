#include "weather_info_dialog.hpp"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QGroupBox>
#include <QFont>
#include <QDebug>

WeatherInfoDialog::WeatherInfoDialog(const WeatherModel &weatherModel, bool isMetric, QWidget *parent)
    : QDialog(parent)
    , m_isMetric(isMetric)
{
    setupUI(weatherModel, isMetric);

    // Настройка окна
    setWindowTitle("Weather information");
    setFixedSize(500, 580);
    setModal(false);
}

void WeatherInfoDialog::setupUI(const WeatherModel &weatherModel, bool isMetric)
{
    // Основной layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Заголовок с указанием системы измерений
    QString title = QString("Weather information (%1)")
                    .arg(isMetric ? "Metric system" : "Imperial system");
    m_titleLabel = new QLabel(title);
    m_titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; color: #333; }");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_titleLabel);

    // Разделитель
    m_separator = new QFrame();
    m_separator->setFrameShape(QFrame::HLine);
    m_separator->setFrameShadow(QFrame::Plain);
    m_separator->setStyleSheet("background-color: #333;");
    mainLayout->addWidget(m_separator);

    // Группа с погодной информацией
    m_weatherGroupBox = new QGroupBox("Current weather");
    QVBoxLayout *weatherLayout = new QVBoxLayout(m_weatherGroupBox);
    weatherLayout->setSpacing(15);

    // Название города
    m_cityLabel = new QLabel(weatherModel.getCityName(), m_weatherGroupBox);
    m_cityLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 22px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   padding: 10px 0;"
        "   text-align: center;"
        "}"
    );
    weatherLayout->addWidget(m_cityLabel);

    // Температура - меняем только единицы
    QString tempUnit = isMetric ? "°C" : "°F";
    m_temperatureLabel = new QLabel(
        QString("%1%2").arg(weatherModel.getTemperature(), 0, 'f', 1).arg(tempUnit),
        m_weatherGroupBox
    );
    m_temperatureLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 42px;"
        "   font-weight: bold;"
        "   color: #e74c3c;"
        "   padding: 10px 0;"
        "   text-align: center;"
        "}"
    );
    weatherLayout->addWidget(m_temperatureLabel);

    // Описание погоды (не зависит от системы измерений)
    m_descriptionLabel = new QLabel(
        QString("%1").arg(weatherModel.getDescription()),
        m_weatherGroupBox
    );
    m_descriptionLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 16px;"
        "   color: #3498db;"
        "   font-style: italic;"
        "   padding: 5px 0;"
        "   text-align: center;"
        "}"
    );
    weatherLayout->addWidget(m_descriptionLabel);

    // Дополнительная информация (давление и ветер)
    QHBoxLayout *detailsLayout = new QHBoxLayout();

    // Давление - меняем только единицы
    QFrame *pressureFrame = new QFrame(m_weatherGroupBox);
    pressureFrame->setStyleSheet(
        "QFrame {"
        "   background-color: #f0f8ff;"
        "   border: 1px solid #b0d0ff;"
        "   border-radius: 6px;"
        "   padding: 10px;"
        "}"
    );

    QVBoxLayout *pressureLayout = new QVBoxLayout(pressureFrame);
    QLabel *pressureTitle = new QLabel("Pressure", pressureFrame);
    pressureTitle->setStyleSheet(
        "QLabel {"
        "   font-size: 12px;"
        "   color: #7f8c8d;"
        "   text-align: center;"
        "}"
    );

    // Меняем только единицы давления
    QString pressureUnit = " hPa";  // OpenWeather возвращает в любой системе hPa
    m_pressureLabel = new QLabel(
        QString("%1%2").arg(weatherModel.getPressure(), 0, 'f', 1).arg(pressureUnit),
        pressureFrame
    );
    m_pressureLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   text-align: center;"
        "}"
    );

    pressureLayout->addWidget(pressureTitle);
    pressureLayout->addWidget(m_pressureLabel);
    pressureLayout->setAlignment(Qt::AlignCenter);
    detailsLayout->addWidget(pressureFrame);

    // Скорость ветра - меняем только единицы
    QFrame *windFrame = new QFrame(m_weatherGroupBox);
    windFrame->setStyleSheet(
        "QFrame {"
        "   background-color: #f0f8ff;"
        "   border: 1px solid #b0d0ff;"
        "   border-radius: 6px;"
        "   padding: 10px;"
        "}"
    );

    QVBoxLayout *windLayout = new QVBoxLayout(windFrame);
    QLabel *windTitle = new QLabel("Wind speed", windFrame);
    windTitle->setStyleSheet(
        "QLabel {"
        "   font-size: 12px;"
        "   color: #7f8c8d;"
        "   text-align: center;"
        "}"
    );

    // Меняем только единицы скорости ветра
    QString windUnit = isMetric ? " m/s" : " miles/h";
    m_windSpeedLabel = new QLabel(
        QString("%1%2").arg(weatherModel.getWindSpeed(), 0, 'f', 1).arg(windUnit),
        windFrame
    );
    m_windSpeedLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   text-align: center;"
        "}"
    );

    windLayout->addWidget(windTitle);
    windLayout->addWidget(m_windSpeedLabel);
    windLayout->setAlignment(Qt::AlignCenter);
    detailsLayout->addWidget(windFrame);

    weatherLayout->addLayout(detailsLayout);

    mainLayout->addWidget(m_weatherGroupBox);

    // Добавляем растягивающийся элемент
    mainLayout->addStretch();

    // Кнопка закрытия
    m_closeButton = new QPushButton("Close", this);
    m_closeButton->setMinimumHeight(40);
    m_closeButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 10px 30px;"
        "   background-color: #4A90E2;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #357ABD;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c5d9e;"
        "}"
    );

    connect(m_closeButton, &QPushButton::clicked,
            this, &WeatherInfoDialog::close);

    mainLayout->addWidget(m_closeButton, 0, Qt::AlignCenter);

    // Устанавливаем общий стиль для группы
    m_weatherGroupBox->setStyleSheet(
        "QGroupBox {"
        "   font-weight: bold;"
        "   border: 1px solid #ddd;"
        "   border-radius: 6px;"
        "   margin-top: 10px;"
        "   padding-top: 10px;"
        "   background-color: #f9f9f9;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 5px 0 5px;"
        "   color: #333;"
        "}"
    );
}