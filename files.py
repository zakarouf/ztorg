#!/usr/bin/env python3

import os, sys
'''
    For the given path, get the List of all files in the directory tree 
'''
def getListOfFiles(dirName):

    listOfFile = os.listdir(dirName)
    allFiles = list()

    
    for entry in listOfFile:
        
        fullPath = os.path.join(dirName, entry)
        
        if os.path.isdir(fullPath):
            allFiles = allFiles + getListOfFiles(fullPath)
        else:
            allFiles.append(fullPath)
                
    return allFiles

def main():
    
    dirName = sys.argv[1];
    
    # Get the list of all files in directory tree at given path
    listOfFiles = getListOfFiles(dirName)
    
    # Print the files
    '''for elem in listOfFiles:
        print(elem)
    print ("****************")'''
    
    # Get the list of all files in directory tree at given path
    listOfFiles = list()
    for (dirpath, dirnames, filenames) in os.walk(dirName):
        listOfFiles += [os.path.join(dirpath, file) for file in filenames]
        
        
    st = str()

    ignorePatternFront = ["."]
    ignorePatternEnd = []
    onlyTakePatternEnd = [".c"]

    # Print the files    
    for elem in listOfFiles:
        if elem[2] != ".":
            if elem[-1] == "c":
                st += elem + " "
        
    print(st)
        
        
if __name__ == '__main__':
    main()