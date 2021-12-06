import math

#class for storing data in an efficient way
class Angle:
    def __init__(self, rad):
        self.rad=rad
    def __inti__(self, degree, prime):
        self.rad=math.radians(degree+prime/60)
    def Display(self):
        degree=math.trunc(math.degrees(self.rad))
        prime=(math.degrees(self.rad)-degree)*60.
        return str(degree)+"°\t"+str(prime)



        


def angle(m : int, lamb : float, d : float) -> Angle:
    partial= m*lamb/d 
    a=Angle(math.asin(partial))
    return a


def main() -> int:
    color=[5.89e-7, 5.896e-7]
    for i, k in range(0, 6, 1),color:
        angel=angle(i,k, 1/0.3)
        print("for lambda = %f, angle ="%
        (k)+angel.Display())
    return 0



if __name__=="__main__":
    main()