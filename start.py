#!/usr/bin/env python3
import os, sys, fnmatch

folderIgnore={"r_stdio", ".git"}
IgnoreNames={"cave_hunter.c"}

def checkIfNameFound(name, nArray):
    for i in nArray:
        if fnmatch.fnmatch(name, "*"+i):
            return 1
    return 0

if __name__ == '__main__':

    dirName = sys.argv[1];
    
    # Get the list of all files in directory tree at given path
    listOfFiles = list()
    for (dirpath, dirnames, filenames) in os.walk(dirName):
        dirnames[:] = [d for d in dirnames if d not in folderIgnore]
        listOfFiles += [os.path.join(dirpath, file) for file in filenames]

    outstr = str()

    ignorePatternFront = ["."]
    ignorePatternEnd = []
    onlyTakePatternEnd = [".c"]

    # Print the files    
    for elem in listOfFiles:
        if elem[2] != ".":
            if elem[-1] == "c":
                if checkIfNameFound(elem, IgnoreNames) != 1:
                    outstr += elem + " "
        
    print(outstr)