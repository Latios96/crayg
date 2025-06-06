#pragma once
#include "image/film/Film.h"
#include <filesystem>

namespace crayg {

class FilmWriter {
  public:
    static bool writeFilm(const Film &film, const std::filesystem::path &path);
};

}