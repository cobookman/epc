from build import epc

tag = epc.Epc()
print epc.SGTIN96 == tag.Type()
print tag.Hex()
print tag.Base64()
print tag.Type()
