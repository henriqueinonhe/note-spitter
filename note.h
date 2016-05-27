#ifndef NOTE_H
#define NOTE_H

class Note
{
    public:
        Note(const unsigned char _pitch = 0, const double _duration = 0);
        unsigned char getPitch() const;
        double getDuration() const;
        char getVelocity() const;
        void setPitch(const unsigned char _pitch);
        void incrementPitch(const unsigned char _pitch);
        void setDuration(const double _duration);
        void incrementDuration(const double _duration);
        void setVelocity(const char _velocity);
        bool isRest() const;
        ~Note();

    private:
        unsigned char pitch;
        double duration;
        char velocity;
};

#endif
