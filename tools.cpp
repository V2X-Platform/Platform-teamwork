#include "tools.h"
#include "stdafx.h"


double arg(pair<double,double> pos_vect)
{
    double x_cord = pos_vect.first;
    double y_cord = pos_vect.second;
    double radius = sqrt(pow(x_cord,2)+pow(y_cord,2));

    double cos_value = y_cord/radius;
    double sin_value = x_cord/radius;

    double result;

    if(x_cord>=0)
    {
        if(y_cord>=0)
            result = acos(cos_value);
        else
            result = asin(sin_value);
    }
    else
    {
        if(y_cord>=0)
            result = PI-acos(cos_value);
        else
            result = -PI-asin(sin_value);
    }
    return result;
}

double cac_length(pair<double,double> pos_vect)
{
    double x_cord = pos_vect.first;
    double y_cord = pos_vect.second;
    double radius = sqrt(pow(x_cord,2)+pow(y_cord,2));
    return radius;
}

double arg(double length,double hight)
{
    double radius=sqrt(pow(length,2)+pow(hight,2));
    return asin(length/radius);
}
