//
// Random Access Memory Device.
//

#ifndef M68K_DEVICES_ROM_HPP_
#define M68K_DEVICES_ROM_HPP_

#include <string>

#include "Framework/BasicDevice.hpp"

class ROM : public BasicDevice {
public:
  ROM(const std::string &args, BasicCPU &cpu);
  ~ROM();

  // Returns true iff the address maps into the device.
  bool CheckMapped(Address addr) const;

  // Returns the lowest address used by the device.
  Address LowestAddress() const { return myBaseAddress; }

  // Returns the highest address used by the device.
  Address HighestAddress() const { return myBaseAddress + mySize - 1; }

  // Gets a byte from memory.
  Byte Peek(Address address) {
    if (address < LowestAddress() || HighestAddress() < address) {
      return 0xFF;
    }
    return myBuffer[address - myBaseAddress];
  }

  // Puts a byte into memory.
  virtual void FPoke(Address address, Byte c) {
    if (LowestAddress() <= address && address <=  HighestAddress()) {
      myBuffer[address - myBaseAddress] = c;
    }
  }
  // Normal pokes do nothing! Only load!
  virtual void Poke(Address address, Byte c) {};
  // ROM never has Events
  void EventCallback(int, void *) { }

protected:
  // Buffer to hold the ROM's contents.
  Byte *myBuffer;

private:
  // Starting address of the ROM device
  Address myBaseAddress;

  // Size of the ROM device in bytes
  size_t mySize;
};

#endif  // M68K_DEVICES_ROM_HPP_
