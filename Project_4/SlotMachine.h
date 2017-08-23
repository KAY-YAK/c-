#ifndef SLOTMACHINE_H
#define SLOTMACHINE_H
#include "Shape.h"
#include "IsoTriangle.h"
#include "RightTriangle.h"
#include "Rhombus.h"
#include "Rectangle.h"
#include<array>

class SlotMachine{
  private:
    array<Shape*, 3> reel;
    void make_shapes();
    void make_shape(int rand);
    void display_shapes();
    void report_status();
    void release_shapes();
  public:
    int tokens;
    int conversion;
    SlotMachine();
    ~SlotMachine();
    void run();

};



#endif
