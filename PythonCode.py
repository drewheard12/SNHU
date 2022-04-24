import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v



    
def makeList(): # option 1 in menu
    itemList = [] #temp list to assign the file to
    infile = open("CS210_Project_Three_Input_File.txt", "r")
    for line in infile: #assign each line to a workable lsit
        tempLine = line.strip()
        itemList.append(tempLine)

    itemDict = {} #dict that assigns a number to each item
    for i in itemList:
        if i in itemDict: #check to if the item already has been sold
            tempNum = itemDict[i]
            itemDict[i] = tempNum +1 #if so, +1
        else:
            itemDict[i] = 1 #if not, create and assign 1

    keyList = [] #list of each unique name sold
    for key, value in itemDict.items(): # for loop for getting name of each item sold
        keyList.append(key)

    tempNum = len(keyList)
    for i in range (tempNum): #output each name and its assigned number
        print(keyList[i], ":", itemDict[keyList[i]])
    
    infile.close()
    return 0


def countItem(v): #option 2 in menu
    itemList = []
    tempNum = 0
    infile = open("CS210_Project_Three_Input_File.txt", "r") # same open procedure as before
    for line in infile:
        tempLine = line.strip()
        itemList.append(tempLine)

    for i in itemList:# for loop that counts each time the item name is mentioned
        if i == v:
            tempNum = tempNum + 1
    #print(tempNum, v, "sold.")
    
    infile.close()
    return tempNum #return the count



def makeGraph():#option 3 in menu
    itemList = []
    infile = open("CS210_Project_Three_Input_File.txt", "r") # same open procedure as before
    for line in infile:
        tempLine = line.strip()
        itemList.append(tempLine)

    itemDict = {}
    for i in itemList:
        if i in itemDict:
            tempNum = itemDict[i]
            itemDict[i] = tempNum +1 #same dict procedure as 1
        else:
            itemDict[i] = 1

    keyList = []
    for key, value in itemDict.items():#same key procedure as 1
        keyList.append(key)
    tempNum = len(keyList)

    outfile = open("frequency.dat", "w")#open DAT file and write to it
    for i in range (tempNum):
        outfile.write(str((keyList[i], ":", itemDict[keyList[i]])))
    outfile.close()


    for i in range (tempNum): #printing for loop
        print(keyList[i], end="")
        j = itemDict[keyList[i]] #get item count
        for i in range (j):
            print("*", end="") #print * for each item sold
        print("\n")
    
    infile.close()
    return 0