#include <iostream>

using namespace std;

class Box
{
    public:
        double getvolume(void); //获得面积
        void setlength(double len);//设置长度
        void setheight(double hei);//设置宽度
        void setbreadth(double bre);//设置高度
        Box operator+(const Box &b){
            Box box;
            box.length = this->length + b.length;
            box.heigth = this->heigth + b.heigth;
            box.breadth = this->breadth + b.breadth;
            return box;
        }
    private:
        double length;
        double heigth;
        double breadth;

};

double Box::getvolume(void){

    return length * heigth * breadth;
}


void Box::setlength(double len){

    length = len;
}

void Box::setheight(double hei){

    heigth = hei;
}

void Box::setbreadth(double bre){

    breadth = bre;
}

int main( )
{
   Box Box1;                // 声明 Box1，类型为 Box
   Box Box2;                // 声明 Box2，类型为 Box
   Box Box3;                // 声明 Box3，类型为 Box
   double volume = 0.0;     // 把体积存储在该变量中
 
   // Box1 详述
   Box1.setlength(6.0); 
   Box1.setbreadth(7.0); 
   Box1.setheight(5.0);
 
   // Box2 详述
   Box2.setlength(12.0); 
   Box2.setbreadth(13.0); 
   Box2.setheight(10.0);
 
   // Box1 的体积
   volume = Box1.getvolume();
   cout << "Volume of Box1 : " << volume <<endl;
 
   // Box2 的体积
   volume = Box2.getvolume();
   cout << "Volume of Box2 : " << volume <<endl;
 
   // 把两个对象相加，得到 Box3
   Box3 = Box1 + Box2;
 
   // Box3 的体积
   volume = Box3.getvolume();
   cout << "Volume of Box3 : " << volume <<endl;
   
   return 0;
}
