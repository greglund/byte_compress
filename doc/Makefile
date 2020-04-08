# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build

DOXY_OUT = $(BUILDDIR)/doxygen
SRC_OUT = $(SOURCEDIR)/_srcs
DIRS = $(sort $(BUILDDIR) $(DOXY_OUT) $(SRC_OUT))
SRCS = ../src/byte_compress.c \
       ../src/byte_decompress.c \
       ../test/test/test_bytecompress.c
SRC_FILE_NAMES = $(notdir $(SRCS))
SRC_OUT_FILES = $(addprefix $(SRC_OUT)/, $(SRC_FILE_NAMES))

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

$(DIRS):
	mkdir $@

$(SRC_OUT_FILES): $(SRCS)
	cp $< $(SRC_OUT)

doxygen:
	doxygen Doxyfile

.PHONY: help Makefile

clean: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	trash _srcs

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile $(SRC_OUT_FILES) $(DIRS) doxygen
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
