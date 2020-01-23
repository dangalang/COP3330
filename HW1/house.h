/* Name: Forrest Lang
 * Date: 21 JAN 2020
 * Section: 0005
 * Assignment: Homework 1
 */

class House {
public:
    House(int size, char wall='X', char filler='*');

    // Mutators:
    // If the base is less than 37 units, increase the size by 1.
    bool Grow();

    // If the base is larger than 3 units, shrink the size by 1.
    bool Shrink();

    // Change the border character to a valid ascii char (between 33 and 126).
    bool SetBorder(char wall);

    // Change the filler character to a valid ascii char (between 33 and 126).
    bool SetFill(char filler);

    
    // Accessors:
    // Get the size of the base of the house.
    int GetSize() const;

    // Calculate the perimeter of the house. Returns answer as integer.
    int Perimeter() const;

    // Calculate the area of the house. Returns answer as double
    double Area() const;

    // Draw an ascii representation of the house.
    void Draw() const;

    // Print the base width, perimeter, area and ascii depiction of the house.
    void Summary() const;

private:
    int base;
    char border;
    char fill;
};
