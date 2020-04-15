/*
 * Vector2d.h
 *
 *  Created on: Feb 23, 2020
 *      Author: sandrogiannini
 */

#ifndef SRC_VECTOR2D_H_
#define SRC_VECTOR2D_H_

#include <cmath>

class Vector2d {
private:
    double m_x;
    double m_y;

public:
    Vector2d();
    Vector2d(double x, double y);
    virtual ~Vector2d();
    Vector2d operator+(const Vector2d &vec);
    Vector2d operator+=(const Vector2d &vec);
    Vector2d operator-(const Vector2d &vec);
    Vector2d operator*(double);
    Vector2d operator/(double);
    void makeUnitVector();
    double getX();
    void setX(double x);
    double getY();
    void setY(double y);
    double length();
    double distance(Vector2d);
};

#endif /* SRC_VECTOR2D_H_ */
