def countZeros(n):
"""
  return the number of 0 appear in sequences of  1..n
"""
    result = 0
    i = 1

    while True:
        b, c = divmod(n, i)
        a, b = divmod(b, 10)

        if a == 0:
            return result

        if b == 0:
            result += (a - 1) * i + c + 1
        else:
            result += a * i

        i *= 10

if __name__ == "__main__":
  print countZeros(12304)  
  print countZeros(1234)  
  print countZeros(457)  
