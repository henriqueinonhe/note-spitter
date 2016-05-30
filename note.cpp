#include "note.h"

Note::Note(const unsigned char _pitch, const double _duration, const char _velocity) : pitch(_pitch), duration(_duration), velocity(_velocity)
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

void Note::operator =(const Note &_note)
{
    pitch = _note.getPitch();
    duration = _note.getDuration();
    velocity = _note.getVelocity();
}

Note::~Note()
{

}




