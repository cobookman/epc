const assert = require('assert');
var epc = require('./build/Release/epc');

assert.equal(epc.EpcFactory("301").Type(), epc.SGTIN96);
console.log("All tests a-ok");
