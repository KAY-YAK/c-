#include "SlotMachine.h"
#include <iostream>
#include <array>
#include <random>
#include <regex>
#include <string>
using namespace std;

SlotMachine::SlotMachine(){
  tokens = 10;
}

SlotMachine::~SlotMachine(){

}


void SlotMachine::make_shapes(){
  for (int x = 0 ; x<=2 ;x++){
    this->make_shape(x);
  }
}


void SlotMachine::make_shape(int x){
  random_device rd;

  mt19937 e2(rd());

  uniform_int_distribution<> dist_1(1, 4);

  uniform_int_distribution<> dist_2(1, 25);
  int rand_shape = dist_1(e2);
  int rand_width =0;
  int rand_height =0;
  Shape *shp_1;
  Shape *shp_2;
  Shape *shp_3;
  if(rand_shape == 1){
    rand_width = dist_2(e2);
    //cout << "rand_w : "<< rand_width << endl;
    if(x == 0){
      shp_1 = new Rhombus(rand_width);
    }
    if(x==1){
      shp_2 = new Rhombus(rand_width);
    }
    if(x==2){
      shp_3 = new Rhombus(rand_width);
    }
  }

  if(rand_shape == 2){
    rand_width = dist_2(e2);
    //cout << "rand_w : "<< rand_width << endl;
    if(x == 0){
      shp_1 = new IsoTriangle(rand_width);
    }
    if(x==1){
      shp_2 = new IsoTriangle(rand_width);
    }
    if(x==2){
      shp_3 = new IsoTriangle(rand_width);
    }
  }

  if(rand_shape == 3){
    rand_width = dist_2(e2);
    //cout << "rand_w : "<< rand_width << endl;
    if(x == 0){
      shp_1 = new RightTriangle(rand_width);
    }
    if(x==1){
      shp_2 = new RightTriangle(rand_width);
    }
    if(x==2){
      shp_3 = new RightTriangle(rand_width);
    }
  }

  if(rand_shape == 4){
    rand_height = dist_2(e2);
    rand_width = dist_2(e2);
    // cout << "rand_w : "<< rand_width << endl;
    // cout << "rand_h : "<< rand_height << endl;
    if(x == 0){
      shp_1 = new Rectangle(rand_height, rand_width);
    }
    if(x==1){
      shp_2 = new Rectangle(rand_height, rand_width);
    }
    if(x==2){
      shp_3 = new Rectangle(rand_height, rand_width);
    }
  }

  if(x == 0){
    this->reel[x] = shp_1;
  }
  if(x == 1){
    this->reel[x] = shp_2;
  }
  if(x == 2){
    this->reel[x] = shp_3;
  }
}


void SlotMachine::display_shapes(){
  int height = 0;
  int width_1 = reel[0]->calculate_box_width() + 1;
  int width_2 = width_1 + reel[1]->calculate_box_width() + 1;
  int width_3 = width_2 + reel[2]->calculate_box_width() + 1;

  int width = reel[0]->calculate_box_width() + reel[1]->calculate_box_width() + reel[2]->calculate_box_width() + 4;


  if(reel[0]->calculate_box_height() >= reel[1]->calculate_box_height()){
    height = reel[0]->calculate_box_height();
  }else{
    height = reel[1]->calculate_box_height();
  }

  if(reel[2]->calculate_box_height() >= height){
    height = reel[2]->calculate_box_height();
  }

  height = height + 2;
  // cout << height<<endl;
  // cout << width -1 <<endl;
  // cout << width_1 << endl;
  // cout << width_2 << endl;
  // cout << width_3 << endl;


  for(int x = 0 ; x <= height - 1; x++){
    for(int y =0; y<= width-1; y++){
      //outline top and bottom
      if(x == 0 || x == height - 1){
        if(y== 0 || y==width_1 || y == width_2 || y == width_3){
          cout << "+";
        }else{
          cout <<"-";
        }
        continue;
      }

      //middle boundaries
      if(y== 0 || y==width_1 || y == width_2 || y == width_3){
        cout << "|";
        continue;
      }

      //reel[0]
      if(y <= width_1 -1){
        if(x > reel[0]->calculate_box_height()){
          cout <<" ";
          continue;
        }
        cout << reel[0]->str_rep[x-1][y-1];
        continue;
      }

      //reel[1]
      if(y <= width_2 -1){
        if(x > reel[1]->calculate_box_height()){
          cout <<" ";
          continue;
        }
        cout << reel[1]->str_rep[x-1][y- width_1 - 1];
        continue;
      }

      //reel[2]
      if(y <= width_3 -1){
        if(x > reel[2]->calculate_box_height()){
          cout <<" ";
          continue;
        }
        cout << reel[2]->str_rep[x-1][y- width_2 - 1];
        continue;
      }
    }
    cout << endl;
  }
}

