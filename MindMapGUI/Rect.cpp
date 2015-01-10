#include "Rect.h"

Rect::Rect()
{
    this->_x = 0;
    this->_y = 0;
    this->_height = 0;
    this->_width = 0;
}

void Rect::setPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}

void Rect::setSize(int width, int height)
{
    this->setWidth(width);
    this->setHeight(height);
}

void Rect::setX(int x)
{
    this->_x = x;
}

int Rect::getX()
{
    return this->_x;
}

void Rect::setY(int y)
{
    this->_y = y;
}

int Rect::getY()
{
    return this->_y;
}

void Rect::setWidth(int width)
{
    this->_width = width;
}

int Rect::getWidth()
{
    return this->_width;
}

void Rect::setHeight(int height)
{
    this->_height = height;
}

int Rect::getHeight()
{
    return this->_height;
}

string Rect::toString()
{
    string position = to_string(this->getX()) + ", " + to_string(this->getY());
    string rect = to_string(this->getWidth()) + ", " + to_string(this->getHeight());
    return position + " [ " + rect + " ]";
}

Rect::~Rect()
{
}