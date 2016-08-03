if __name__ == "__main__":
  arg = input("fizzbuzz]")
  n = int(arg) 

  for i in range(1, n+1):
    #print i
    if (i % 3) == 0 and (i % 5) == 0: 
      print "fizzbuzz"
    elif (i % 3) == 0:
      print "fizz"
    elif (i % 5) == 0:
      print "buzz"
    else:
      print i
