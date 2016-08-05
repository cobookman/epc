%module epc
%include "std_string.i"
%include "stdint.i"

%{
#include "epc.h"
#include "sgtin96.h"
#include "factory.h"
%}

%include "epc.h"
%include "sgtin96.h"
%include "factory.h"

