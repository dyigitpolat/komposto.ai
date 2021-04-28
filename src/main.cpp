//std headers
#include <iostream> //std::cout, std::endl
#include <random>

//user headers
#include "palette_generator.hpp"
#include "demo_menu.hpp"

void hello_world()
{
    std::cout << "42." << std::endl;
}

void test_random()
{
    double gamma;
    static std::default_random_engine generator;

    gamma = 3.5;
    std::exponential_distribution<double> distribution(gamma);
    std::cout << "gamma: " << gamma << std::endl;
    for (int i=0; i<10; ++i) {
        std::cout << static_cast<int>(distribution(generator)*10) << " ";
    }
    std::cout << std::endl;
}

namespace komposto
{

void test_palette()
{
    PaletteGenerator pg;
    Palette p{pg.generate()};

    for( Tone& t : p.tones)
    {
        std::cout << t.ratio_.numerator_ << "/" <<
            t.ratio_.denominator_ << ", ";
    }
    std::cout << std::endl;
}

}

int main()
{
    //----------------------------------------------------//
    std::cout << "- - - - - - - - - - - - - -" << std::endl;
    std::cout << "- - - - - - - - - - - - - -" << std::endl;
    std::cout << "-         Welcome!        -" << std::endl;
    std::cout << "  Demo Program Entry Point " << std::endl;
    std::cout << "- - - - - - - - - - - - - -" << std::endl;
    std::cout << "- - - - - - - - - - - - - -" << std::endl;
    //----------------------------------------------------//

    DemoMenu main_menu("MAIN MENU");
    main_menu.add_menu_item({hello_world, "Hello World!"});
    main_menu.add_menu_item({test_random, "exponential random"});
    main_menu.add_menu_item({komposto::test_palette, "palette"});
    main_menu.show();

    return 0;
}