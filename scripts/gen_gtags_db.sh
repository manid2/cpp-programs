#!/bin/sh
#
# Generate gtags db

# source project files list generator script
if [ -x gen_proj_src_files_list.sh ]; then
    . gen_proj_src_files_list.sh
else
    echo "ERR: gen_proj_src_files_list.sh is required!"
    exit -1
fi

#--- gen gnu global gtags db
set_gtags_env() {
    # Force .h files as Cpp headers
    export GTAGSFORCECPP=1
    # set gtags src n db paths
    export GTAGSROOT=$PROJ_SRC_DIR
    export GTAGSDBPATH=$PROJ_GTAGS_DB_DIR
}

gen_gtags_db() {
    # set GTAGSFORCECPP to force use cpp sources
    set_gtags_env

    # Review and edit the generated project source files as suited.
    # Generate GNU Global database files
    gtags -c -f $PROJ_SRC_FILES

    # htags optional, uses large memory, ~5GB for NFV
    #htags --suggest2
    #htags-server >& log &
    #firefox http://127.0.0.1:8000
}

PROJ_GTAGS_DB_DIR=$PROJ_BUILD_IDE_DIR/gtags_db

mv_gtags_db_to_build_ide() {
    # create directory fo gnu global ide gen files
    if [ ! -d "$PROJ_GTAGS_DB_DIR" ]; then
        mkdir -p $PROJ_GTAGS_DB_DIR
    fi

    # move gtags db files to PROJ_BUILD_IDE_DIR/gnu_global dir
    for db_file in GPATH GRTAGS GTAGS; do
        if [ -r "$db_file" ]; then
            mv $db_file $PROJ_GTAGS_DB_DIR/
        else
            echo "Tags DB File '${db_file}' not found. Exit with error"
            exit -1
        fi
    done

    # set gtags export paths
    set_gtags_env
}


# FIXME: global update option is not working as expected.
# Some extra files not presetn $PROJ_SRC_FILES were indexed.
# This causes unnecessary indexing extra, uncomment when fix is known.
#update_gtags_db() {
#    set_gtags_env
#    global -vu -L $PROJ_SRC_FILES 
#}

gen_proj_gtags_db_n_setenv() {
    gen_proj_src_files_list
    gen_gtags_db
    mv_gtags_db_to_build_ide
}

# set env when sourcing to avoid repeating/forgetting
set_gtags_env
