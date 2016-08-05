from build import epc

print epc.EpcFactory("30").Type()
print epc.EpcFactory("302").Hex();
print epc.EpcFactory("302").Base64();
print epc.EpcFactory("30223423423423423422222222222222222222222222222222").Base64();

