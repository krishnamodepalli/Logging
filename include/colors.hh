

#ifndef COLORS_HH
#define COLORS_HH

#include <iostream>
#include <string>


// MACROS
#define RED "\033[91m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

#define RESET "\033[0m"


#define BOLD "\033[01m"
#define ITALIC "\033[03m"
#define UNDERLINE "\033[04m"


[[deprecated("Use the latter col::`color` instead")]]
inline const char * operator ""_red (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[91m%s\033[0m", str);
    return buffer;
}

[[deprecated("Use the latter col::`color` instead")]]
inline const char * operator ""_green (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[32m%s\033[0m", str);
    return buffer;
}

[[deprecated("Use the latter col::`color` instead")]]
inline const char * operator ""_yellow (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[33m%s\033[0m", str);
    return buffer;
}

[[deprecated("Use the latter col::`color` instead")]]
inline const char * operator ""_blue (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[34m%s\033[0m", str);
    return buffer;
}

[[deprecated("Use the latter col::`color` instead")]]
inline const char * operator ""_magenta (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[35m%s\033[0m", str);
    return buffer;
}

[[deprecated("Use the latter col::`color` instead" "h")]]
inline const char * operator ""_cyan (const char * str, std::size_t len) {
    auto buffer = new char[len + 19];
    sprintf(buffer, "\033[36m%s\033[0m", str);
    return buffer;
}

namespace col {
    // Foreground colors
    const char *black = "\033[30m";
    const char *red = "\033[91m";
    const char *green = "\033[32m";
    const char *yellow = "\033[33m";
    const char *blue = "\033[34m";
    const char *magenta = "\033[35m";
    const char *cyan = "\033[36m";
    const char *white = "\033[37m";

    // Background colors
    const char *bgblack = "\033[40m";
    const char *bgred = "\033[41m";
    const char *bggreen = "\033[42m";
    const char *bgyellow = "\033[43m";
    const char *bglue = "\033[44m";
    const char *bgmagenta = "\033[45m";
    const char *bgcyan = "\033[46m";
    const char *bgwhite = "\033[47m";

    // Formatting
    const char *bold = "\033[1m";
    const char *dim = "\033m[2m";
    const char *italic = "\033[3m";
    const char *underline = "\033[4m";
    const char *blink = "\033[5m";
    const char *hide = "\033[8m";

    // Reset Attributes
    const char *resetAll = "\033[0m";
    const char *unbold = "\033[22m";
    const char *unitalic = "\033[23m";
    const char *unline = "\033[24m";
    const char *unblink = "\033[25m";
    const char *unhide = "\033[28m";

}


#endif // COLORS_HH
