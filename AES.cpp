#include<bits\stdc++.h>

using namespace std;

struct Word{
    string bytes[4];
}word[44];

string stateKey[4][4];
string stateMatrix[4][4];

string extendedKey[176];
int z = 4;

string roundConstant[10] = {"01","02","04","08","10","20","40","80","1B","36"};
string S_Box[16][16]=
{
    "63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76",
    "CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0",
    "B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15",
    "04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75",
    "09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84",
    "53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF",
    "D0", "EF",	"AA", "FB",	"43", "4D",	"33", "85",	"45", "F9",	"02", "7F",	"50", "3C",	"9F", "A8",
    "51", "A3",	"40", "8F",	"92", "9D",	"38", "F5",	"BC", "B6", "DA", "21", "10", "FF", "F3", "D2",
    "CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73",
    "60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB",
    "E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79",
    "E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56",	"F4", "EA", "65", "7A", "AE", "08",
    "BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A",
    "70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E",
    "E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF",
    "8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"

};

 string Table_for_2[] ={
"00", "02", "04", "06", "08", "0A", "0C", "0E", "10", "12", "14", "16", "18", "1A", "1C", "1E",
"20", "22", "24", "26", "28", "2A", "2C", "2E", "30", "32", "34", "36", "38", "3A", "3C", "3E",
"40", "42", "44", "46", "48", "4A", "4C", "4E", "50", "52", "54", "56", "58", "5A", "5C", "5E",
"60", "62", "64", "66", "68", "6A", "6C", "6E", "70", "72", "74", "76", "78", "7A", "7C", "7E",
"80", "82", "84", "86", "88", "8A", "8C", "8E", "90", "92", "94", "96", "98", "9A", "9C", "9E",
"A0", "A2", "A4", "A6", "A8", "AA", "AC", "AE", "B0", "B2", "B4", "B6", "B8", "BA", "BC", "BE",
"C0", "C2", "C4", "C6", "C8", "CA", "CC", "CE", "D0", "D2", "D4", "D6", "D8", "DA", "DC", "DE",
"E0", "E2", "E4", "E6", "E8", "EA", "EC", "EE", "F0", "F2", "F4", "F6", "F8", "FA", "FC", "FE",
"1B", "19", "1F", "1D", "13", "11", "17", "15", "0B", "09", "0F", "0D", "03", "01", "07", "05",
"3B", "39", "3F", "3D", "33", "31", "37", "35", "2B", "29", "2F", "2D", "23", "21", "27", "25",
"5B", "59", "5F", "5D", "53", "51", "57", "55", "4B", "49", "4F", "4D", "43", "41", "47", "45",
"7B", "79", "7F", "7D", "73", "71", "77", "75", "6B", "69", "6F", "6D", "63", "61", "67", "65",
"9B", "99", "9F", "9D", "93", "91", "97", "95", "8B", "89", "8F", "8D", "83", "81", "87", "85",
"BB", "B9", "BF", "BD", "B3", "B1", "B7", "B5", "AB", "A9", "AF", "AD", "A3", "A1", "A7", "A5",
"DB", "D9", "DF", "DD", "D3", "D1", "D7", "D5", "CB", "C9", "CF", "CD", "C3", "C1", "C7", "C5",
"FB", "F9", "FF", "FD", "F3", "F1", "F7", "F5", "EB", "E9", "EF", "ED", "E3", "E1", "E7", "E5"
};

 string Table_for_3[] ={
"00", "03", "06", "05", "0C", "0F", "0A", "09", "18", "1B", "1E", "1D", "14", "17", "12", "11",
"30", "33", "36", "35", "3C", "3F", "3A", "39", "28", "2B", "2E", "2D", "24", "27", "22", "21",
"60", "63", "66", "65", "6C", "6F", "6A", "69", "78", "7B", "7E", "7D", "74", "77", "72", "71",
"50", "53", "56", "55", "5C", "5F", "5A", "59", "48", "4B", "4E", "4D", "44", "47", "42", "41",
"C0", "C3", "C6", "C5", "CC", "CF", "CA", "C9", "D8", "DB", "DE", "DD", "D4", "D7", "D2", "D1",
"F0", "F3", "F6", "F5", "FC", "FF", "FA", "F9", "E8", "EB", "EE", "ED", "E4", "E7", "E2", "E1",
"A0", "A3", "A6", "A5", "AC", "AF", "AA", "A9", "B8", "BB", "BE", "BD", "B4", "B7", "B2", "B1",
"90", "93", "96", "95", "9C", "9F", "9A", "99", "88", "8B", "8E", "8D", "84", "87", "82", "81",
"9B", "98", "9D", "9E", "97", "94", "91", "92", "83", "80", "85", "86", "8F", "8C", "89", "8A",
"AB", "A8", "AD", "AE", "A7", "A4", "A1", "A2", "B3", "B0", "B5", "B6", "BF", "BC", "B9", "BA",
"FB", "F8", "FD", "FE", "F7", "F4", "F1", "F2", "E3", "E0", "E5", "E6", "EF", "EC", "E9", "EA",
"CB", "C8", "CD", "CE", "C7", "C4", "C1", "C2", "D3", "D0", "D5", "D6", "DF", "DC", "D9", "DA",
"5B", "58", "5D", "5E", "57", "54", "51", "52", "43", "40", "45", "46", "4F", "4C", "49", "4A",
"6B", "68", "6D", "6E", "67", "64", "61", "62", "73", "70", "75", "76", "7F", "7C", "79", "7A",
"3B", "38", "3D", "3E", "37", "34", "31", "32", "23", "20", "25", "26", "2F", "2C", "29", "2A",
"0B", "08", "0D", "0E", "07", "04", "01", "02", "13", "10", "15", "16", "1F", "1C", "19", "1A"
};