void SlotMachine::release_shapes(){
  delete this->reel[0];
  delete this->reel[1];
  delete this->reel[2];
}

void SlotMachine::report_status(){
  cout << "(" << reel[0]->get_generic_name() << "," << reel[0]->calculate_box_height() << "," << reel[0]->calculate_box_width() <<")";
  cout << "(" << reel[1]->get_generic_name() << "," << reel[1]->calculate_box_height() << "," << reel[1]->calculate_box_width() <<")";
  cout << "(" << reel[2]->get_generic_name() << "," << reel[2]->calculate_box_height() << "," << reel[2]->calculate_box_width() <<")" << endl;

  string abc = reel[0]->get_generic_name();
  string def = reel[1]->get_generic_name();
  string ghi = reel[2]->get_generic_name();
  int a = reel[0]->calculate_box_width();
  int b = reel[1]->calculate_box_width();
  int c = reel[2]->calculate_box_width();

  int d = reel[0]->calculate_box_height();
  int e = reel[1]->calculate_box_height();
  int f = reel[2]->calculate_box_height();


  if(abc == def && abc == ghi && ghi == def && a == b && b == c && c == a && d==e && e==f && f==d){
    cout << "You win bet!!"<< endl;
    conversion = conversion * 3;
    tokens = tokens + conversion;
  }else if(abc == def && abc == ghi && ghi == def){
    cout << "You win bet!!"<< endl;
    conversion = conversion * 2;
    tokens = tokens + conversion;
  }else if(abc == def || abc == ghi ||def == ghi){
    cout << "You nither lose nor win!!" << endl;
  }else{
    tokens = tokens - conversion;
    cout << "You lose bet!!"<< endl;
  }
  cout <<"You now have "<<tokens <<" tokens!"<< endl;
}


void SlotMachine::run(){
  int rand_shape;
  int rand_width;
  int rand_height;

  random_device rd;

  mt19937 e2(rd());

  uniform_int_distribution<> dist_1(1, 4);

  uniform_int_distribution<> dist_2(1, 25);

  cout <<"Welcome to this 3-Reel Slot Machine Game!\n";
  cout <<"Each reel will randomly display one of four shapes, each in 25 sizes.\n";
  cout << "To win 3 times your bet you need 3 similar shapes of the same size.\n";
  cout << "To win 2 times your bet you need 3 similar shapes.\n";
  cout << "To win or lose nothing you need 2 similar shapes.\n";
  cout << "Otherwise , you lose your bet.\n";
  cout << "You start with 10 free tokens!"<<endl;

  // int tokenss = 10;

  string input;

  while(true){
    while(true){
      input = "";
      cout << "How much would you like to bet? (enter 0 to QUIT!!): ";
      getline(cin, input);
      input = regex_replace(input, regex(" "),"");
      if(!regex_match(input,regex("[0123]"))){
        cout << "Wrong Input!!"<<endl;
      }else{
        break;
      }
    }

    conversion = stoi(input);

    while( tokens - conversion < 0){
      cout << "You only have "<<tokens <<" tokens!!";
      while(true){
        input = "";
        cout << "How much would you like to bet? (enter 0 to QUIT!!): ";
        getline(cin, input);
        input = regex_replace(input, regex(" "),"");
        if(!regex_match(input,regex("[0123]"))){
          cout << "Wrong Input!!"<<endl;
        }else{
          break;
        }
      }
      conversion = stoi(input);
    }

    make_shapes();


    if(conversion == 0){
      cout << "BYE BYE !!" << endl;
      break;
    }
    display_shapes();
    report_status();
    if(tokens == 0){
      cout << "LOOOOOOOOOOSERRRR!!!  GAME OVER!!!!" << endl;
      break;
    }



  }
}
