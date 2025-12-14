#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QRegularExpressionValidator>
#include "first_page.hpp"

FirstPage::FirstPage(QWidget *parent)
    : QWidget(parent)
    , m_apiKeyValid(false)
    , m_cityNameValid(false) {
    setupUI();
    setupConnections();
    show();
}

void FirstPage::setupUI() {
    // ======Настройка основного layout======
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(30, 30, 30, 30);

    // Добавляем заголовок для программы
    QLabel *titleLabel = new QLabel("Setting the weather parameters");
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; color: #333; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Добавляем разделитель
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Plain);
    separator->setStyleSheet("background-color: #333;");
    m_mainLayout->addWidget(separator);

    // ======Секция для API ключа======
    QGroupBox *apiKeyGroup = new QGroupBox("API Key");
    QVBoxLayout *apiKeyLayout = new QVBoxLayout(apiKeyGroup);

    // Надпись
    QLabel *apiKeyLabel = new QLabel("Enter your API key:", apiKeyGroup);
    apiKeyLabel->setStyleSheet("QLabel { font-size: 14px; color: #333; }");
    apiKeyLayout->addWidget(apiKeyLabel);

    // Layout для строки ввода и кнопки
    QHBoxLayout *apiKeyInputLayout = new QHBoxLayout();

    // Настройка строки ввода
    m_apiKeyLineEdit = new QLineEdit(apiKeyGroup);
    m_apiKeyLineEdit->setPlaceholderText("Enter the API key from OpenWeather");
    m_apiKeyLineEdit->setEchoMode(QLineEdit::Password);
    m_apiKeyLineEdit->setMinimumWidth(300);
    m_apiKeyLineEdit->setStyleSheet(
        "QLineEdit {"
        "   padding: 8px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4A90E2;"
        "}"
    );

    // Установка валидатора для ввода
    QRegularExpression apiKeyRegex("^[A-Za-z0-9]+$");
    QValidator *apiKeyValidator = new QRegularExpressionValidator(apiKeyRegex);
    m_apiKeyLineEdit->setValidator(apiKeyValidator);

    // Настройки кнопки "Сохранить"
    m_apiKeySaveButton = new QPushButton("Save", apiKeyGroup);
    m_apiKeySaveButton->setEnabled(false);
    m_apiKeySaveButton->setStyleSheet(
        "QPushButton {"
        "   padding: 8px 20px;"
        "   background-color: #4A90E2;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #357ABD;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c5d9e;"
        "}"
        "QPushButton:focus {"
        "   outline: none;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #cccccc;"
        "   color: #666666;"
        "}"
    );
    
    apiKeyInputLayout->addWidget(m_apiKeyLineEdit);
    apiKeyInputLayout->addWidget(m_apiKeySaveButton);
    apiKeyLayout->addLayout(apiKeyInputLayout);

    // Label для сообщений об API ключе
    m_apiKeyMessageLabel = new QLabel("", apiKeyGroup);
    m_apiKeyMessageLabel->setStyleSheet("QLabel { font-size: 12px; padding: 5px 0; }");
    m_apiKeyMessageLabel->setWordWrap(true);
    apiKeyLayout->addWidget(m_apiKeyMessageLabel);

    m_mainLayout->addWidget(apiKeyGroup);

    // ======Секция для названия города======
    QGroupBox *cityNameGroup = new QGroupBox("City Name");
    QVBoxLayout *cityNameLayout = new QVBoxLayout(cityNameGroup);

    // Надпись
    QLabel *cityNameLabel = new QLabel("Enter your city name:", cityNameGroup);
    cityNameLabel->setStyleSheet("QLabel { font-size: 14px; color: #555; }");
    cityNameLayout->addWidget(cityNameLabel);

    // Layout для строки ввода и кнопки
    QHBoxLayout *cityNameInputLayout = new QHBoxLayout();

    // Настройка строки ввода
    m_cityNameLineEdit = new QLineEdit(cityNameGroup);
    m_cityNameLineEdit->setPlaceholderText("Example: Moscow or New York");
    m_cityNameLineEdit->setMinimumWidth(300);
    m_cityNameLineEdit->setStyleSheet(
        "QLineEdit {"
        "   padding: 8px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4A90E2;"
        "}"
    );
    
    // Установка валидатора для ввода
    QRegularExpression cityNameRegex("^[A-Za-z]+(?:[.,\\s\\-'][A-Za-z]+)*$");
    QValidator *cityNameValidator = new QRegularExpressionValidator(cityNameRegex);
    m_cityNameLineEdit->setValidator(cityNameValidator);

    // Настройки кнопки "Сохранить"
    m_cityNameSaveButton = new QPushButton("Save", cityNameGroup);
    m_cityNameSaveButton->setEnabled(false);
    m_cityNameSaveButton->setStyleSheet(
        "QPushButton {"
        "   padding: 8px 20px;"
        "   background-color: #4A90E2;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #357ABD;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #2c5d9e;"
        "}"
        "QPushButton:focus {"
        "   outline: none;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #cccccc;"
        "   color: #666666;"
        "}"
    );
    
    cityNameInputLayout->addWidget(m_cityNameLineEdit);
    cityNameInputLayout->addWidget(m_cityNameSaveButton);
    cityNameLayout->addLayout(cityNameInputLayout);

    // Label для сообщений о названии города
    m_cityNameMessageLabel = new QLabel("", cityNameGroup);
    m_cityNameMessageLabel->setStyleSheet("QLabel { font-size: 12px; padding: 5px 0; }");
    m_cityNameMessageLabel->setWordWrap(true);
    cityNameLayout->addWidget(m_cityNameMessageLabel);

    m_mainLayout->addWidget(cityNameGroup);

    // ======Блок для единиц измерений======
    QGroupBox *m_unitsGroupBox = new QGroupBox("Units of measurement");
    QVBoxLayout *unitsLayout = new QVBoxLayout(m_unitsGroupBox);

    // Описание
    QLabel *unitsDescription = new QLabel("Select the measurement system to display the data:", m_unitsGroupBox);
    unitsDescription->setStyleSheet("QLabel { font-size: 14px; color: #555; }");
    unitsLayout->addWidget(unitsDescription);

    // Создаем группу кнопок
    m_unitsButtonGroup = new QButtonGroup();

    // Метрическая система (по умолчанию)
    m_metricRadioButton = new QRadioButton("Metric system", m_unitsGroupBox);
    m_metricRadioButton->setChecked(true);
    m_metricRadioButton->setStyleSheet(
        "QRadioButton {"
        "   font-size: 14px;"
        "   padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
        "QRadioButton:focus {"
        "   outline: none;"
        "   border: 2px solid #4A90E2;"
        "   border-radius: 4px;"
        "}"
    );

    // Имперская система
    m_imperialRadioButton = new QRadioButton("Imperial system", m_unitsGroupBox);
    m_imperialRadioButton->setStyleSheet(
        "QRadioButton {"
        "   font-size: 14px;"
        "   padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
        "QRadioButton:focus {"
        "   outline: none;"
        "   border: 2px solid #4A90E2;"
        "   border-radius: 4px;"
        "}"
    );

    // Добавляем кнопки в группу
    m_unitsButtonGroup->addButton(m_metricRadioButton, 0);    // ID 0 для метрической
    m_unitsButtonGroup->addButton(m_imperialRadioButton, 1);  // ID 1 для имперской

    // Добавляем кнопки в layout
    unitsLayout->addWidget(m_metricRadioButton);
    unitsLayout->addWidget(m_imperialRadioButton);

    // Добавляем пояснение
    QLabel *unitsNote = new QLabel("Note: This selection affects the display of temperature, wind speed, and pressure.", m_unitsGroupBox);
    unitsNote->setStyleSheet("QLabel { font-size: 12px; color: #777; font-style: italic; padding: 5px 0; }");
    unitsNote->setWordWrap(true);
    unitsLayout->addWidget(unitsNote);

    m_mainLayout->addWidget(m_unitsGroupBox);

    // ======Label для ошибок сети======
    m_networkErrorLabel = new QLabel("");
    m_networkErrorLabel->setWordWrap(true);
    m_networkErrorLabel->setAlignment(Qt::AlignCenter);
    m_networkErrorLabel->setMinimumHeight(30);
    m_mainLayout->addWidget(m_networkErrorLabel);


    // Добавляем растягивающийся элемент
    m_mainLayout->addStretch();


    // Кнопка запроса погоды
    m_requestWeatherButton = new QPushButton("Request the weather");
    m_requestWeatherButton->setMinimumHeight(50);
    m_requestWeatherButton->setEnabled(false); // Изначально отключена
    m_requestWeatherButton->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 12px 30px;"
        "   background-color: #50C878;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 6px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #40A060;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #348548;"
        "}"
        "QPushButton:focus {"
        "   outline: none;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #cccccc;"
        "   color: #666666;"
        "}"
    );
    
    m_mainLayout->addWidget(m_requestWeatherButton);

    // Устанавливаем стиль для всего виджета
    setStyleSheet(
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

void FirstPage::setupConnections() {
    // Подключаем кнопки к слотам
    connect(m_apiKeySaveButton, &QPushButton::clicked,
            this, &FirstPage::onApiKeySaveClicked);
    
    connect(m_cityNameSaveButton, &QPushButton::clicked,
            this, &FirstPage::onCityNameSaveClicked);

    connect(m_unitsButtonGroup, &QButtonGroup::idClicked,
          this, &FirstPage::onUnitsSystemChanged);
    
    connect(m_requestWeatherButton, &QPushButton::clicked,
            this, &FirstPage::onRequestWeatherClicked);
    
    // Очистка предупреждения при повторном заполнении
    connect(m_apiKeyLineEdit, &QLineEdit::textChanged, [this]() {
        m_apiKeyMessageLabel->clear();
        m_apiKeySaveButton->setEnabled(!m_apiKeyLineEdit->text().isEmpty());
    });
    
    connect(m_cityNameLineEdit, &QLineEdit::textChanged, [this]() {
        m_cityNameMessageLabel->clear();
        m_cityNameSaveButton->setEnabled(!m_cityNameLineEdit->text().isEmpty());
    });
    
    // Enter в поле ввода также триггерит сохранение
    connect(m_apiKeyLineEdit, &QLineEdit::returnPressed,
            this, &FirstPage::onApiKeySaveClicked);
    
    connect(m_cityNameLineEdit, &QLineEdit::returnPressed,
            this, &FirstPage::onCityNameSaveClicked);
}

void FirstPage::onApiKeySaveClicked() {
    QString apiKey = m_apiKeyLineEdit->text().trimmed();
    if (!apiKey.isEmpty()) {
        emit apiKeyChanged(apiKey);
    } else {
        showApiKeyValidationMessage("API key cannot be empty", false);
    }
}

void FirstPage::onCityNameSaveClicked() {
    QString cityName = m_cityNameLineEdit->text().trimmed();
    if (!cityName.isEmpty()) {
        emit cityNameChanged(cityName);
    } else {
        showCityNameValidationMessage("City name cannot be empty", false);
    }
}

void FirstPage::onUnitsSystemChanged() {
    int selectedId = m_unitsButtonGroup->checkedId();
    // 0 = метрическая, 1 = имперская
    bool isMetric = (selectedId == 0);
    emit unitsSystemChanged(isMetric);
}


void FirstPage::onRequestWeatherClicked() {
    if (m_apiKeyValid && m_cityNameValid) {
        emit requestWeatherData();
    }
}

void FirstPage::showApiKeyValidationMessage(const QString &message, bool isValid) {
    QString color = isValid ? "#50C878" : "#FF6B6B"; // Зеленый или красный
    m_apiKeyMessageLabel->setText(QString("<span style='color:%1;'>%2</span>").arg(color, message));
    m_apiKeyValid = isValid;
    
    // Проверяем, можно ли активировать кнопку запроса погоды
    enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
}

void FirstPage::showCityNameValidationMessage(const QString &message, bool isValid) {
    QString color = isValid ? "#50C878" : "#FF6B6B"; // Зеленый или красный
    m_cityNameMessageLabel->setText(QString("<span style='color:%1;'>%2</span>").arg(color, message));
    m_cityNameValid = isValid;
    
    // Проверяем, можно ли активировать кнопку запроса погоды
    enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
}

void FirstPage::showNetworkError(const QString &message) {
    m_networkErrorLabel->setText(message);
    m_networkErrorLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "   border-radius: 4px;"
        "   background-color: #FFEBEE;"
        "   color: #FF6B6B;"
        "   border: 1px solid #FFCDD2;"
        "}"
    );
}

void FirstPage::clearNetworkError() {
    m_networkErrorLabel->clear();
    m_networkErrorLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 12px;"
        "   padding: 8px;"
        "   margin: 5px 0;"
        "   border-radius: 4px;"
        "   background-color: transparent;"
        "   color: transparent;"
        "}"
    );
}

void FirstPage::enableWeatherRequestButton(bool enable) {
    m_requestWeatherButton->setEnabled(enable);
    
    if (enable) {
        m_requestWeatherButton->setText("Request the weather");
    } else {
        m_requestWeatherButton->setText("Fill in the fields");
    }
}