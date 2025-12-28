#ifndef COLORED_H
#define COLORED_H

#include <iostream>
using namespace std;

enum class Foreground : int {
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    RESET = 39,

    BRIGHT_BLACK = 90,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

enum class Background : int {
    BLACK = 40,
    RED = 41,
    GREEN = 42,
    YELLOW = 43,
    BLUE = 44,
    MAGENTA = 45,
    CYAN = 46,
    WHITE = 47,
    RESET = 49,

    BRIGHT_BLACK = 100,
    BRIGHT_RED = 101,
    BRIGHT_GREEN = 102,
    BRIGHT_YELLOW = 103,
    BRIGHT_BLUE = 104,
    BRIGHT_MAGENTA = 105,
    BRIGHT_CYAN = 106,
    BRIGHT_WHITE = 107
};

enum class Attribute : int {
    RESET = 0,
    BOLD = 1,
    DIM = 2,
    ITALIC = 3,
    UNDERLINE = 4,
    BLINK = 5,
    REVERSE = 7,
    HIDDEN = 8,
    STRIKETHROUGH = 9
};

struct Colored {
    Foreground fg_ = Foreground::RESET;
    Background bg_ = Background::RESET;
    Attribute attr_ = Attribute::RESET;
    int R = -1;
    int G = -1;
    int B = -1;
    
    Colored(Foreground fg, Background bg, Attribute attr) : fg_(fg), bg_(bg), attr_(attr) {};
    Colored(Foreground fg, Background bg) : fg_(fg), bg_(bg) {};
    Colored(Background bg, Attribute attr) : bg_(bg), attr_(attr) {};
    Colored(Foreground fg, Attribute attr) : fg_(fg), attr_(attr) {};
    Colored(Foreground fg) : fg_(fg) {};
    Colored(Background bg) : bg_(bg) {};
    Colored(Attribute attr) : attr_(attr) {};
    Colored(int r, int g, int b) : R(r), G(g), B(b) {};

    template <typename... Args>
    void print(Args&&... args) {
        // c++17+ is required (fold expression) 
        cout << parse();
        (cout << ... << args);
        cout << "\033[0m";
    }

    template <typename... Args>
    void println(Args&&... args) {
        // c++17+ is required (fold expression) 
        cout << parse();
        (cout << ... << args) << '\n';
        cout << "\033[0m";
    }

    string reset() const {
        return "\033[0m";
    }

    string bg_reset() const {
        return "\033[49m";
    }
    
    string parse() const {
        string code = "\033[";
        bool first = true;
        if (attr_ != Attribute::RESET) {
            code += to_string(static_cast<int>(attr_));
            first = false;
        }
        if (fg_ != Foreground::RESET) {
            if (!first) code += ";";
            code += to_string(static_cast<int>(fg_));
            first = false;
        }
        if (bg_ != Background::RESET) {
            if (!first) code += ";";
            code += to_string(static_cast<int>(bg_));
            first = false;
        }
        if (R != -1 || G != -1 || B != -1) {
            if (!first) code += ";";
            code += "38;2;" + to_string(R) + ";" + to_string(G) + ";" + to_string(B);
        }
        code += "m";
        return code;
    }
};

#endif // COLORED_H
