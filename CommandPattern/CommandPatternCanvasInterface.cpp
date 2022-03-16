#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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

class Command {

public:

    virtual ~Command() {}

    virtual void execute() = 0;

};

class Button {

    Command* command;

public:

    Button(Command* new_command): command(new_command) {}

    void click() {

        command->execute();

    }

};

class AddShapeCommand: public Command {

    std::string shape_name;
    Canvas* canvas;

public:

    AddShapeCommand(const std::string & new_shape_name, Canvas* new_canvas): shape_name(new_shape_name), canvas(new_canvas) {}

    void execute() override {

        canvas->add_shape(shape_name);

    }

};

class ClearCommand: public Command {

    Canvas* canvas;

public:

    ClearCommand(Canvas* new_canvas): canvas(new_canvas) {}

    void execute() override {

        canvas->clear_all();

    }

};

std::string vector_to_string(const std::vector<std::string> & vect) {

    std::ostringstream buffer;

    for (const std::string & str: vect) {

        buffer << str << ", ";

    }

    return buffer.str();

}

int main() {

    Canvas* canvas = new Canvas();

    Button* add_triangle_button = new Button(new AddShapeCommand("Triangle", canvas));
    Button* add_square_button = new Button(new AddShapeCommand("Square", canvas));
    Button* clear_button = new Button(new ClearCommand(canvas));

    add_triangle_button->click();

    std::cout << "Current canvas state: " << vector_to_string(canvas->get_shapes()) << std::endl;

    add_square_button->click();
    add_square_button->click();
    add_triangle_button->click();

    std::cout << "Current canvas state: " << vector_to_string(canvas->get_shapes()) << std::endl;

    clear_button->click();

    std::cout << "Current canvas state: " << vector_to_string(canvas->get_shapes()) << std::endl;

    delete canvas;

    return 0;

}
