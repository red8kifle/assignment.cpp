#include <iostream>
using namespace std;
#define tax_rate_by_preprocessor 0.15
int main ( ) {
  cout<<"This C++ Program is  used to analyzes product sales and inventory for a store. \n";
  cout<<"Remember that C++ is a compiled language. \n";
  
  // 2. product detail
  string product_name;
  int product_category ;
  int initial_inventory;
  float product_price;
  int num_of_items_sold;
  
   double totalSalesAmount;
   string inventory_status;
   
   //4.Demonstrate different Initialization methods
   int forDirect=100;       //direct initialization
   float forAssign;
   forAssign=10.5F;  //Assignment after declaration
   int forList{15};    //List initialization
   
    //5
  auto totalSalesCopy= totalSalesAmount;
  decltype(initial_inventory)inventoryNew= 50;
   
  const double tax_rate_by_const = 0.15;
  
  cout<<"Enter product name፦          ";
  cin>>product_name;
  cout<<"you entered"<<" "<< product_name<<"."<< endl;
  cout<< "Enter product category number(1-5):-  \n ";
  cin>>product_category;
  if(product_category >=1 && product_category <= 5){
   cout<<"you entered a correct category number!   \n ";
  switch (product_category){
        case 1:
              cout<<"Category 1: Electronics   \n";
              break;
        case 2:
              cout<<"Category 2:Groceries \n";
              break;
        case 3:
              cout<<"Category 3 : Clothing \n";
              break;
        case 4:
               cout<<"Category 4 : Stationery \n";
        case 5:
                cout<<"Category 5: Miscellaneous \n";              }
  }else{ 
          cout<<"you entered an incorrect category number.please enter a correct category number.\n";
          cin>>product_category;
           switch (product_category){
        case 1:
              cout<<"Category 1: Electronics   \n";
              break;
        case 2:
              cout<<"Category 2:Groceries \n";
              break;
        case 3:
              cout<<"Category 3 : Clothing \n";
              break;
        case 4:
               cout<<"Category 4 : Stationery \n";
        default:
                cout<<"Category 5: Miscellaneous \n";              }
  }
                
  cout<<"Enter initial inventory quantity:-  \n ";  cin>> initial_inventory;
  cout<<"Enter product price:-  \n";
  cin>>product_price;
  cout<<"Enter number of items sold:- \n ";
  cin>>num_of_items_sold;
  
  //computed values
  
 int new_inventory= initial_inventory - num_of_items_sold;
 totalSalesAmount= num_of_items_sold* product_price;
 inventory_status=(new_inventory < 10)?"Low Inventory":"Sufficient";
 
 for(int i=1; i<=num_of_items_sold; ++i){
  cout<<"Item"<<i<<": price:- $"<<product_price<<endl;
 }
 
 //all out puts
 cout<<"The tax rate is" << tax_rate_by_preprocessor<<
 "."<<endl;
 cout <<"The tax rate is"<< tax_rate_by_const<<"."<<endl;
 cout<<"The new inventory is "<<new_inventory<<"."<<endl;
 cout<<"The total sale is "<<totalSalesAmount<<"."<<endl;
 cout<<"The inventory status is "<<   inventory_status<<"."<<endl;
 cout<<"Copy of total sale="<<totalSalesCopy<<endl;
 cout<<"Additional Inventory="<<inventoryNew;
 
return 0 ;
}