int hexToDec(string num) {
   int len = num.size();
   int base = 1;
   int temp = 0;
   for (int i=len-1; i>=0; i--) {
      if (num[i]>='0' && num[i]<='9') {
         temp += (num[i] - 48)*base;
         base = base * 16;
      }
      else if (num[i]>='A' && num[i]<='F') {
         temp += (num[i] - 55)*base;
         base = base*16;
      }
   }
   return temp;
}

string decToHex(char c){
    string hexNum = "";
    long decimalNum, quotient, remainder;
    int  j = 0;
    quotient = c;

    while (quotient != 0){
        remainder = quotient % 16;
        if (remainder < 10)
            hexNum += 48 + remainder;
        else
            hexNum += 55 + remainder;
        quotient = quotient / 16;
    }
    return hexNum;
}


// Hexadecimal to Binary Number
string HexToBin(string hexdec)
{
    long int i = 0;
    string bin = "";

    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            bin += "0000";
            break;
        case '1':
            bin += "0001";
            break;
        case '2':
            bin += "0010";
            break;
        case '3':
            bin += "0011";
            break;
        case '4':
            bin += "0100";
            break;
        case '5':
            bin += "0101";
            break;
        case '6':
            bin += "0110";
            break;
        case '7':
            bin += "0111";
            break;
        case '8':
            bin += "1000";
            break;
        case '9':
            bin += "1001";
            break;
        case 'A':
        case 'a':
            bin += "1010";
            break;
        case 'B':
        case 'b':
            bin += "1011";
            break;
        case 'C':
        case 'c':
            bin += "1100";
            break;
        case 'D':
        case 'd':
            bin += "1101";
            break;
        case 'E':
        case 'e':
            bin += "1110";
            break;
        case 'F':
        case 'f':
            bin += "1111";
            break;
        case ' ':
            bin += " ";
            break;
        default:
            cout << "\nInvalid hexadecimal digit "
                 << hexdec[i];
        }
        i++;
    }
    return bin;
}

string binToHex(string bin){
        int i =0;
        string hex = "";

        while(bin[i]){
        string tmp = bin.substr(i, 4);
        if      (!tmp.compare("0000")) hex += "0";
        else if (!tmp.compare("0001")) hex += "1";
        else if (!tmp.compare("0010")) hex += "2";
        else if (!tmp.compare("0011")) hex += "3";
        else if (!tmp.compare("0100")) hex += "4";
        else if (!tmp.compare("0101")) hex += "5";
        else if (!tmp.compare("0110")) hex += "6";
        else if (!tmp.compare("0111")) hex += "7";
        else if (!tmp.compare("1000")) hex += "8";
        else if (!tmp.compare("1001")) hex += "9";
        else if (!tmp.compare("1010")) hex += "A";
        else if (!tmp.compare("1011")) hex += "B";
        else if (!tmp.compare("1100")) hex += "C";
        else if (!tmp.compare("1101")) hex += "D";
        else if (!tmp.compare("1110")) hex += "E";
        else if (!tmp.compare("1111")) hex += "F";
        else continue;
        i += 4;
    }
    return hex;
}

