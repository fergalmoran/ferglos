#ifndef __FERGLOS_DRIVERS_DRIVER_H
#define __FERGLOS_DRIVERS_DRIVER_H
namespace ferglos {
namespace drivers {
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
}  // namespace drivers
}  // namespace ferglos
#endif
