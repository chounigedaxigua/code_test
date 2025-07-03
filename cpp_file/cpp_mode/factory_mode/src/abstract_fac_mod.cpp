#include <iostream>
#include <memory>

// 抽象产品族
class Button {
public:
    virtual void paint() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void check() = 0;
    virtual ~Checkbox() = default;
};

// 具体产品
class WinButton : public Button {
public:
    void paint() override { std::cout << "Windows Button\n"; }
};

class MacButton : public Button {
public:
    void paint() override { std::cout << "Mac Button\n"; }
};

class WinCheckbox : public Checkbox {
public:
    void check() override { std::cout << "Windows Checkbox\n"; }
};

class MacCheckbox : public Checkbox {
public:
    void check() override { std::cout << "Mac Checkbox\n"; }
};

// 抽象工厂
class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

// 具体工厂
class WinFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WinButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WinCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};

// 使用示例
int main() {
    std::unique_ptr<GUIFactory> factory = std::make_unique<MacFactory>();
    
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();
    
    button->paint();    // Mac Button
    checkbox->check();  // Mac Checkbox
}