var epc = require("../build/Release/epc");
var assertions = require("mocha").it;
var assert = require("chai").assert;

describe("epc", function() {
  describe("Epc", function() {
    assertions("Should allow instantiation", function() {
      assert.equal(new epc.Epc("300000").Type(), epc.UNKNOWN);
    });
  });

  describe("EpcFactory", function() {
    assertions("Should give valid epcs for all inputs", function() {
      assert.equal(epc.EpcFactory("3018E51206F26DC000000002").PureUri().indexOf("urn:epc:id:sgtin-96"), 0);
      assert.equal(epc.EpcFactory("30").Type(), epc.SGTIN96);
    });

    assertions("Should handle bad hex input", function() {
      assert.equal(epc.EpcFactory("").Type(), epc.UNKNOWN);
      assert.equal(epc.EpcFactory("!!QQ").Type(), epc.UNKNOWN);
    });

  });

  describe("Type", function() {
    assertions("Should give sgtin96", function() {
      assert.equal(epc.EpcFactory("3018E51206F26DC000000002").Type(), epc.SGTIN96);
    });
    assertions("Should give unknown for bad tags", function() {
      assert.equal(epc.EpcFactory("0018E51206F26DC000000002").Type(), epc.UNKNOWN);
    });
  });

  describe("Hex", function() {
    assertions("Should give a valid hex string for good inputted hex", function() {
      assert.equal(epc.EpcFactory("3018E51206F26DC000000002").Hex(), "3018E51206F26DC000000002");
      assert.equal(epc.EpcFactory("0018E51206F26DC000000002").Hex(), "0018E51206F26DC000000002");
    });
    assertions("Should give empty hex string for bad inputted hex", function() {
      assert.equal(epc.EpcFactory("QQ1234").Hex(), "");
      assert.equal(epc.EpcFactory("").Hex(), "");
    });
  });

  describe("Base64", function() {
    assertions("Should give valid base64 for good inputted hex", function() {
      assert.equal(epc.EpcFactory("3018E51206F26DC000000002").Base64(), "MBjlEgbybcAAAAAC");
      assert.equal(epc.EpcFactory("").Base64(), "");
    });
    assertions("Should give empty string for bad inputted hex", function() {
      assert.equal(epc.EpcFactory("!!QQ").Base64(), "");
    });
  });

});
