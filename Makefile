INCLUDES=./include

python=python
swig=swig3.0 -c++ -I$(INCLUDES)

.PHONY: all
all: python_lib node_lib

.PHONY: test
test: test_node test_python

#######################################
# Install and dist commands	      #
#######################################
.PHONY: python_install
python_install: epc_wrap_python.cpp
	$(python) python/setup.py install

.PHONY: python_dist
python_dist: epc_wrap_python.cpp
	$(python) python/setup.py sdist

.PHONY: python_lib
python_lib: epc_wrap_python.cpp
	mkdir -p python/build
	echo "" > python/build/__init__.py
	CPLUS_INCLUDE_PATH=$(INCLUDES) $(python) python/setup.py install --install-lib=python/build

.PHONY: node_gyp_configure
node_gyp_configure: epc_wrap_node.cpp node_modules
	./nodejs/node_modules/.bin/node-gyp -C nodejs/ configure

.PHONY: node_lib
node_lib: node_gyp_configure node_modules
	./nodejs/node_modules/.bin/node-gyp -C nodejs/ build

.PHONY: node_modules
node_modules:
	cd nodejs && npm i

#######################################
# Unit Tests                          #
#######################################
.PHONY: test_node
test_node: node_lib node_modules
	cd nodejs && npm test

.PHONY: test_python
test_python: python_lib
	$(python) python/epc_test.py

#######################################
# Swig Wrappers                       #
#######################################
epc_wrap_node.cpp: epc.i
	$(swig) -javascript -node -o epc_wrap_node.cpp epc.i

epc_wrap_python.cpp: epc.i
	$(swig) -python -o epc_wrap_python.cpp epc.i


.PHONY: clean
clean:
	-rm epc_wrap_*.cpp
	-rm epc.py _epc*.so *.pyc *.gch MANIFEST python/*.pyc
	-rm build/ dist/ __pycache__/ python/build/ -rf
	-node-gyp -C nodejs/ clean
	-rm nodejs/node_modules -rf

