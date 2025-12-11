#include "first_page.hpp"
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QRegularExpressionValidator>

FirstPage::FirstPage(QWidget *parent)
    : QWidget(parent)
    , m_apiKeyValid(false)
    , m_cityNameValid(false)
{
    setupUI();
    setupConnections();
    show();
}

void FirstPage::setupUI()
{
    // Настройка основного layout
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setContentsMargins(30, 30, 30, 30);

    // Добавляем заголовок
    QLabel *titleLabel = new QLabel("Настройка параметров погоды", this);
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; color: #333; }");
    titleLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(titleLabel);

    // Добавляем разделитель
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("background-color: #ccc;");
    m_mainLayout->addWidget(separator);

    // Секция для API ключа
    QGroupBox *apiKeyGroup = new QGroupBox("API Key", this);
    QVBoxLayout *apiKeyLayout = new QVBoxLayout(apiKeyGroup);

    // Надпись для API ключа
    m_apiKeyLabel = new QLabel("Введите свой ключ API:", apiKeyGroup);
    m_apiKeyLabel->setStyleSheet("QLabel { font-size: 14px; color: #555; }");
    apiKeyLayout->addWidget(m_apiKeyLabel);

    // Layout для строки ввода и кнопки
    QHBoxLayout *apiKeyInputLayout = new QHBoxLayout();
    
    m_apiKeyLineEdit = new QLineEdit(apiKeyGroup);
    m_apiKeyLineEdit->setPlaceholderText("Введите API ключ от OpenWeatherMap");
    m_apiKeyLineEdit->setEchoMode(QLineEdit::Password); // Скрываем ввод для безопасности
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
    
    m_apiKeySaveButton = new QPushButton("Сохранить", apiKeyGroup);
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

    // Секция для названия города
    QGroupBox *cityNameGroup = new QGroupBox("Город", this);
    QVBoxLayout *cityNameLayout = new QVBoxLayout(cityNameGroup);

    // Надпись для названия города
    m_cityNameLabel = new QLabel("Введите название города:", cityNameGroup);
    m_cityNameLabel->setStyleSheet("QLabel { font-size: 14px; color: #555; }");
    cityNameLayout->addWidget(m_cityNameLabel);

    // Layout для строки ввода и кнопки
    QHBoxLayout *cityNameInputLayout = new QHBoxLayout();
    
    m_cityNameLineEdit = new QLineEdit(cityNameGroup);
    m_cityNameLineEdit->setPlaceholderText("Например: Moscow или New York");
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
    
    // Установка валидатора для ввода названия города
    QRegularExpression cityNameRegex("^[A-Za-z]+(?:[.,\\s\\-'][A-Za-z]+)*$");
    QValidator *cityNameValidator = new QRegularExpressionValidator(cityNameRegex, this);
    m_cityNameLineEdit->setValidator(cityNameValidator);
    
    m_cityNameSaveButton = new QPushButton("Сохранить", cityNameGroup);
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

    //Блок для единиц измерений
    QGroupBox *m_unitsGroupBox = new QGroupBox("Единицы измерения", this);
    QVBoxLayout *unitsLayout = new QVBoxLayout(m_unitsGroupBox);

    // Описание
    QLabel *unitsDescription = new QLabel("Выберите систему измерения для отображения данных:", m_unitsGroupBox);
    unitsDescription->setStyleSheet("QLabel { font-size: 14px; color: #555; }");
    unitsLayout->addWidget(unitsDescription);

    // Создаем группу кнопок
    m_unitsButtonGroup = new QButtonGroup(this);

    // Метрическая система (по умолчанию)
    m_metricRadioButton = new QRadioButton("Метрическая система", m_unitsGroupBox);
    m_metricRadioButton->setChecked(true);  // По умолчанию выбрана метрическая система
    m_metricRadioButton->setStyleSheet(
        "QRadioButton {"
        "   font-size: 14px;"
        "   padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
    );

    // Имперская система (США)
    m_imperialRadioButton = new QRadioButton("Имперская система", m_unitsGroupBox);
    m_imperialRadioButton->setStyleSheet(
        "QRadioButton {"
        "   font-size: 14px;"
        "   padding: 8px;"
        "}"
        "QRadioButton::indicator {"
        "   width: 20px;"
        "   height: 20px;"
        "}"
    );

    // Добавляем кнопки в группу
    m_unitsButtonGroup->addButton(m_metricRadioButton, 0);    // ID 0 для метрической
    m_unitsButtonGroup->addButton(m_imperialRadioButton, 1);  // ID 1 для имперской

    // Добавляем кнопки в layout
    unitsLayout->addWidget(m_metricRadioButton);
    unitsLayout->addWidget(m_imperialRadioButton);

    // Добавляем пояснение
    QLabel *unitsNote = new QLabel("Примечание: Этот выбор влияет на отображение температуры, скорости ветра и давления.", m_unitsGroupBox);
    unitsNote->setStyleSheet("QLabel { font-size: 12px; color: #777; font-style: italic; padding: 5px 0; }");
    unitsNote->setWordWrap(true);
    unitsLayout->addWidget(unitsNote);

    m_mainLayout->addWidget(m_unitsGroupBox);

    // Добавляем растягивающийся элемент
    m_mainLayout->addStretch();

    // Кнопка запроса погоды
    m_requestWeatherButton = new QPushButton("Запросить погоду", this);
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

void FirstPage::setupConnections()
{
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

void FirstPage::onApiKeySaveClicked()
{
    QString apiKey = m_apiKeyLineEdit->text().trimmed();
    if (!apiKey.isEmpty()) {
        emit apiKeyChanged(apiKey);
    } else {
        showApiKeyValidationMessage("API key cannot be empty", false);
    }
}

void FirstPage::onCityNameSaveClicked()
{
    QString cityName = m_cityNameLineEdit->text().trimmed();
    if (!cityName.isEmpty()) {
        emit cityNameChanged(cityName);
    } else {
        showCityNameValidationMessage("City name cannot be empty", false);
    }
}

void FirstPage::onUnitsSystemChanged() {
    // Получаем ID выбранной кнопки
    int selectedId = m_unitsButtonGroup->checkedId();

    // 0 = метрическая, 1 = имперская
    bool isMetric = (selectedId == 0);

    // Эмитируем сигнал с выбранной системой
    emit unitsSystemChanged(isMetric);
}


void FirstPage::onRequestWeatherClicked()
{
    if (m_apiKeyValid && m_cityNameValid) {
        emit requestWeatherData();
    }
}

QString FirstPage::getApiKey() const
{
    return m_apiKeyLineEdit->text().trimmed();
}

QString FirstPage::getCityName() const
{
    return m_cityNameLineEdit->text().trimmed();
}

void FirstPage::showApiKeyValidationMessage(const QString &message, bool isValid)
{
    QString color = isValid ? "#50C878" : "#FF6B6B"; // Зеленый или красный
    m_apiKeyMessageLabel->setText(QString("<span style='color:%1;'>%2</span>").arg(color, message));
    m_apiKeyValid = isValid;
    
    // Проверяем, можно ли активировать кнопку запроса погоды
    enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
}

void FirstPage::showCityNameValidationMessage(const QString &message, bool isValid)
{
    QString color = isValid ? "#50C878" : "#FF6B6B"; // Зеленый или красный
    m_cityNameMessageLabel->setText(QString("<span style='color:%1;'>%2</span>").arg(color, message));
    m_cityNameValid = isValid;
    
    // Проверяем, можно ли активировать кнопку запроса погоды
    enableWeatherRequestButton(m_apiKeyValid && m_cityNameValid);
}

bool FirstPage::isMetricSystem() const {
    // Возвращает true, если выбрана метрическая система
    return m_metricRadioButton->isChecked();
}

void FirstPage::enableWeatherRequestButton(bool enable)
{
    m_requestWeatherButton->setEnabled(enable);
    
    if (enable) {
        m_requestWeatherButton->setText("Запросить погоду");
    } else {
        m_requestWeatherButton->setText("Заполните поля");
    }
}