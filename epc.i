%module epc
%include "std_string.i"
%include "stdint.i"

%{
#include "epc.h"
#include "factory.h"
#include "encodings/sgtin96.h"
%}

%include "epc.h"
%include "factory.h"
%include "encodings/sgtin96.h"
