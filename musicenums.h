#ifndef MUSICENUMS_H
#define MUSICENUMS_H

enum IntervalName
{
    UNISON = 0,
    MINOR_SECOND,
    MAJOR_SECOND,
    MINOR_THIRD,
    MAJOR_THIRD,
    PERFECT_FOURTH,
    AUGMENTED_FOURTH,
    PERFECT_FIFTH,
    MINOR_SIXTH,
    MAJOR_SIXTH,
    MINOR_SEVENTH,
    MAJOR_SEVENTH,
    PERFECT_OCTAVE,
    MINOR_NINTH,
    MAJOR_NINTH,
    MINOR_TENTH,
    MAJOR_TENTH,
    PERFECT_ELEVENTH,
    AUGMENTED_ELEVENTH,
    PERFECT_TWELFTH,
    MINOR_THIRTEENTH,
    MAJOR_THIRTEENTH,
    MINOR_FOURTEENTH,
    MAJOR_FOURTEENTH,
    PERFECT_FIFTEENTH
};

enum NoteName
{
    C = 0,
    Db,
    D,
    Eb,
    E,
    F,
    Gb,
    G,
    Ab,
    A,
    Bb,
    B
};

enum TimeSignatureMeter
{
    BINARY_METER,
    TERNARY_METER
};

enum FigureName
{
    WHOLE = 48,
    DOTTED_HALF = 36,
    HALF = 24,
    DOTTED_QUARTER = 18,
    QUARTER = 12,
    DOTTED_EIGHTH = 9,
    EIGHTH = 6,
    TRIPLET = 4,
    SIXTEENTH = 3
};

enum PulseMeasureValidFigures
{
    MEASURE_HALF = 1,
    MEASURE_QUARTER = 2,
    MEASURE_EIGHTH = 3,
    MEASURE_SIXTEENTH = 4,
    MEASURE_THIRTYSECOND = 5
};

#endif // MUSICENUMS_H
