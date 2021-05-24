#!/bin/sh
#==============================================================================
# Generate universal ctags database
#==============================================================================

# source project files list generator script
if [ -f ./gen_proj_src_file_list.sh ]; then
    . ./gen_proj_src_file_list.sh
else
    echo "ERR: gen_proj_src_files_list.sh is required!"
    exit -1
fi

gen_proj_ctags_db() {
    ctags --totals --fields=fKsSt --extras=-fq --kinds-c++=+p --excmd=number \
        -L $PROJ_SRC_FILES \
        -f $PROJ_BUILD_IDE_DIR/geany_ide/cpp-code-examples.tags
}

# NOTE: no setenv for ctags, just generate the tags file, create a soft link
# to it or add it directly to vim tags command.
# Geany and OpenGrok uses same tags file to index the source.
