python=python

.PHONY: all
all: python_lib

.PHONY: test
test: epc_test_node epc_test_python

#######################################
# Install and dist commands	      #
#######################################
.PHONY: python_install
python_install: epc_wrap_python.cpp _epc.so
	$(python) python/setup.py install

.PHONY: python_dist
python_dist: epc_wrap_python.cpp _epc.so
	$(python) python/setup.py sdist

.PHONY: python_lib
python_lib: epc_wrap_python.cpp _epc.so
	mkdir -p python/build
	echo "" > python/build/__init__.py
	$(python) python/setup.py install --install-lib=python/build

#######################################
# Unit Tests                          #
#######################################
.PHONY: epc_test_node
epc_test_node: epc_wrap_node.cpp
	nodejs --version > /dev/null

.PHONY: epc_test_python
epc_test_python: python_lib
	$(python) python/epc_test.py

#######################################
# Swig Wrappers                       #
#######################################
epc_wrap_node.cpp: epc.i
	swig3.0 -javascript -node -c++ -o epc_wrap_node.cpp epc.i

epc_wrap_python.cpp: epc.i
	swig3.0 -python -c++ -o epc_wrap_python.cpp epc.i


#######################################
# Language Specific Build             #
#######################################
_epc.so: python/setup.py epc_wrap_python.cpp epc.h epc.cpp epc.i
	$(python) python/setup.py build_ext --inplace

.PHONY: clean
clean:
	-rm epc_wrap_*.cpp
	-rm epc.py _epc*.so *.pyc *.gch MANIFEST python/*.pyc
	-rm build/ dist/ __pycache__/ python/build/ -rf

