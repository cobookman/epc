var epc = require("../build/Release/epc");
var assertions = require("mocha").it;
var assert = require("chai").assert;

describe("sgtin", function() {
  describe("gtin14", function() {
    assertions("Should give valid gtin14 for valid epc", function() {
      assert.equal(new epc.Sgtin96("3018E51206F26DC000000002").Gtin14(), "12345688211115");
    });
  });
});
