{
	"targets": [{
		"target_name": "epc",
		"sources": [
			"../epc_wrap_node.cpp",
                        "../src/b64/cencode.cpp",
                        "../src/epc.cpp",
                        "../src/factory.cpp",
                        "../src/encodings/sgtin96.cpp",
		],
		"include_dirs": [
			"../include"
		],
		"cflags": [
			"-std=c++11"
		]
	}]
}
