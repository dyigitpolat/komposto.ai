//user headers
#include "demo_menu.hpp"
#include "demos.hpp"

//std headers
#include <iostream> //std::cout, std::endl
#include <random>

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
    main_menu.add_menu_item({komposto::test_motif, "motif"});
    main_menu.add_menu_item({komposto::test_pattern_with_midi, "pattern midi"});
    main_menu.add_menu_item({
        komposto::test_pattern_duration, "pattern duration"});
    main_menu.add_menu_item({komposto::test_section_with_midi, "section midi"});
    main_menu.add_menu_item({
        komposto::test_composition_with_midi, "composition midi"});
    main_menu.show();

    return 0;
}