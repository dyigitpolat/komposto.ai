//std headers
#include <iostream> //std::cout, std::endl
#include <random>

//user headers
#include "palette_generator.hpp"
#include "motif_generator.hpp"
#include "pattern_generator.hpp"
#include "rhythmic_motif_generator.hpp"
#include "notes_to_midi.hpp"
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
    PaletteGenerator pg{440};
    Palette p{pg.generate(7, 5)};

    for( Tone& t : p.tones_)
    {
        std::cout << t.ratio_.numerator_ << "/" <<
            t.ratio_.denominator_ << ", ";
    }
    std::cout << std::endl;
}

void test_motif()
{
    PaletteGenerator pg{440};
    Palette p{pg.generate(11, 5)};

    RhythmicMotifGenerator rmg{};

    MotifGenerator mg{rmg};
    Motif m{mg.generate(p, 4)};

    for( Note& n : m.notes_)
    {
        std::cout << "(" << n.tone_.ratio_.numerator_ << "/" <<
            n.tone_.ratio_.denominator_ << " : ";

        std::cout << n.timing_.duration_ << "), ";
    }

    std::cout << std::endl;
}

void test_midi()
{
    PaletteGenerator pg{440};
    Palette p{pg.generate(11, 10)};

    RhythmicMotifGenerator rmg{};

    MotifGenerator mg{rmg};
    Motif m{mg.generate(p, 4)};

    NotesToMidi n2m{};
    n2m.generate_midi_file(m.notes_, "test.mid");
}

void test_pattern_with_midi()
{
    PaletteGenerator pg{440};
    Palette p{pg.generate(7, 5)};

    RhythmicMotifGenerator rmg{};
    
    MotifGenerator mg{rmg};
    Motif m{mg.generate(p, 4)};

    Pattern pat{ 
        PatternGenerator{
            MotifMutator{p}, mg 
            }.generate(m)
    };
    
    NotesToMidi n2m{};
    n2m.generate_midi_file(pat.get_notes(), "test.mid");
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
    main_menu.add_menu_item({komposto::test_motif, "motif"});
    main_menu.add_menu_item({komposto::test_midi, "midi"});
    main_menu.add_menu_item({komposto::test_pattern_with_midi, "pattern midi"});
    main_menu.show();

    return 0;
}