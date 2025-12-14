#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

class FirstPage : public QWidget {
    Q_OBJECT
public:
    explicit FirstPage(QWidget *parent = nullptr);
    ~FirstPage() override = default;

    void enableWeatherRequestButton(bool enable);

    // Методы для обновления UI
    void showApiKeyValidationMessage(const QString &message, bool isValid);
    void showCityNameValidationMessage(const QString &message, bool isValid);
    void showNetworkError(const QString &message);
    void clearNetworkError();

signals:
    void apiKeyChanged(const QString &apiKey);
    void cityNameChanged(const QString &cityName);
    void unitsSystemChanged(bool isMetric);
    void requestWeatherData();

private slots:
    void onApiKeySaveClicked();
    void onCityNameSaveClicked();
    void onRequestWeatherClicked();
    void onUnitsSystemChanged();

private:
    void setupUI();
    void setupConnections();

    // UI элементы для ввода API ключа
    QLineEdit *m_apiKeyLineEdit;
    QPushButton *m_apiKeySaveButton;
    QLabel *m_apiKeyMessageLabel;

    // UI элементы для ввода названия города
    QLineEdit *m_cityNameLineEdit;
    QPushButton *m_cityNameSaveButton;
    QLabel *m_cityNameMessageLabel;

    // UI элементы для выбора системы мер
    QRadioButton *m_metricRadioButton;
    QRadioButton *m_imperialRadioButton;
    QButtonGroup *m_unitsButtonGroup;

    // Label для отображения ошибок сети  ← ДОБАВЛЯЕМ
    QLabel *m_networkErrorLabel;

    // Кнопка запроса погоды
    QPushButton *m_requestWeatherButton;

    // Флаги валидации
    bool m_apiKeyValid = false;
    bool m_cityNameValid = false;

    // Основные layout
    QVBoxLayout *m_mainLayout;
};