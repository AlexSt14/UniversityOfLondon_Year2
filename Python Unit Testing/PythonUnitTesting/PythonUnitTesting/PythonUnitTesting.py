import unittest

myListOfNumbers = [10,12,15,16,19]

print(myListOfNumbers)

print(myListOfNumbers[2])


#Using the iteration of lists similar to array index i style
for i in range(0,len(myListOfNumbers)):
    print("Index", i, "value", myListOfNumbers[i])
   
myListOfNumbers.append(246)
myListOfNumbers.extend([1,2,3])

#Iterating over a list

for value in myListOfNumbers:
    print(value)

def addOne(value):
    value += 1
    return value
myNumber = 10
print(myNumber)
myNumber = addOne(myNumber)
print(myNumber)


