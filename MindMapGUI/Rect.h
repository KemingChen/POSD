#pragma once

class Rect
{
    private:
        int _x;
        int _y;
        int _width;
        int _height;

    public:
        Rect();
        void setPosition(int x, int y);
        void setSize(int width, int height);

        void setX(int x);
        int getX();

        void setY(int y);
        int getY();

        void setWidth(int width);
        int getWidth();

        void setHeight(int height);
        int getHeight();
        ~Rect();
};