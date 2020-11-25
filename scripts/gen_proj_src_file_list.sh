#!/bin/sh
#
# Generate source files list for use with gtags/cscope/geany/u-ctags

PROJ_SRC_DIR=$PWD # source this script from project top level directory
PROJ_BUILD_IDE_DIR=$PROJ_SRC_DIR/build_ide
PROJ_SRC_FILES=$PROJ_BUILD_IDE_DIR/proj_src_files.txt

gen_proj_src_files_list() {
    if [ ! -d "$PROJ_BUILD_IDE_DIR" ]; then
        mkdir -p $PROJ_BUILD_IDE_DIR
    fi

    # find all source files ignore everything else
    # include nfv build time files, nfv src files
    # exclude non-src files, include only c/cpp src & hdrs
    find -L $PROJ_SRC_DIR \
	-path "$PROJ_SRC_DIR/CodeCoverage/*" \
        -path "$PROJ_SRC_DIR/StructuredData/*" \
        -path "$PROJ_SRC_DIR/UnitTesting/*" \
        -prune -o -path "$PROJ_SRC_DIR/autom4te.cache/*" \
        -prune -o -path "$PROJ_SRC_DIR/build/*" \
        -prune -o -path "$PROJ_SRC_DIR/build-aux/*" \
        -prune -o -path "$PROJ_SRC_DIR/m4/*" \
        -regex '.*/.*\.\(cpp\|h\|c\|cc\|hh\)$' -type f \
        -print >$PROJ_SRC_FILES

    if [ -r $PROJ_SRC_FILES ]; then
        echo "Success in creating project source files list"
        echo "Path: $PROJ_SRC_FILES"
    else
        echo "Error in creating $PROJ_SRC_FILES"
    fi
}
