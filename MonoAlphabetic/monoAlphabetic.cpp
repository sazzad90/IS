#include<bits\stdc++.h>
#define N 5
using namespace std;
int main(){
   string str;
   cout<<"Enter text: "<<endl;
   cin>>str;
   cout<<"Plain text: "<<str<<endl;
   for(int i = 0;i<str.size();i++){

       if(str[i] >='a' && str[i] <= 'z'){
           str[i] = 'a' + (str[i] + N - 'a') % 26;
       }
       else if(str[i] >='A' && str[i] <= 'Z'){
            str[i] = 'A' + (str[i] + N- 'A') % 26 ;
       }


   }
   cout<<"cipher text: "<<str<<endl;

   for(int i = 0;i<str.size();i++){

       if(str[i] >='a' && str[i] <= 'z'){
           str[i] = 'a' + (str[i] - N - 'a' + 26) % 26;
       }
       else if(str[i] >='A' && str[i] <= 'Z'){
            str[i] = 'A' + (str[i] - N- 'A' + 26 ) % 26 ;
       }


   }
   cout<<"Decrypted text: "<<str<<endl;
}
