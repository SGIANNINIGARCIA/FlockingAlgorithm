/*
 * Vector2d.cpp
 *
 *  Created on: Feb 23, 2020
 *      Author: sandrogiannini
 */

#include "Vector2d.h"
#include <iostream>

Vector2d::Vector2d() {

    m_x = 0;
    m_y = 0;
}

Vector2d::Vector2d(double x, double y) {

    m_x = x;
    m_y = y;

}

Vector2d::~Vector2d() { }



double Vector2d::getX() {
    return m_x;
}

void Vector2d::setX(double x) {
    m_x = x;
}

double Vector2d::getY() {
    return m_y;
}

void Vector2d::setY(double y) {

    m_y = y;

}

Vector2d
Vector2d::operator+(const Vector2d &vec)  {

    Vector2d sum;
    sum.m_x = m_x + vec.m_x;
    sum.m_y = m_y + vec.m_y;

    return sum;
}

Vector2d
Vector2d::operator+=(const Vector2d &vec)  {

    Vector2d sum;
    sum.m_x = m_x + vec.m_x;
    sum.m_y = m_y + vec.m_y;

    return sum;
}

Vector2d
Vector2d::operator*(double x)  {

    Vector2d mul;
    mul.m_x = m_x * x;
    mul.m_y = m_y * x;

    return mul;
}

Vector2d
Vector2d::operator-(const Vector2d &vec)  {

    Vector2d def;
    def.m_x = m_x + (-vec.m_x);
    def.m_y = m_y + (-vec.m_y);

    return def;
}

void
Vector2d::makeUnitVector(){

    double magnitud = sqrt((m_x*m_x) + (m_y*m_y));

    m_x = (m_x/magnitud);
    m_y = (m_y/magnitud);

}

double
Vector2d::length(){
    return sqrt((m_x*m_x)+(m_y*m_y));
}

double
Vector2d::distance(Vector2d other){
    return sqrt(((m_x - other.getX())*(m_x - other.getX())) + ((m_y - other.getY())*(m_y - other.getY())));
}

Vector2d
Vector2d::operator/(double div){

    Vector2d def;
    def.m_x = m_x/div;
    def.m_y = m_y/div;

    return def;

}

