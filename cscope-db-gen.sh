#!/bin/bash
######
# Generate cscope database
######

PRD=$(pwd)      # Project Root Directory
PCD=$PRD/cscope # Project cscope directory

if [ ! -d "$PCD" ]; then
    mkdir -p $PCD
fi

# find all source files ignore everything else
find $PRD \
    -path "$PRD/LearnGcov/*" \
    -path "$PRD/LearnGTestAndGMock/*" \
    -path "$PRD/StructuredData/*" \
    -prune -o -path "$PRD/autom4te.cache/*" \
    -prune -o -path "$PRD/build/*" \
    -prune -o -path "$PRD/build-aux/*" \
    -prune -o -path "$PRD/m4/*" \
    -prune -o -regex '.*/.*\.\(cc\|hh\)$' \
    -print >$PCD/cscope.files

cd $PCD
cscope -b -q # build cscope db
cd $PRD
CSCOPE_DB=$PCD/cscope.out
echo "CSCOPE_DB=$CSCOPE_DB"
export CSCOPE_DB
