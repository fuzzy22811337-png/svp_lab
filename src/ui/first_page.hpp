#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>

class FirstPage : public QWidget {
    Q_OBJECT
public:
    explicit FirstPage(QWidget *parent = nullptr);
    ~FirstPage() override = default;

    // Геттеры для получения введенных данных
    QString getApiKey() const;
    QString getCityName() const;
    bool isMetricSystem() const;

    // Методы для обновления UI
    void showApiKeyValidationMessage(const QString &message, bool isValid);
    void showCityNameValidationMessage(const QString &message, bool isValid);
    void enableWeatherRequestButton(bool enable);

signals:
    // Сигналы для взаимодействия с другими компонентами
    void apiKeyChanged(const QString &apiKey);
    void cityNameChanged(const QString &cityName);
    void requestWeatherData();
    void unitsSystemChanged(bool isMetric);


private slots:
    void onApiKeySaveClicked();
    void onCityNameSaveClicked();
    void onRequestWeatherClicked();
    void onUnitsSystemChanged();

private:
    void setupUI();
    void setupConnections();

    // UI элементы для API ключа
    QLabel *m_apiKeyLabel;
    QLineEdit *m_apiKeyLineEdit;
    QPushButton *m_apiKeySaveButton;
    QLabel *m_apiKeyMessageLabel;

    // UI элементы для названия города
    QLabel *m_cityNameLabel;
    QLineEdit *m_cityNameLineEdit;
    QPushButton *m_cityNameSaveButton;
    QLabel *m_cityNameMessageLabel;

    // UI элементы для выбора системы мер
    QRadioButton *m_metricRadioButton;
    QRadioButton *m_imperialRadioButton;
    QButtonGroup *m_unitsButtonGroup;

    // Кнопка запроса погоды
    QPushButton *m_requestWeatherButton;

    // Флаги валидации
    bool m_apiKeyValid;
    bool m_cityNameValid;

    // Основные layout
    QVBoxLayout *m_mainLayout;
};