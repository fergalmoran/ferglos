#ifndef __DRIVER_H
#define __DRIVER_H
class Driver {
   public:
    Driver();
    ~Driver();

    virtual void Activate();
    virtual int Reset();
    virtual void Deactivate();
};

class DriverManager {
   private:
    Driver* _drivers[32];  // hard code size for now until we have memory management sorted
    int _numDrivers;

   public:
    DriverManager();
    ~DriverManager();
    void AddDriver(Driver*);

    void ActivateAll();
};
#endif
