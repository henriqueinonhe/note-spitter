#include "note.h"

Note::Note(unsigned char _pitch, float _duration) : pitch(_pitch), duration(_duration)
{

}

unsigned char Note::getPitch()
{
    return pitch;
}

float Note::getDuration()
{
    return duration;
}

void Note::setPitch(unsigned char _pitch)
{
    pitch = _pitch;
}

void Note::setDuration(float _duration)
{
    duration = _duration;
}

void Note::incrementDuration(float _duration)
{
    duration += _duration;
}

bool Note::isRest()
{
    return duration < 0;
}

Note::~Note()
{

}





