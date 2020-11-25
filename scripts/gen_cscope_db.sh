#!/bin/sh
#==============================================================================
# Generate cscope database
#==============================================================================

# source project files list generator script
if [ -f ./gen_proj_src_file_list.sh ]; then
    . ./gen_proj_src_file_list.sh
else
    echo "ERR: gen_proj_src_files_list.sh is required!"
    exit -1
fi

set_cscope_env() {
    export CSCOPE_DB="$PROJ_BUILD_IDE_DIR/cscope_db/cscope.out"
}

gen_proj_cscope_db_n_setenv() {
    cscope -bqv \
      -i $PROJ_SRC_FILES \
      -f $PROJ_BUILD_IDE_DIR/cscope_db/cscope.out
}

# set env when sourcing to avoid repeating/forgetting
set_cscope_env
