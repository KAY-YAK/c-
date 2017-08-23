#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H
#include"Triangle.h"
#include<typeinfo>
#include <cmath>




class RightTriangle : public Triangle {
	public:
		int height;
		int base;
		RightTriangle(int base);
    RightTriangle(int base, string desc_name);
		~RightTriangle();

		void generate_string_representation(){
			this->str_rep.resize(this->base);
			for (int x = 0; x <= this->base - 1; x++) {
				this->str_rep[x].resize(this->base);
				for (int y = 0; y <= this->base - 1; y++) {
          if(y <= x){
            this->str_rep[x][y] ='*';
          }else{
            this->str_rep[x][y] =' ';
          }
				}
			}
		}

		void scale(int factor) {
			if (this->base + factor >= 1) {
				this->height = this->height + factor;
				this->base = this->base + factor;
				this->generate_string_representation();
			}
		}

		float area() const{
			return float(float(this->height * this->base)/2);
		}

		float perimeter() const{
			return float((2 + pow(2,.5)) * this->base);
		}

		vector< vector<char> > draw(char penChar, char fillChar) const{
			const int b = this->base;
			const int h = this->height;
			vector< vector<char> > temp(b, vector<char>(h));
			for (int x = 0; x <= this->base - 1; x++) {
				for (int y = 0; y <= this->base - 1; y++) {
          if(y <= x){
            temp[x].push_back(penChar);

          }else{
            temp[x].push_back(fillChar);

          }
				}
			}

			return temp;
		}

    vector< vector<char> > draw(char penChar) const{
			const int b = this->base;
			const int h = this->height;
			vector< vector<char> > temp(b, vector<char>(h));
			for (int x = 0; x <= this->base - 1; x++) {
				for (int y = 0; y <= this->base - 1; y++) {
          if(y <= x){
            temp[x].push_back(penChar);

          }else{
            temp[x].push_back(' ');

          }
				}
			}

			return temp;
		}

    vector< vector<char> > draw() const{
      return this->str_rep;
    }

		float calculate_box_height() const{
			return this->height;
		}

		float calculate_box_width() const{
			return this->base;
		}

		float scrn_area() const{
			return float(float(this->height * (this->height + 1)) /2);
		}

		float scrn_perimeter() const{
			return float(3 * (height - 1));
		}

    string toString() const{
      string abcd;
      abcd = string("Shape Information") + "\n";
      abcd = abcd + "-----------------" + "\n";
      abcd = abcd + "Static type: " + typeid(this).name() + "\n";
      abcd = abcd + "Dynamic type: " + typeid(this).name() + "\n";
      abcd = abcd + "Generic Name: " + this->get_generic_name() + "\n";
      abcd = abcd + "Description: " + this->get_descriptive_name() + "\n";
      abcd = abcd + "id: " + to_string(this->get_id()) + "\n";
      abcd = abcd + "B. box width: " + to_string(this->calculate_box_width()) + "\n";
      abcd = abcd + "B. box height: " + to_string(this->calculate_box_height()) + "\n";
      abcd = abcd + "Scr area: " + to_string(this->scrn_area()) + "\n";
      abcd = abcd + "Geo area: " + to_string(this->area()) + "\n";
      abcd = abcd + "Scr Perimeter: " + to_string(this->scrn_perimeter()) + "\n";
      abcd = abcd + "Geo Perimeter: " + to_string(this->perimeter()) + "\n";
      return abcd;
    }

    void draw_on_screen(char penChar, char fillChar) const{
    	cout << draw(penChar, fillChar) << endl;
    }

    void draw_on_screen(char penChar) const{
    	cout << draw( penChar) << endl;
    }

    void draw_on_screen() const{
    	cout << draw() << endl;
    }



};



#endif // !RightTriangle_H
