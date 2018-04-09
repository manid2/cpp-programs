#!/bin/bash
#####################################################################
#
# Author: Mani Kumar
# Date: 03-Mar-2018
# 
# Description: This script automates the project related tasks.
#####################################################################
 
# Creates the folder structure of the modules
create_folders()
{

TargetFolder=$1
echo ${TargetFolder}
SubFolders=("inc" "src" "obj" "data" "doc" "test")

for Folder in *${TargetFolder}/ ; do
   Folder=${Folder%/}

   cd $Folder;
   echo -e "##### Entered "$Folder" #####";
    
   for SubFolder in ${SubFolders[*]} ; do
           # make sub folder
           if [ ! -d $SubFolder ]; then
               mkdir $SubFolder;
               echo -e "  --> Created "$SubFolder;
           fi
   done
    
   cd ../
   echo -e "##### Left "$Folder" #####";
    
done
} # create_folders()

# TODO: Additional tasks 
# --- yet to implement ---

# main script code
create_folders $1
