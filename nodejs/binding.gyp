{
	"targets": [{
		"target_name": "epc",
		"sources": [
			"../epc_wrap_node.cpp",
                        "../src/b64/cencode.cpp",
                        "../src/epc.cpp",
                        "../src/factory.cpp",
                        "../src/encodings/sgtin.cpp",
		],
		"include_dirs": [
			"../include"
		],
		"cflags": [
			"-std=c++11",
		],
		"cflags!": [ "-fno-exceptions" ],
		"cflags_cc!": [ "-fno-exceptions" ],
		"conditions": [
			["OS==\"mac\"", {
				"xcode_settings": {
					"GCC_ENABLE_CPP_EXCEPTIONS": "YES"
				}
			}]
		]
	}]
}
