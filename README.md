# EPC Parser

After writing an epc parser for python and java and c.  It got tiring having to
port the same code to various languages.  I found that finding bugs was getting
complicated as each library was slightly different.

This library aims to provide epc parsing in various languages using SWIG.  While
the epc parsing is done using c++, I'm not aiming for high performance. And
code readability was placed at a higher priority than performance.


## Tests

// TODO(bookman): Implement code
Slowly but surely unit tests for each end-language will be produced.  This gives
assurance on integration.  Unit tests in C++ will also be done as well.

## Libraries

// TODO(bookman): Implement
This library will be published to npm / pip ...etc so that end users wont need
to compile the code manually.  However this is how you'd build the code.


### Node.js

Build our code:

`$ make node_lib`


Test it's working as intenteded:

`$ make test_node`

Then simply require the following:
```
var epc = require("./nodejs/build/Releases/epc");
```


### Python

Build our code:

`$ make python_lib`


Test it's working as intended:

`$ make test_python`

Then to use simply copy `python/build` into your python project and use the
following python code:

```
from build import epc
```
