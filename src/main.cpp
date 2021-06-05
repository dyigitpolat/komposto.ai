//user headers
#include "demo_menu.hpp"
#include "demos.hpp"

//std headers
#include <iostream>

void hello_world()
{
    std::cout << "42." << std::endl;
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
    main_menu.add_menu_item({komposto::test_palette, "palette"});
    main_menu.add_menu_item({komposto::test_motif, "motif"});
    main_menu.add_menu_item({komposto::test_pattern_with_midi, "pattern midi"});
    main_menu.add_menu_item({
        komposto::test_pattern_duration, "pattern duration"});
    main_menu.add_menu_item({komposto::test_section_with_midi, "section midi"});
    main_menu.add_menu_item({
        komposto::test_composition_with_midi, "composition midi"});
    main_menu.add_menu_item({
        komposto::test_pythagorean_walk, "pythagorean"});
    main_menu.show();

    return 0;
}