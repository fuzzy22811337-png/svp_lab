#include <QStatusBar>
#include <QVBoxLayout>
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_firstPage(new FirstPage(this))
    , m_dataSource(new WeatherDataSource(this))
    , m_repository(new Repository(m_dataSource)){

    // Настройка главного окна
    setWindowTitle("Weather Application");
    setCentralWidget(m_firstPage);
    setMinimumSize(600, 780);

    // Настройка статус бара
    statusBar()->showMessage("Ready");

    // Настройка соединений
    setupConnections();

    // Начальное состояние кнопки и надписи с ошибкой
    m_firstPage->enableWeatherRequestButton(false);
}

void MainWindow::setupConnections(){
    if (!m_firstPage || !m_repository) {
        return;
    }

    // ========== FirstPage -> Repository ==========
    connect(m_firstPage, &FirstPage::apiKeyChanged,
            m_repository, &Repository::setApiKey);

    connect(m_firstPage, &FirstPage::cityNameChanged,
            m_repository, &Repository::setCityName);

    connect(m_firstPage, &FirstPage::unitsSystemChanged,
           m_repository, &Repository::isMetric);

    connect(m_firstPage, &FirstPage::requestWeatherData,
            m_repository, &Repository::fetchWeatherData);

    // ========== Repository -> MainWindow -> FirstPage ==========
    connect(m_repository, &Repository::apiKeyValidationResult,
            this, &MainWindow::onApiKeyValidationResult);

    connect(m_repository, &Repository::cityNameValidationResult,
            this, &MainWindow::onCityNameValidationResult);

    connect(m_repository, &Repository::weatherErrorMessage,
            this, &MainWindow::onWeatherErrorNetworkResult);

    // ========== Repository -> MainWindow ==========
    connect(m_repository, &Repository::weatherDataReceivedSignal,
            this, &MainWindow::onWeatherDataReceived);

    connect(m_repository, &Repository::weatherRequestStarted,
            this, &MainWindow::onWeatherRequestStarted);

    connect(m_repository, &Repository::weatherRequestCompleted,
            this, &MainWindow::onWeatherRequestCompleted);

    connect(m_repository, &Repository::infoMessage,
            this, &MainWindow::onInfoMessage);
}

void MainWindow::onApiKeyValidationResult(bool isValid, const QString &message){
    m_apiKeyValid = isValid;
    m_firstPage->showApiKeyValidationMessage(message, isValid);
}

void MainWindow::onCityNameValidationResult(bool isValid, const QString &message){
    m_cityNameValid = isValid;
    m_firstPage->showCityNameValidationMessage(message, isValid);
}

void MainWindow::onWeatherErrorNetworkResult(const QString &message) {
    // Отображаем ошибку в FirstPage
    m_firstPage->showNetworkError(message);
}

void MainWindow::onInfoMessage(const QString &message) {
    statusBar()->showMessage(message);
}

void MainWindow::onWeatherDataReceived(const WeatherModel &model, bool isMetric){
    // Закрываем предыдущий диалог, если он открыт
    closeWeatherInfo();

    // Показываем новую информацию о погоде с указанием системы измерений
    showWeatherInfo(model, isMetric);
}

void MainWindow::showWeatherInfo(const WeatherModel &model, bool isMetric) {
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


void MainWindow::closeWeatherInfo() {
    if (m_weatherDialog) {
        m_weatherDialog->disconnect();
        // Закрываем и удаляем диалог
        m_weatherDialog->close();
        m_weatherDialog->deleteLater();
        m_weatherDialog = nullptr;
    }
}

void MainWindow::onWeatherRequestStarted() {
    m_firstPage->enableWeatherRequestButton(false);
    statusBar()->showMessage("Requesting weather data...");
}

void MainWindow::onWeatherRequestCompleted(bool success, const QString &message) {
    if (success) {
        m_firstPage->enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
        statusBar()->showMessage(message);
        statusBar()->showMessage("Weather request completed");
        m_firstPage->clearNetworkError();
    }else {
        m_firstPage->enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
        statusBar()->showMessage(message);
    }

}