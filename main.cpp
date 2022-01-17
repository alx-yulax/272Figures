#include <iostream>
#include <cmath>
#include <assert.h>

enum class Colors {
    NONE,
    RED,
    BLUE,
    GREEN,
    PINK
};

class XY {
    double x;
    double y;
public:
    XY(double inX, double inY) : x(inX), y(inY) {
        assert((inX >= 0) && (inY >= 0));
    }
};

class Figure {
    XY *center;
    Colors color;
    double square = 0;
    double circumscribingRectangle = 0;
public:
    Figure(XY *inCenter = nullptr, Colors inColor = Colors::NONE) : center(inCenter), color(inColor) {
        assert(inCenter != nullptr);
    }

    ~Figure() {
        delete center;
    };

    void setSquare(double inSquare) {
        if (inSquare > 0) {
            square = inSquare;
        }
    }

    void setCircumscribingRectangle(double inCircumscribingRectangle) {
        if (inCircumscribingRectangle > 0) {
            circumscribingRectangle = inCircumscribingRectangle;
        }
    }

    std::string ShowColor() {
        if (color == Colors::NONE) {
            return "NONE";
        } else if (color == Colors::PINK) {
            return "PINK";
        } else if (color == Colors::GREEN) {
            return "GREEN";
        } else if (color == Colors::BLUE) {
            return "BLUE";
        } else if (color == Colors::RED) {
            return "RED";
        }
    }

    void show() {
        std::cout << "Square: " << square << "  circumscribing rectangle: " << circumscribingRectangle << "  color: "
                  << ShowColor() << std::endl;
    }
};

class Circle : public Figure {
    double radius;
public:
    Circle(double inRadius, Colors inColor, XY *inCenter) : Figure(inCenter, inColor), radius(inRadius) {
        assert(inRadius > 0);
        setSquare(M_PI * std::pow(radius, 2));
        setCircumscribingRectangle(std::pow(radius * 2, 2));
    }
};

class Triangle : public Figure {
    double ribLength;
public:
    Triangle(double inRibLength, Colors inColor, XY *inCenter) : Figure(inCenter, inColor), ribLength(inRibLength) {
        assert(inRibLength > 0);
        setSquare((std::pow(ribLength, 2) * std::sqrt(3)) / 4);
        setCircumscribingRectangle(((ribLength * std::sqrt(3)) / 2) * ribLength);
    }
};

class Square : public Figure {
    double ribLength;
public:
    Square(double inRibLength, Colors inColor, XY *inCenter) : Figure(inCenter, inColor), ribLength(inRibLength) {
        assert(inRibLength > 0);
        double square = std::pow(ribLength, 2);
        setSquare(square);
        setCircumscribingRectangle(square);
    }
};

class Rectangle : public Figure {
    double width;
    double height;
public:
    Rectangle(double inWidth, double inHeight, Colors inColor, XY *inCenter) : Figure(inCenter, inColor),
                                                                               width(inWidth), height(inHeight) {
        assert((inWidth > 0) && (inHeight > 0));
        double square = width * height;
        setSquare(square);
        setCircumscribingRectangle(square);
    }
};

Colors colorSelection() {
    Colors colorSelected;
    std::string color;
    std::cout << "Input color (red,blue,green,pink or none):  ";
    std::cin >> color;
    if (color == "red") {
        colorSelected = Colors::RED;
    } else if (color == "blue") {
        colorSelected = Colors::BLUE;
    } else if (color == "green") {
        colorSelected = Colors::GREEN;
    } else if (color == "pink") {
        colorSelected = Colors::PINK;
    } else {
        colorSelected = Colors::NONE;
    }
    return colorSelected;
}

XY *centerCoordinatesSelection() {
    double x, y;
    std::cout << "Input the coordinates of the center (x y)";
    std::cin >> x >> y;
    XY *coordinates = new XY(x, y);
    return coordinates;
}

int main() {

    std::string figure;
    do {
        std::cout << "Input the name of the shape: ";
        std::cin >> figure;
        if (figure == "circle" || figure == "square" || figure == "triangle" || figure == "rectangle") {
            XY *coordinates = centerCoordinatesSelection();
            Colors color = colorSelection();

            if (figure == "circle") {
                std::cout << "Input radius: ";
                double radius;
                std::cin >> radius;

                Circle *circle = new Circle(radius, color, coordinates);
                circle->show();
                delete circle;
            } else if (figure == "square") {
                std::cout << "Input rib length: ";
                double ribLengthSquare;
                std::cin >> ribLengthSquare;

                Square *square = new Square(ribLengthSquare, color, coordinates);
                square->show();
                delete square;
            } else if (figure == "triangle") {
                std::cout << "Input rib length: ";
                double ribLength;
                std::cin >> ribLength;

                Triangle *triangle = new Triangle(ribLength, color, coordinates);
                triangle->show();
                delete triangle;
            } else if (figure == "rectangle") {
                std::cout << "Input width and height (10 50): ";
                double width, height;
                std::cin >> width >> height;

                Rectangle *rectangle = new Rectangle(width, height, color, coordinates);
                rectangle->show();
                delete rectangle;
            }
        }

    } while (figure != "exit");


    return 0;
}
