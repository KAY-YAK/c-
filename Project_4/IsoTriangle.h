#ifndef IsoTriangle_H
#define IsoTriangle_H
#include"Triangle.h"
#include<typeinfo>
#include<string>
#include <cmath>



class IsoTriangle : public Triangle {
	public:
		int height;
		int base;
		IsoTriangle(int base);
    IsoTriangle(int base, string desc_name);
		~IsoTriangle();

		void generate_string_representation(){
			this->str_rep.resize(this->height);
      int point = (this->base / 2) ;
      int count = 0;
			for (int x = 0; x <= this->height - 1; x++) {
				this->str_rep[x].resize(this->base);
				for (int y = 0; y <= this->base - 1; y++) {
          if(y >= point - count && y<= point + count){
            this->str_rep[x][y] ='*';
          }else{
            this->str_rep[x][y] =' ';
          }
				}
        count++;
			}
		}

		void scale(int factor) {
			if (this->base + (2 * factor) >= 1) {
				this->base = this->base +  (2 * factor);
        this->height = (this->base + 1)/2;
				this->generate_string_representation();
			}
		}

		float area() const{
			return float(float(this->height * this->base)/2);
		}

		float perimeter() const{
      int b_sq = this->base * this->base;
      int h_sq = this->height * this->height;
			return float(this->base + (2 * pow(((.25 * b_sq) + h_sq), .5)));
		}

		vector< vector<char> > draw(char penChar, char fillChar) const{
			const int b = this->base;
			const int h = this->height;
			vector< vector<char> > temp(h, vector<char>(b));
      int point = (this->base / 2) ;
      int count = 0;
			for (int x = 0; x <= this->height - 1; x++) {
				for (int y = 0; y <= this->base - 1; y++) {
          if(y >= point - count && y<= point + count){
            temp[x].push_back(penChar);

          }else{
            temp[x].push_back(fillChar);

          }
				}
        count++;
			}
			return temp;
		}

    vector< vector<char> > draw(char penChar) const{
			const int b = this->base;
			const int h = this->height;
			vector< vector<char> > temp(h, vector<char>(b));
      int point = (this->base / 2) ;
      int count = 0;
			for (int x = 0; x <= this->height - 1; x++) {
				for (int y = 0; y <= this->base - 1; y++) {
          if(y >= point - count && y<= point + count){
            temp[x].push_back(penChar);

          }else{
            temp[x].push_back(' ');

          }
				}
        count++;
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
			return float(this->height * this->height);
		}

		float scrn_perimeter() const{
			return float(4 * (this->height - 1));
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
      cout << this->draw( penChar, fillChar) << endl;
    }

    void draw_on_screen(char penChar) const{
      cout << this->draw( penChar) << endl;
    }

    void draw_on_screen() const{
      cout << this->draw() << endl;
    }



};



#endif // !IsoTriangle_H
