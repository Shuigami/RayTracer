#include "image/image.hh"
#include "image/color.hh"
#include "logger/logger.hh"

#include <fstream>

Image::Image(int height, int width, std::list<Color*> pixels)
: height_(height), width_(width), pixels_(pixels)
{
}

void Image::image_to_ppm(std::string path)
{
    Logger::getInstance().log(Logger::Level::INFO, "Writing image to file...");

    std::ofstream myfile;
    myfile.open (path);

    myfile << "P3" << std::endl << std::endl
        << width_ << " " << height_ << std::endl << "255" << std::endl;

    int i = 0;
    for (auto p : pixels_)
    {
        myfile << p->getR() << " " << p->getG() << " " << p->getB() << " ";
        i++;

        if (i == width_)
        {
            myfile << std::endl;
            i = 0;
        }
    }

    myfile.close();

    Logger::getInstance().log(Logger::Level::INFO, "Image written to file.");
}
