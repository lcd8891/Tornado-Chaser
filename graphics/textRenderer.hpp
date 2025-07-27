#include "../vector.hpp"
#include "../types.hpp"
#include <string>

namespace TextRenderer{
    void initialize();
    void draw();
    void updateLocale(std::string _locale);
    void export_texture();
    void cleanup();
}