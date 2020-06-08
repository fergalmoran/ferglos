#include "../include/driver.h"

Driver::Driver() {}
Driver::~Driver() {}

void Driver::Activate() {}
int Driver::Reset() { return 0; }
void Driver::Deactivate() {}

DriverManager::DriverManager() {
    _numDrivers = 0;
}
DriverManager::~DriverManager() {}
void DriverManager::AddDriver(Driver* drv) {
    _drivers[_numDrivers] = drv;
    _numDrivers++;
}

void DriverManager::ActivateAll() {
    for (int i = 0; i < _numDrivers; i++) {
        _drivers[i]->Activate();
    }
}
