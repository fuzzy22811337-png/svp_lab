#pragma once
#include <QObject>
#include <QDebug>

class WeatherModel {
public:
    //void print() const;

    inline double getTemperature() const
    {return m_temperature;}
    inline QString getDescription() const
    {return m_description;}
    inline double getWindSpeed() const
    {return m_windSpeed;}
    inline double getPressure() const
    {return m_pressure;}
    inline QString getCityName() const
    { return m_cityName;}
    inline QString getIconCode() const
    { return m_iconCode;}

    inline void setTemperature(const double& temperature)
    {m_temperature = temperature;}
    inline void setDescription(const QString& desc)
    {m_description = desc;}
    inline void setWindSpeed(const double& windSpeed)
    {m_windSpeed = windSpeed;}
    inline void setPressure(const double& pressure)
    {m_pressure = pressure;}
    inline void setCityName(const QString& name)
    {m_cityName = name;}
    inline void setIconCode(const QString& icon)
    {m_iconCode = icon;}

private:
    double m_temperature = 0.0;
    QString m_description = "";
    double m_windSpeed = 0.0;
    double m_pressure = 0.0;
    QString m_cityName = "";
    QString m_iconCode = ""; // для смены фона
};
