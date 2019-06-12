#include <iostream>
#include <vector>

using namespace std;

// This is a class that defines a circle
class Circle {
protected:
    double radius;
public:
    Circle() { radius = 0.0; }
    Circle(double r) { radius = r; }
    virtual double area() { return (3.14 * radius * radius); }
};

// This is a class that defines a cylinder
// While technically, you have a volume for cylinders,
// name it area for consistency (also, I want to test your 
// ability to use polymorphism)
class Cylinder : public Circle {
private:
    double height;
public:
    Cylinder() { height = 0.0; }
    Cylinder(double r, double h) : Circle(r) { height = h; }
    virtual double area();
    friend const Cylinder operator+ (const Cylinder &A, const Cylinder &B);
};
// Use upcasting to calculate the volume
double Cylinder::area()
{
    // Fill in code here
				return Circle::area() * height;
}

// The add operator is used to combine two cylinders of the same radius
// to make a longer cylinder.
// That is, if the two cylinders have equal radius, combine their
// heights, otherwise throw an error and exit()
const Cylinder operator+ (const Cylinder &A, const Cylinder &B)
{
    // Fill in code here
		if(A.radius == B.radius) {
			int newH = A.height + B.height;
			Cylinder *newC = new Cylinder(A.radius, newH);
			return *newC;
		} else {
			throw;
			exit(1);
		}
}

// This is a class that defines a rectangle
class Rectangle {
protected:
    double length;
    double width;
public:
    Rectangle() { length = 0.0; width = 0.0; }
    Rectangle(double l, double w) { length = l; width = w; }
    virtual double area() { return (length * width); } 
};

// This is a class that defines a cuboid - a 3D rectangle
// Same reasoning as above for area/volume
class Cuboid : public Rectangle {
private:
    double height;
public:
    Cuboid() { height = 0.0; }
    Cuboid(double l, double w, double h) : Rectangle(l, w) { height = h; }
    virtual double area();
};
// Use upcasting to calculate the volume
double Cuboid::area()
{
    // Fill in code here
		return Rectangle::area() * height;
}


// Now define a Table class that uses composition to
// combine a cuboid and numLegs cylinders
// Find the volume
class Table {
private:
    Cuboid top;
    vector<Cylinder> legs;
    int numLegs;
public:
    Table() { numLegs = 0; }
    Table(Cuboid c, Cylinder l, int nLegs);
    double volume();
};
Table::Table(Cuboid c, Cylinder l, int nLegs)
{
    // Fill in code here
				top = c;
				numLegs = nLegs;
				for(int i = 0; i < numLegs; ++i) {
					legs.push_back(l);
				}
}
double Table::volume()
{
    // Fill in code here
		double topV = top.area();
		double legV = legs[0].area() * numLegs;
		return topV + legV;
}

int main(int argc, char **argv)
{
    // Table legs are cylinders
    // Define the first cylinder
    Cylinder *X = new Cylinder(3.0, 5.0);
    cout << X->area() << endl;

    // Define the second cylinder
    Cylinder *Y = new Cylinder(3.0, 7.0);
    cout << Y->area() << endl;

    // Cylinders X and Y are not long enough - combine them to
    // make a longer cylinder
    Cylinder Z = *X + *Y;
    cout << Z.area() << endl;

    // Create a flat surface for the table
    Cuboid C(70.0, 30.0, 3.0);
    cout << C.area() << endl;

    // Construct the table from the cylinder and cuboid
    // Since the legs have to be identical, you can specify one leg and 
    // give the number of legs you want for this table
    Table T(C, Z, 4);
    cout << T.volume() << endl;

    return 0;
}
/*
141.3
197.82
339.12
6300
7656.48
*/
