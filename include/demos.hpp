#pragma once

#include "harmonizer.hpp"
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
//static integer_t tuning_limit_p{11};
static integer_t palette_size{5};
static integer_t motif_beats{4};
static integer_t patterns_count{4};
static integer_t patterns_motif_count{2};

static harmonic_complexity_t harmonic_complexity{1.0};
static rhythmic_complexity_t rhythmic_complexity{0.3};

static Tuning tuning = Harmonizer::get_just_harmonic_minor_tuning();

static PaletteGenerator pg{base_test_tone};
static Palette p{pg.generate(tuning, palette_size)};
static RhythmicMotifGenerator rmg{};
static MotifGenerator mg{rmg};
static Motif m{mg.generate(p, motif_beats)};
static NotesToMidi n2m{};
static PatternGenerator pat_gen{MotifMutator{p}, mg };
static Pattern pat{pat_gen.generate(m, patterns_count)};
    
void test_reinit()
{
    pg = PaletteGenerator{base_test_tone};
    p = pg.generate(tuning, palette_size);
    rmg = RhythmicMotifGenerator{};
    mg = MotifGenerator{rmg};
    m = mg.generate(p, motif_beats);
    pat_gen = PatternGenerator{MotifMutator{p}, mg};
    pat = pat_gen.generate(m, patterns_motif_count);
    tuning = Harmonizer::get_just_harmonic_minor_tuning();
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

void test_pythagorean_walk()
{
    test_reinit();

    Tuning pyth{Harmonizer::get_pythagorean_tuning(8)};
    PaletteGenerator::sort_ratios(pyth.harmonics_);

    std::vector<Note> notes;
    Timing time{0,1};
    for(auto ratio : pyth.harmonics_)
    {
        notes.emplace_back(time, Tone(base_test_tone, ratio));
        std::cout << ratio.numerator_ << "/" << ratio.denominator_ << " ";
        time.start_ += 1;
    }
    std::cout << std::endl;
    
    n2m.generate_midi_file(notes, "test.mid");
}

}