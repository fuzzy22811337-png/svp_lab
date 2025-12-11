#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <locale>
#include <windows.h>

#include "first_page.hpp"
#include "MainWindow.hpp"
#include "src/data/model/weather_model.hpp"
#include "src/data/datasource/weather_data_source.hpp"
#include "src/data/repository/repository.hpp"


int main(int argc, char *argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");

    QApplication app(argc, argv);
    // Создаем главное окно
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
    /*Repository repo = Repository(new WeatherDataSource());
    repo.isMetric(true);
    repo.setApiKey("c23075e6a49a1e13eb5986d1fa354d98");
    repo.setCityName("Moscow");
    repo.fetchWeatherData();
    repo.setCityName("London");
    repo.fetchWeatherData();*/


    return app.exec();
}
