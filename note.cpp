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

char Note::getVelocity() const
{
    return velocity;
}

void Note::setPitch(const unsigned char _pitch)
{
    pitch = _pitch;
}

void Note::setDuration(const double _duration)
{
    duration = _duration;
}

void Note::incrementPitch(const unsigned char _pitch)
{
    pitch += _pitch;
}

void Note::incrementDuration(const double _duration)
{
    duration += _duration;
}

void Note::setVelocity(const char _velocity)
{
    velocity = _velocity;
}

bool Note::isRest() const
{
    return duration < 0;
}

Note::~Note()
{

}





