#ifndef DEVICE_H
#define DEVICE_H

class Device {
    private:
        int volume;

    public: 
        int getVolume() const;
        void setVolume(const int & value);
};

#endif