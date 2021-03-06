#include <SFML/Graphics.hpp>

#include <iostream>

#include "filter.hpp"
#include "filters/bw.hpp"
#include "filters/isolate.hpp"
#include "filters/reduce.hpp"
#include "filters/reducebw.hpp"
#include "filters/threshold.hpp"
#include "filters/dither.hpp"

inline void deleteAll(std::vector<filters::AbstractFilter*> filters) {
    for (auto &f : filters) {
        delete f;
    }
}

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image> <operation> [..operation args]\n";
        std::cerr << "Available operations:\n";
        std::cerr << "bw                    - Makes the image black-and-white.\n";
        std::cerr << "isolate <r|g|b>       - Isolates either the r, g or b channel.\n";
        std::cerr << "reduce <r> <g> <b>    - Reduces the colors to a subset of the original spectrum, with the three\n";
        std::cerr << "                        arguments being the reduction factor for each channel. WARNING: Slow!\n";
        std::cerr << "reducebw <factor>     - Makes the image black-and-white, but with a subset. Same rules apply\n";
        std::cerr << "                        like for reduce.\n";
        std::cerr << "threshold <r> <g> <b> - Eight colours, but with a specific threshold.\n";
        
        std::cerr << std::endl;
        return 1;
    }

    // Why are these here? I've noticed that it takes a shit ton of time to execute the program,
    // if the argument count isn't correct. Turns out, it's the constructors of these lot. Welp :shrug:

    sf::Image oldImage;
    sf::Image newImage;
    sf::Vector2u oldSize;
    sf::Vector2u newSize;
    sf::Texture tex;
    sf::Sprite spr;
    sf::Event event;
    std::string filterSelector;
    std::vector<filters::AbstractFilter*> allFilters;
    std::vector<filters::AbstractFilter*> filters;
    int currFilterI = 0;

    allFilters.push_back(new filters::BW);
    allFilters.push_back(new filters::Isolate);
    allFilters.push_back(new filters::Reduce);
    allFilters.push_back(new filters::ReduceBW);
    allFilters.push_back(new filters::Threshold);
    allFilters.push_back(new filters::Dither);

    bool found = false;
    int argCount = 0;

    for (int i = 2; i < argc; i++) {
        filters::AbstractFilter *filter;

        for (auto &f : allFilters) {
            if (f->getName() != argv[i]) continue;

            filter = f;
            found = true;
        }

        if (!found) {
            std::cerr << "Couldn't find a filter for operation " << argv[i] << "." << std::endl;
            deleteAll(allFilters);
            return 1;
        }

        argCount = filter->getArgCount();

        if (!filter->init(argCount, &argv[i + 1])) {
            deleteAll(allFilters);
            return 1;
        }

        filters.push_back(filter);
        i += argCount;
        found = false;
        std::cout << "Using filter " << filter->getName() << "." << std::endl;

    }

    if (!oldImage.loadFromFile(argv[1])) {
        std::cerr << "Couldn't load file " << argv[1] << " as an image." << std::endl;
        deleteAll(allFilters);
        return 1;
    }

    oldSize = oldImage.getSize();

    newSize.x = 800;
    newSize.y = oldSize.y * 800 / oldSize.x;

    if (newSize.y > 800) {
        newSize.x = newSize.x * 800 / newSize.y;
        newSize.y = 800;
    }

    newImage.create(oldSize.x, oldSize.y);
    tex.loadFromImage(newImage);
    spr.setTexture(tex);
    spr.setScale((float) newSize.x / (float) oldSize.x, (float) newSize.y / (float) oldSize.y);

    sf::RenderWindow window(sf::VideoMode(newSize.x, newSize.y), "ImgFilter");

    unsigned int y = 0;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                    break;
            }
        }

        window.clear();

        if (y < oldSize.y && currFilterI < filters.size()) {
            for (unsigned int i = 0; i < 8 && y < oldSize.y; i++) {
                for (unsigned int x = 0; x < oldSize.x; x++) {
                    newImage.setPixel(x, y, filters[currFilterI]->apply(oldImage.getPixel(x, y), x, y, &oldImage));
                }

                y++;
            }

            if (y == oldSize.y) {
                currFilterI++;
                y = 0;

                if (currFilterI == filters.size()) {
                    std::string path = argv[1];
                    std::size_t lastDot = path.find_last_of('.');
                    path = path.substr(0, lastDot) + "_reduced.png";
                    newImage.saveToFile(path);
                } else {
                    oldImage.copy(newImage, 0, 0);
                }
            }
        }

        tex.loadFromImage(newImage);

        window.draw(spr);

        window.display();
    }

    deleteAll(allFilters);

    return 0;
}