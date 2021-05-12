#pragma once

#include "palette_generator.hpp"
#include "motif_generator.hpp"
#include "palette_generator.hpp"
#include "section_generator.hpp"
#include "composition_generator.hpp"
#include "pattern_mutator.hpp"
#include "rhythmic_motif_generator.hpp"
#include "notes_to_midi.hpp"

#include <iostream>
#include <random>

namespace komposto
{

static frequency_t base_test_tone{110};
static integer_t tuning_limit_p{11};
static integer_t palette_size{5};
static integer_t motif_beats{4};
static integer_t patterns_count{4};
static integer_t patterns_motif_count{2};

static harmonic_complexity_t harmonic_complexity{0.3};
static rhythmic_complexity_t rhythmic_complexity{0.3};

static PaletteGenerator pg{base_test_tone};
static Palette p{pg.generate(tuning_limit_p, palette_size)};
static RhythmicMotifGenerator rmg{};
static MotifGenerator mg{rmg};
static Motif m{mg.generate(p, motif_beats)};
static NotesToMidi n2m{};
static PatternGenerator pat_gen{MotifMutator{p}, mg };
static Pattern pat{pat_gen.generate(m, patterns_count)};
    
void test_reinit()
{
    pg = PaletteGenerator{base_test_tone};
    p = pg.generate(tuning_limit_p, palette_size);
    rmg = RhythmicMotifGenerator{};
    mg = MotifGenerator{rmg};
    m = mg.generate(p, motif_beats);
    pat_gen = PatternGenerator{MotifMutator{p}, mg};
    pat = pat_gen.generate(m, patterns_motif_count);
}

void test_palette()
{
    test_reinit();

    for( Tone& t : p.tones_)
    {
        std::cout << t.ratio_.numerator_ << "/" <<
            t.ratio_.denominator_ << ", ";
    }
    std::cout << std::endl;
}

void test_motif()
{
    test_reinit();

    for( Note& n : m.notes_)
    {
        std::cout << "(" << n.tone_.ratio_.numerator_ << "/" <<
            n.tone_.ratio_.denominator_ << " : ";

        std::cout << n.timing_.duration_ << "), ";
    }

    std::cout << std::endl;
}

void test_pattern_with_midi()
{
    test_reinit();

    n2m.generate_midi_file(pat.get_notes(), "test.mid");
}

void test_pattern_duration()
{
    test_reinit();

    std::cout << pat.get_duration() << std::endl;
}

void test_section_with_midi()
{
    test_reinit();

    SectionGenerator sec_gen = SectionGenerator{PatternMutator{p}, pat_gen, mg};
    Section s = sec_gen.generate(
        p, motif_beats, patterns_count, patterns_motif_count);

    n2m.generate_midi_file(s.get_notes(), "test.mid");
}

void test_composition_with_midi()
{
    test_reinit();

    SectionGenerator sec_gen = SectionGenerator{PatternMutator{p}, pat_gen, mg};
    Section s = sec_gen.generate(
        p, motif_beats, patterns_count, patterns_motif_count);

    CompositionGenerator comp_gen = CompositionGenerator{sec_gen, pg};
    Composition comp = comp_gen.generate(
        harmonic_complexity, rhythmic_complexity);

    n2m.generate_midi_file(comp.get_notes(), "test.mid");
}

}