#include <iostream>
#include <memory>

// 产品接口
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

// 具体产品
class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing Circle\n"; }
};

class Rectangle : public Shape {
public:
    void draw() override { std::cout << "Drawing Rectangle\n"; }
};

// 简单工厂
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "Circle") return std::make_unique<Circle>();
        if (type == "Rectangle") return std::make_unique<Rectangle>();
        return nullptr;
    }
};

// 使用示例
int main() {
    auto circle = ShapeFactory::createShape("Circle");
    auto rect = ShapeFactory::createShape("Rectangle");
    
    circle->draw();  // Drawing Circle
    rect->draw();    // Drawing Rectangle
}