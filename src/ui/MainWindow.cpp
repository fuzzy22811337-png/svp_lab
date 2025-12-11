#include "MainWindow.hpp"

#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_firstPage(new FirstPage(this))
    , m_dataSource(new WeatherDataSource(this))
    , m_repository(new Repository(m_dataSource)){

    // Настройка главного окна
    setWindowTitle("Weather Application");
    setCentralWidget(m_firstPage);
    setMinimumSize(600, 500);

    // Настройка статус бара
    statusBar()->showMessage("Ready");

    // Настройка соединений
    setupConnections();

    // Начальное состояние
    m_firstPage->enableWeatherRequestButton(false);
}

void MainWindow::setupConnections(){
    if (!m_firstPage || !m_repository) {
        qWarning() << "MainWindow: Components not initialized";
        return;
    }

    // ========== FirstPage -> Repository ==========
    // Пользователь вводит данные в FirstPage, они передаются в Repository

    connect(m_firstPage, &FirstPage::apiKeyChanged,
            m_repository, &Repository::setApiKey);

    connect(m_firstPage, &FirstPage::cityNameChanged,
            m_repository, &Repository::setCityName);

    connect(m_firstPage, &FirstPage::unitsSystemChanged,
           m_repository, &Repository::isMetric);

    connect(m_firstPage, &FirstPage::requestWeatherData,
            m_repository, &Repository::fetchWeatherData);

    // ========== Repository -> FirstPage ==========
    // Repository валидирует данные и отправляет результаты в FirstPage

    connect(m_repository, &Repository::apiKeyValidationResult,
            this, &MainWindow::onApiKeyValidationResult);

    connect(m_repository, &Repository::cityNameValidationResult,
            this, &MainWindow::onCityNameValidationResult);

    connect(m_repository, &Repository::weatherDataReceivedSignal,
            this, &MainWindow::onWeatherDataReceived);

    connect(m_repository, &Repository::weatherRequestStarted,
            this, &MainWindow::onWeatherRequestStarted);

    connect(m_repository, &Repository::weatherRequestCompleted,
            this, &MainWindow::onWeatherRequestCompleted);

    connect(m_repository, &Repository::infoMessage,
            this, &MainWindow::onInfoMessage);
}

// ========== СЛОТЫ ДЛЯ ОБРАБОТКИ СИГНАЛОВ REPOSITORY ==========

void MainWindow::onApiKeyValidationResult(bool isValid, const QString &message){
    //qDebug() << "API Key validation result:" << isValid << message;

    m_apiKeyValid = isValid;
    m_firstPage->showApiKeyValidationMessage(message, isValid);

    // Обновляем кнопку запроса погоды
    m_firstPage->enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);

    // Показываем в статус баре
    statusBar()->showMessage(isValid ? "API key is valid" : "API key error");
}

void MainWindow::onCityNameValidationResult(bool isValid, const QString &message)
{
    //qDebug() << "City Name validation result:" << isValid << message;

    m_cityNameValid = isValid;
    m_firstPage->showCityNameValidationMessage(message, isValid);

    // Обновляем кнопку запроса погоды
    m_firstPage->enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);

    // Показываем в статус баре
    statusBar()->showMessage(isValid ? "City name is valid" : "City name error");
}

void MainWindow::onWeatherDataReceived(const WeatherModel &model)
{
    qDebug() << "Weather data received for city:" << model.getCityName();

    // Закрываем предыдущий диалог, если он открыт
    closeWeatherInfo();

    // Получаем текущую систему измерений из FirstPage
    bool isMetric = m_firstPage->isMetricSystem();

    // Показываем новую информацию о погоде с указанием системы измерений
    showWeatherInfo(model, isMetric);

    // Обновляем статус бар
    statusBar()->showMessage(
        QString("Weather for %1 received").arg(model.getCityName())
    );
}

void MainWindow::showWeatherInfo(const WeatherModel &model, bool isMetric)
{
    // Создаем новый диалог, передавая информацию о системе измерений
    m_weatherDialog = new WeatherInfoDialog(model, isMetric, this);

    // Позиционируем диалог рядом с главным окном
    QPoint dialogPos = this->pos();
    dialogPos.setX(dialogPos.x() + this->width() + 10);
    m_weatherDialog->move(dialogPos);

    // Показываем диалог
    m_weatherDialog->show();

    // Подключаем сигнал закрытия для очистки указателя
    connect(m_weatherDialog, &QDialog::finished,
            this, &MainWindow::closeWeatherInfo);
}


void MainWindow::closeWeatherInfo()
{
    if (m_weatherDialog) {
        // Отключаем сигналы, чтобы не было двойного вызова
        m_weatherDialog->disconnect();

        // Закрываем и удаляем диалог
        m_weatherDialog->close();
        m_weatherDialog->deleteLater();
        m_weatherDialog = nullptr;

        qDebug() << "Weather dialog closed";
    }
}

void MainWindow::onWeatherRequestStarted()
{
    //qDebug() << "Weather request started";

    m_firstPage->enableWeatherRequestButton(false);
    statusBar()->showMessage("Requesting weather data...");

}

void MainWindow::onWeatherRequestCompleted(bool success, const QString &message)
{
    //qDebug() << "Weather request completed:" << success << message;

    m_firstPage->enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
    statusBar()->showMessage(message);

    // Скрыть индикатор загрузки
    //m_firstPage->showLoadingIndicator(false);
}

void MainWindow::onInfoMessage(const QString &message)
{
    //qDebug() << "Info message:" << message;
    statusBar()->showMessage(message);
}