string x_or(string a,string b){
    string c = "";
    int i = 0;
    while(a[i]){
        if(a[i] == b[i]){
            c += '0';
        }
        else
            c += '1';

    i++;
    }

    return c;
}

string subBytes(string x){
   int row = x[0], col = x[1];
   string y;

   if(row >= 48 && row <= 57) row = row - 48;
   else row = row - 55;

   if(col >= 48 && col <= 57) col = col - 48;
   else col = col - 55;

   y = S_Box[row][col];
   return y;
}

struct Word addRoundKey(int r){
    int wordNo = (r * 4) - 1;

    Word t;
    t.bytes[0] = word[wordNo].bytes[0];
    t.bytes[1] = word[wordNo].bytes[1];
    t.bytes[2] = word[wordNo].bytes[2];
    t.bytes[3] = word[wordNo].bytes[3];
    //circular left shift
    string temp = t.bytes[0];
    t.bytes[0] = t.bytes[1];
    t.bytes[1] = t.bytes[2];
    t.bytes[2] = t.bytes[3];
    t.bytes[3] = temp;

    //substitution bytes
    for(int i = 0;i < 4;i++){
        t.bytes[i] = subBytes(t.bytes[i]);
    }

    //adding round const
    t.bytes[0] = HexToBin(t.bytes[0]);
    string temp2 = roundConstant[r-1];
    temp2 = HexToBin(temp2);
    t.bytes[0] = x_or(t.bytes[0],temp2);
    t.bytes[0] = binToHex(t.bytes[0]);

    return t;
}

struct Word x_or_word(Word word1,Word word2){
    Word w;
    word1.bytes[0] = HexToBin(word1.bytes[0]);
    word1.bytes[1] = HexToBin(word1.bytes[1]);
    word1.bytes[2] = HexToBin(word1.bytes[2]);
    word1.bytes[3] = HexToBin(word1.bytes[3]);

    word2.bytes[0] = HexToBin(word2.bytes[0]);
    word2.bytes[1] = HexToBin(word2.bytes[1]);
    word2.bytes[2] = HexToBin(word2.bytes[2]);
    word2.bytes[3] = HexToBin(word2.bytes[3]);

    w.bytes[0] = x_or(word1.bytes[0],word2.bytes[0]);
    w.bytes[1] = x_or(word1.bytes[1],word2.bytes[1]);
    w.bytes[2] = x_or(word1.bytes[2],word2.bytes[2]);
    w.bytes[3] = x_or(word1.bytes[3],word2.bytes[3]);

    w.bytes[0] = binToHex(w.bytes[0]);
    w.bytes[1] = binToHex(w.bytes[1]);
    w.bytes[2] = binToHex(w.bytes[2]);
    w.bytes[3] = binToHex(w.bytes[3]);

    return w;

};

void extendKey(){
    int keyLength = 16,x = 4,y = 0,wordLength = 4;
    for(int i = 1;i <= 10;i++){
        Word t = addRoundKey(i);
        word[wordLength++] = x_or_word(t,word[y++]);
        word[wordLength++] = x_or_word(word[x++],word[y++]);
        word[wordLength++] = x_or_word(word[x++],word[y++]);
        word[wordLength++] = x_or_word(word[x++],word[y++]);
        x++;

    }
}

void subBytes_matrix(){
    cout<<"after sub_bytes: "<<endl;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            stateMatrix[i][j] = subBytes(stateMatrix[i][j]);
            cout<<stateMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void shiftRows(){
    string temp = stateMatrix[1][0];
    stateMatrix[1][0] = stateMatrix[1][1];
    stateMatrix[1][1] = stateMatrix[1][2];
    stateMatrix[1][2] = stateMatrix[1][3];
    stateMatrix[1][3] = temp;

    temp = stateMatrix[2][0];
    stateMatrix[2][0] = stateMatrix[2][2];
    stateMatrix[2][2] = temp;
    temp = stateMatrix[2][1];
    stateMatrix[2][1] = stateMatrix[2][3];
    stateMatrix[2][3] = temp;

    temp = stateMatrix[3][0];
    stateMatrix[3][0] = stateMatrix[3][3];
    stateMatrix[3][3] = stateMatrix[3][2];
    stateMatrix[3][2] = stateMatrix[3][1];
    stateMatrix[3][1] = temp;

    cout<<"after sub bytes: "<<endl;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout<<stateMatrix[i][j]<<" ";
        }cout<<endl;
    }
    cout<<endl;

}

