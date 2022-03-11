#include <vector>
#include <string>

class Canvas {

    std::vector<std::string> shapes;

public:
    
    Canvas() {}

    void add_shape(const std::string & new_shape) {
        
        shapes.push_back(new_shape);
        
    }

    void clear_all() {

        shapes.clear();

    }

    std::vector<std::string> get_shapes() {

        return shapes;

    }

};

class Button {

public:
    
    virtual ~Button();
    virtual void click() = 0;

};

class AddTriangleButton: public Button {

    Canvas* canvas;

public:

    AddTriangleButton(Canvas* new_canvas): canvas(new_canvas) {}
    
    void click() override {
        
        canvas->add_shape("Triangle");
        
    }

};

class AddSquareButton: public Button {

    Canvas* canvas;

public:

    AddSquareButton(Canvas* new_canvas): canvas(new_canvas) {}
    
    void click() override {

        canvas->add_shape("Square");

    }

};

class ClearButton: public Button {

    Canvas* canvas;

public:
    
    ClearButton(Canvas* new_canvas): canvas(new_canvas) {}

    void click() override {

        canvas->clear_all();

    }

};

int main () {

    return 0;

}