#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>

#include "first_page.hpp"
#include "MainWindow.hpp"
#include "src/data/model/weather_model.hpp"
#include "src/data/datasource/weather_data_source.hpp"
#include "src/data/repository/repository.hpp"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    // Создаем главное окно
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
