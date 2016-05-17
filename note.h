#ifndef NOTE_H
#define NOTE_H

class Note
{
    public:
        Note(const unsigned char _pitch = 0, const double _duration = 0);
        unsigned char getPitch() const;
        double getDuration() const;
        void setPitch(const unsigned char _pitch);
        void setDuration(const double _duration);
        void incrementDuration(const double _duration);
        bool isRest() const;
        ~Note();

    private:
        unsigned char pitch;
        double duration;
};

#endif
