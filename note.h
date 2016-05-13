#ifndef NOTE_H
#define NOTE_H

class Note
{
    public:
        Note(unsigned char _pitch = 0, float _duration = 0);
        unsigned char getPitch();
        float getDuration();
        void setPitch(unsigned char _pitch);
        void setDuration(float _duration);
        void incrementDuration(float _duration);
        bool isRest();
        ~Note();

    private:
        unsigned char pitch;
        float duration;
};

#endif
