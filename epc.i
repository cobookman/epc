%module epc
%include "std_string.i"
%include "stdint.i"

%{
#include "epc.h"
#include "factory.h"
#include "encodings/sgtin.h"
%}

%typemap(out) Epc* {
        const std::string lookup_typename = $1->ClassName() + " *";
        swig_type_info * const outtype = SWIG_TypeQuery(lookup_typename.c_str());
        $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), outtype, $owner);
}

%include "epc.h"
%include "factory.h"
%include "encodings/sgtin.h"
