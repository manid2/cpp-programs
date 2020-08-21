#!/usr/bin/env python3
# rename files recursively

import os
import sys

# get the directory of your script
directory = os.path.dirname(os.path.realpath(sys.argv[0]))
for subdir, dirs, files in os.walk(directory):
    for filename in files:
        if filename.find('.cpp') > 0:
            # get the path to your subdirectory
            subdirectoryPath = os.path.relpath(subdir, directory)
            # get the path to your file
            filePath = os.path.join(subdirectoryPath, filename)
            newFilePath = filePath.replace(
                ".cpp", ".cc")  # create the new name
            os.rename(filePath, newFilePath)  # rename your file
