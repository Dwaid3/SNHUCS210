import re
import string



def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v


#This function will open the file read the information and give us a list of items a frequency of purchase
def listOfItems():
    #List will hold all of the items bought
    groceryList = []

    #Dictionary will give us a key value pair that will show occurences of items
    groceryOccur = {}


    #This will open file to read
    file = open("groceryList.txt", 'r+')
    f = file.readlines()
    
    #For loop will add items to our list
    for items in f:
        groceryList.append(items.strip())


    print("\nList of items bought and the amount:\n")
    #This loop and nested loop will added the items and the amount bought into a dictionary making a key values pair
    for items in groceryList:
        timesbought = 0     
        for occurence in groceryList:
            if (items == occurence):
                timesbought += 1
        #This if statement will ensure we do not add the same items to our list twice
        if items != groceryOccur:
            groceryOccur[items] = timesbought
    file.close()
    
    print()
    #This will print out each key values pair
    for values in groceryOccur:
        print(values, ":", groceryOccur[values],)

    print()
    
def quantityBought(item):
    #This will captitalize the first letter to ensure accurate answers
    item = str.capitalize(item)

    #List will hold all of the items bought
    groceryList = []

    #Dictionary will give us a key value pair that will show occurences of items
    groceryOccur = {}
    
    #opens file in read mode
    file = open("groceryList.txt", 'r+')
    f = file.readlines()
    
    

    #For loop will add items to our list
    for items in f:
        groceryList.append(items.strip())

    count = 0
    #This for loop will count the item you want 
    for items in groceryList:
        if (items == item):
            count += 1
    

    print("\n" + item, "has been purchased", count, "times\n" )
    file.close()

def createHistogram():
    #List will hold all of the items bought
    groceryList = []

    #Dictionary will give us a key value pair that will show occurences of items
    groceryOccur = {}
    
     #opens file in read mode
    file = open("groceryList.txt", 'r+')
    f = file.readlines()
    
     #For loop will add items to our list
    for items in f:
        groceryList.append(items.strip())


    f = open("freq.dat", 'w')

    #This loop and nested loop will added the items to a dictionary so we can write them to a file
    for items in groceryList:
        timesbought = 0     
        for occurence in groceryList:
            if (items == occurence):
                timesbought += 1
        #This if statement will ensure we do not add the same items to our list twice
        if items != groceryOccur:
            groceryOccur[items] = timesbought

    for items in groceryOccur:
        lineToAdd = items + "\n" + str(groceryOccur[items])

        f.write(lineToAdd + "\n")
    file.close()