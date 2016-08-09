#ifndef FACTORY_H_
#define FACTORY_H_

#include "epc.h"
#include "encodings/sgtin.h"

// Returns an epc obj for the correct tag type
// If tag does not match any tag type, a tag of type NONE is created
Epc* EpcFactory(const std::string& tag);

#endif  // FACTORY_H_
