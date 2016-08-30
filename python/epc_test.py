import unittest
from build import epc


class TestEpc(unittest.TestCase):
  """Tests the epc class."""

  def test_EpcFactory(self):
    """Tests the EpcFactory method."""
    self.assertEqual(epc.EpcFactory("3018E51206F26DC000000002").Type(), epc.SGTIN96)
    self.assertEqual(epc.EpcFactory("30").Type(), epc.SGTIN96)

    # Test for empty tags and non hex strings
    self.assertEqual(epc.EpcFactory("").Type(), epc.UNKNOWN)
    self.assertEqual(epc.EpcFactory("!!QQ").Type(), epc.UNKNOWN)

  def test_Type(self):
    """Tests the Epc.Type method."""
    self.assertEqual(epc.EpcFactory("3018E51206F26DC000000002").Type(), epc.SGTIN96)
    self.assertEqual(epc.EpcFactory("0018E51206F26DC000000002").Type(), epc.UNKNOWN)

  def test_Hex(self):
    """Tests the epc Hex method."""
    self.assertEqual(epc.EpcFactory("3018E51206F26DC000000002").Hex(), "3018E51206F26DC000000002")
    self.assertEqual(epc.EpcFactory("0018E51206F26DC000000002").Hex(), "0018E51206F26DC000000002")
    self.assertEqual(epc.EpcFactory("QQ1234").Hex(), "")
    self.assertEqual(epc.EpcFactory("").Hex(), "")

  def test_gtin(self):
    self.assertEqual(epc.EpcFactory("3018E51206F26DC000000002").Gtin14(), "12345688211115");

  def test_builder(self):
    builder = epc.Sgtin96.Build()
    tag = builder.CompanyPrefix("1234567").ItemRef("12345").Serial("123456789").Filter(1).Build()
    print tag.Hex()
    # self.assertEqual(tag.Type(), epc.SGTIN96);
    # self.assertEqual(tag.Gtin14(), "45100012312345")
    # self.assertEqual(tag.Hex(), "")

if __name__ == "__main__":
  unittest.main()