void mixCol(){
    string state[16],state2[16];
 //   string mixMatrix[4][4];
    string temp1;
    string temp2;

    int k = 0;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            state[k] = stateMatrix[j][i];
            state2[k] = stateMatrix[j][i];
            k++;
        }
    }

    for(int i = 0;i < 16;i++){
            if(i%4 == 0){
            temp1 = x_or(HexToBin(Table_for_2[hexToDec(state[i])]),HexToBin(Table_for_3[hexToDec(state[i+1])]));
            temp2 = x_or(HexToBin(state[i+2]),HexToBin(state[i+3]));
            state2[i] = x_or(temp1,temp2);
            state2[i] = binToHex(state2[i]);
            }
            if(i%4 == 1){
            temp1 = x_or(HexToBin(Table_for_2[hexToDec(state[i])]),HexToBin(Table_for_3[hexToDec(state[i+1])]));
            temp2 = x_or(HexToBin(state[i+2]),HexToBin(state[i-1]));
            state2[i] = x_or(temp1,temp2);
            state2[i] = binToHex(state2[i]);
            }
            if(i%4 == 2){
            temp1 = x_or(HexToBin(Table_for_2[hexToDec(state[i])]),HexToBin(Table_for_3[hexToDec(state[i+1])]));
            temp2 = x_or(HexToBin(state[i-1]),HexToBin(state[i-2]));
            state2[i] = x_or(temp1,temp2);
            state2[i] = binToHex(state2[i]);
            }
            if(i%4 == 3){
            temp1 = x_or(HexToBin(Table_for_2[hexToDec(state[i])]),HexToBin(Table_for_3[hexToDec(state[i-3])]));
            temp2 = x_or(HexToBin(state[i-1]),HexToBin(state[i-2]));
            state2[i] = x_or(temp1,temp2);
            state2[i] = binToHex(state2[i]);
            }
        }

        k = 0;
        for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            stateMatrix[j][i] = state2[k];
            k++;
        }
    }

     cout<<"after mixcol: "<<endl;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout<<stateMatrix[i][j]<<" ";
        }cout<<endl;
    }
    cout<<endl;

}

void addRoundKey_matrix(){
     int k = 0;
     for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            stateMatrix[j][i] = binToHex(x_or(HexToBin(stateMatrix[j][i]),HexToBin(word[z].bytes[k++])));
            if(k == 4){
                k = 0;
                z++;
            }
        }
     }
     cout<<"after addroundkey: "<<endl;
     for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout<<stateMatrix[i][j]<<" ";
        }cout<<endl;
    }
    cout<<endl;
}

void encrypt(){
    /***************Round 0*************/
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            string temp1 = HexToBin(stateMatrix[j][i]);
            string temp2 = HexToBin(word[i].bytes[j]);
            stateMatrix[j][i] = x_or(temp1,temp2);
            stateMatrix[j][i] = binToHex(stateMatrix[j][i]);
        }
    }

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout<<stateMatrix[i][j]<<" ";
        }cout<<endl;
    }
    cout<<endl;

    /************Round 1-9**************/
    for(int i = 1;i<=9;i++){
    subBytes_matrix();
    shiftRows();
    mixCol();
    addRoundKey_matrix();
    }

    /************Round 10**************/
    subBytes_matrix();
    shiftRows();
    addRoundKey_matrix();
}

int main(){
    string  hexadecimalKey = "", plaintext = "Two One Nine Two", key = "Thats my Kung Fu";

    //converting key into hex values
    int i = 0,j = 0,k = 0;
    while(key[i]){
    string str = decToHex(key[i]);
    reverse(str.begin(),str.end());
    word[j].bytes[k++] = str;
    if(k == 4){
        j++;
        k = 0;
    }
    extendedKey[i] = str;
    i++;
    }

    cout<<"Extended Key: "<<endl;
    extendKey();
    int cnt = 0;
    for(int i = 0;i < 44;i++){
        for(int j = 0;j < 4;j++){
        cout<<word[i].bytes[j]<<" ";
        }
        cnt++;
        if(cnt == 4){
            cout<<endl;
            cnt = 0;
        }
    }

    //converting text into hex values
    int l = 0,r = 0,c = 0;
    while(plaintext[l]){
    string str = decToHex(plaintext[l]);
    reverse(str.begin(),str.end());
    stateMatrix[r++][c] = str;
    if(r == 4){
        c++;
        r = 0;
    }
    l++;
    }

    encrypt();

    cout<<"cipher text: "<<endl;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            cout<<stateMatrix[j][i]<<" ";
        }
    }
    cout<<endl;
    }


