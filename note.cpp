#include "note.h"

Note::Note(const unsigned char _pitch, const double _duration) : pitch(_pitch), duration(_duration)
{

}

unsigned char Note::getPitch() const
{
    return pitch;
}

double Note::getDuration() const
{
    return duration;
}

void Note::setPitch(const unsigned char _pitch)
{
    pitch = _pitch;
}

void Note::setDuration(const double _duration)
{
    duration = _duration;
}

void Note::incrementDuration(const double _duration)
{
    duration += _duration;
}

bool Note::isRest() const
{
    return duration < 0;
}

Note::~Note()
{

}





