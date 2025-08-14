#include "../vector.hpp"
#include "../types.hpp"
#include <string>

namespace Font{
    void initialize();
    void updateLocale(std::string _locale);
    void export_texture();
    void cleanup();
}