import re
import string

FILENAME = 'items.txt'

def readFile(filename):
    '''
    Gets the list of lines read in from the file in raw form.
    @param - the filename to read in (must be in same directory as the Source.cpp!)
    @return - the list of lines
    '''
    
    lines = None
    
    with open(filename) as file:
        lines = file.readlines()

    return lines


def getInventory():
    '''
    Get the inventory read in from the file.
    @return - dictionary of inventory in the form {item : frequency}
    '''
    
    # Dictionary of {item : frequency} 
    inventory = {}
    
    items = readFile(FILENAME)

    # Loop through the list of items
    for item in items:
        
        # Remove the newline character at end of line. 
        # SEE https://www.delftstack.com/howto/python/python-remove-newline-from-string/
        item = item.strip()

        # Update existing frequency; otherwise add item to dictionary
        if item in inventory:
            inventory[item] += 1 # accumulate to the dictionary item
        else:
            inventory[item] = 1
            
    return inventory

    
def determineInventory():
    # Get the inventory
    inventory = getInventory()
    

    # loop through the dictionary's keys and values
    # SEE https://stackoverflow.com/questions/3294889/iterating-over-dictionaries-using-for-loops
    for keys, values in inventory.items():
        # print the output
        print(keys, ':', values)


def determineFrequency(item):
    # Get the inventory
    inventory = getInventory()
    
    # Access the item from the inventory
    # SEE https://www.w3schools.com/python/python_dictionaries_access.asp
    inventory_item = inventory[item]

    return inventory_item
    

def output():
    # Very similar to determineInventory 
    # Get the inventory
    inventory = getInventory()

    # Loop through the dictionary and write to the frequency.dat file
    # SEE https://www.w3schools.com/python/python_file_write.asp
    # Create a file object to open and write to
    f = open('frequency.dat', 'w')
    for keys, values in inventory.items():

        # write mode takes two string arguments; converted integer values to a string
        f.write(keys + ' ' + str(values) + '\n')
    f.close()
    
