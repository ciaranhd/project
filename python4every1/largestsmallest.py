largest = None
smallest = None
sum = 0

while True:
    num = input("Enter a number: ")
    if num == "done" :
        break
    sval = num
    try:
        fval = int(sval)
    except:
        print("invalid input")
        continue

    sum = fval + sum


    if largest is None:
        largest = fval
    if fval > largest:
        largest = fval

    if smallest is None:
        smallest = fval
    if fval < smallest:
        smallest = fval

print("Maximum", largest)
print("Minimum", smallest)
print ("total sum", sum)
