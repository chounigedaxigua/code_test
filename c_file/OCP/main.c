#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// 前置声明，因为Circle和Rectangle都会用到Shape
struct Shape;

// 定义函数指针类型，代表“绘制”行为
typedef void (*DrawFunc)(struct Shape* shape);
// 定义函数指针类型，代表“计算面积”行为
typedef double (*AreaFunc)(struct Shape* shape);

// “图形”接口结构体
// 它包含数据（坐标）和行为（函数指针）
struct Shape {
    int x, y;           // 图形的位置（数据）
    DrawFunc draw;      // 指向具体的绘制函数（行为的抽象）
    AreaFunc area;      // 指向具体的面积计算函数（行为的抽象）
};

// 统一的操作函数，高层模块只会调用这些函数
void shape_draw(struct Shape* shape);
double shape_area(struct Shape* shape);

// 圆形特有的数据
struct CircleData {
    struct Shape base; // 必须作为第一个成员，以便进行“继承”转换
    double radius;
};

// 圆形的具体绘制实现
static void circle_draw(struct Shape* shape) {
    // 通过强制类型转换，将通用Shape指针转为具体的CircleData指针
    struct CircleData* circle = (struct CircleData*)shape;
    printf("Drawing a Circle at (%d, %d) with radius %.2f\n",
           shape->x, shape->y, circle->radius);
}

// 圆形的具体面积计算实现
static double circle_area(struct Shape* shape) {
    struct CircleData* circle = (struct CircleData*)shape;
    return M_PI * circle->radius * circle->radius;
}

// “工厂函数”：创建并初始化一个圆形实例
// 这个函数封装了创建细节，对使用者透明
struct Shape* create_circle(int x, int y, double radius) {
    struct CircleData* circle = malloc(sizeof(struct CircleData));
    circle->base.x = x;
    circle->base.y = y;
    circle->radius = radius;
    // 关键：将具体实现的函数赋值给接口的函数指针
    circle->base.draw = circle_draw;
    circle->base.area = circle_area;
    return (struct Shape*)circle; // 返回抽象的Shape指针
}

// 矩形特有的数据
struct RectangleData {
    struct Shape base; // 同样，基类作为第一个成员
    double width, height;
};

// 矩形的具体绘制实现
static void rectangle_draw(struct Shape* shape) {
    struct RectangleData* rect = (struct RectangleData*)shape;
    printf("Drawing a Rectangle at (%d, %d) with width %.2f and height %.2f\n",
           shape->x, shape->y, rect->width, rect->height);
}

// 矩形的具体面积计算实现
static double rectangle_area(struct Shape* shape) {
    struct RectangleData* rect = (struct RectangleData*)shape;
    return rect->width * rect->height;
}

// “工厂函数”：创建并初始化一个矩形实例
struct Shape* create_rectangle(int x, int y, double w, double h) {
    struct RectangleData* rect = malloc(sizeof(struct RectangleData));
    rect->base.x = x;
    rect->base.y = y;
    rect->width = w;
    rect->height = h;
    rect->base.draw = rectangle_draw;
    rect->base.area = rectangle_area;
    return (struct Shape*)rect;
}

// 这个函数是绘图的核心，它只接收抽象的Shape指针
// 如果要添加新图形，这个函数一行都不需要改！
void draw_all_shapes(struct Shape** shapes, int count) {
    printf("--- Drawing All Shapes ---\n");
    for (int i = 0; i < count; i++) {
        shape_draw(shapes[i]); // 多态调用！
        printf("Area: %.2f\n\n", shape_area(shapes[i]));
    }
}

int main() {
    // 使用工厂函数创建具体图形对象
    struct Shape* my_circle = create_circle(10, 20, 5.0);
    struct Shape* my_rect = create_rectangle(30, 40, 10.0, 15.0);

    struct Shape* shapes[] = {my_circle, my_rect};
    int shape_count = sizeof(shapes) / sizeof(shapes[0]);

    // 调用高层函数，它不关心具体是什么图形
    draw_all_shapes(shapes, shape_count);

    // 清理内存
    free(my_circle);
    free(my_rect);

    return 0;
}