#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"
#include<typeinfo>
#include<vector>
using namespace std;



class Rectangle : public Shape {
	public:
		int height;
		int width;
		Rectangle(int height, int width);
		Rectangle(int height, int width, string desc_name);
		~Rectangle();

		void generate_string_representation(){
			this->str_rep.resize(this->height);
			for (int x = 0; x <= this->height - 1; x++) {
				this->str_rep[x].resize(this->width);
				for (int y = 0; y <= this->width - 1; y++) {
					this->str_rep[x][y] ='*';
				}
			}
		}

		void scale(int factor) {
			if (this->height + factor >= 1 && this->width + factor >= 1) {
				this->height = this->height + factor;
				this->width = this->width + factor;
				this->generate_string_representation();
			}
		}

		float area() const{
			return float(height * width);
		}

		float perimeter() const{
			return float(2 * (height + width));
		}

		vector< vector<char> > draw(char penChar, char fillChar) const{
			const int breadth = this->height;
			const int length = this->width;
			vector< vector<char> > temp(breadth, vector<char>(length));
			for (int x = 0; x <= height - 1; x++) {
				for (int y = 0; y <= width - 1; y++) {
					temp[x].push_back(penChar);
				}
			}

			return temp;
		}

		vector< vector<char> > draw(char penChar) const{
			const int breadth = this->height;
			const int length = this->width;
			vector< vector<char> > temp(breadth, vector<char>(length));
			for (int x = 0; x <= height - 1; x++) {
				for (int y = 0; y <= width - 1; y++) {
					temp[x].push_back(penChar);
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
			return this->width;
		}

		float scrn_area() const{
			return this->height * this->width;
		}

		float scrn_perimeter() const{
			return (2 * (height + width)) - 4;
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
			cout << draw( penChar, fillChar) << endl;
		}

		void draw_on_screen(char penChar) const{
			cout << draw( penChar) << endl;
		}

		void draw_on_screen() const{
			cout << draw() << endl;
		}


};


#endif // !RECTANGLE_H
