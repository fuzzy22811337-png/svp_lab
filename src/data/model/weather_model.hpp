#pragma once
#include <QString>

class WeatherModel {
public:
    WeatherModel() = default;
    ~WeatherModel() = default;

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

    inline void setTemperature(const double& temperature)
    {m_temperature = temperature;}
    inline void setDescription(const QString& description)
    {m_description = description;}
    inline void setWindSpeed(const double& windSpeed)
    {m_windSpeed = windSpeed;}
    inline void setPressure(const double& pressure)
    {m_pressure = pressure;}
    inline void setCityName(const QString& cityName)
    {m_cityName = cityName;}

private:
    double m_temperature = 0.0;
    QString m_description = "";
    double m_windSpeed = 0.0;
    double m_pressure = 0.0;
    QString m_cityName = "";
};
