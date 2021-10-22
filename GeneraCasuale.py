import random 


f=open("data.dat", "w")
random.seed(0000)
x=int(input("quanti numeri devo generare?\n"))
for i in range(x):
    f.write(str(random.gauss(1.62, .5))+"\n")
