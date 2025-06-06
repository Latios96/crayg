#include "FilmWriter.h"
#include "image/Image.h"
#include "image/io/ImageWriters.h"

namespace crayg {

bool FilmWriter::writeFilm(const Film &film, const std::filesystem::path &path) {
    Image image(film.getFilmSpec().resolution);

    film.toImage(image);
    ImageWriters::writeImage(image, path);
}

}