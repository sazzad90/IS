//rounds = 80
//each round->QWord(generated from plaintext) = 64 bits
//each round->constant k

//buffers
//->stores intermediate result
//->stores output(hash code)
//->each buffer size = 64 bit
//->total buffers = 8


#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int  li;


string HEX(string bin)
{
    if (bin == "0000") return "0";
    else if (bin == "0001") return "1";
    else if (bin == "0010") return "2";
    else if (bin == "0011") return "3";
    else if (bin == "0100") return "4";
    else if (bin == "0101") return "5";
    else if (bin == "0110") return "6";
    else if (bin == "0111") return "7";
    else if (bin == "1000") return "8";
    else if (bin == "1001") return "9";
    else if (bin == "1010") return "A";
    else if (bin == "1011") return "B";
    else if (bin == "1100") return "C";
    else if (bin == "1101") return "D";
    else if (bin == "1110") return "E";
    else return "F";
}

string decToHex( li dec)
{
    string bin= bitset<64>(dec).to_string();

    string hex, tmp;

    for(int i=0; i<bin.length(); i+=4){
        tmp= bin.substr(i, 4);
        hex+=HEX(tmp);
    }

    return hex;
}

li message[1024]={};

const li constants[80] = {
        0x428a2f98d728ae22, 0x7137449123ef65cd,0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,0x3956c25bf348b538,
        0x59f111f1b605d019,0x923f82a4af194f9b, 0xab1c5ed5da6d8118,0xd807aa98a3030242, 0x12835b0145706fbe,
        0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,0x72be5d74f27b896f, 0x80deb1fe3b1696b1,0x9bdc06a725c71235,
        0xc19bf174cf692694,0xe49b69c19ef14ad2, 0xefbe4786384f25e3,0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
        0x2de92c6f592b0275, 0x4a7484aa6ea6e483,0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,0x983e5152ee66dfab,
        0xa831c66d2db43210,0xb00327c898fb213f, 0xbf597fc7beef0ee4,0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70,0x27b70a8546d22ffc, 0x2e1b21385c26c926,0x4d2c6dfc5ac42aed,
        0x53380d139d95b3df,0x650a73548baf63de, 0x766a0abb3c77b2a8,0x81c2c92e47edaee6, 0x92722c851482353b,
        0xa2bfe8a14cf10364, 0xa81a664bbc423001,0xc24b8b70d0f89791, 0xc76c51a30654be30,0xd192e819d6ef5218,
        0xd69906245565a910,0xf40e35855771202a, 0x106aa07032bbd1b8,0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
        0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,0x5b9cca4f7763e373,
        0x682e6ff3d6b2b8a3,0x748f82ee5defb2fc, 0x78a5636f43172f60,0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9,0xbef9a3f7b2c67915, 0xc67178f2e372532b,0xca273eceea26619c,
        0xd186b8c721c0c207,0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,0x06f067aa72176fba, 0x0a637dc5a2c898a6,
        0x113f9804bef90dae, 0x1b710b35131c471b,0x28db77f523047d84, 0x32caab7b40c72493,0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c,0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

 li rotateRight( li val,  li pos){
    return ( (val >> pos) | (val << 64-pos) );
}

 li liodec(string bin){
    return bitset<64>(bin).to_ullong();
}
 li shiftRight( li val,  li pos){
    return (val >> pos);
}

void divideBlocks(string block)
{
     li blockNum = 0;

    for( li i=0; i<block.length(); i+=64, blockNum++) message[blockNum]= liodec(block.substr(i, 64));

    for( li i=16; i<80; i++){

         li wordA= rotateRight(message[i-2], 19) ^ rotateRight(message[i-2], 61) ^ shiftRight(message[i-2], 6);
         li wordB= message[i-7];
         li wordC=  rotateRight(message[i-15], 1) ^ rotateRight(message[i-15], 8) ^ shiftRight(message[i-15], 7);
         li wordD= message[i-16];


        message[i]= wordA+ wordB+ wordC+ wordD;
    }
}

 li ch_val( li a,  li b,  li c)
{
    return ( (a & b) ^ (~a & c));
}

 li sigmaE( li a)
{
    return ( rotateRight(a, 14) ^ rotateRight(a, 18) ^ rotateRight(a, 41) );
}

 li sigmaA( li a)
{
    return ( rotateRight(a, 28) ^ rotateRight(a, 34) ^ rotateRight(a, 39) );
}

 li major( li a,  li b,  li c)
{
    return ( (a & b) ^ (b & c) ^ (c & a) );
}

void  func( li a,  li b,  li c,  li& d,  li e,  li f,  li g,  li& h,  li cont)
{
     li t1= h+ ch_val(e, f, g)+ sigmaE(e)+ message[cont]+ constants[cont];
     li t2= sigmaA(a)+ major(a, b, c);

    d+= t1;
    h= t1+ t2;
}

string SHA(string str)
{
    stringstream input;

    for( li i = 0; i<str.length(); i++){
        input<< bitset<8>(str[i]);
    }

    string inputBlock;

    inputBlock = input.str();

     li strLen = inputBlock.length();
     li mod = strLen%1024;
     li temp;

    if(1024 - mod >= 128) temp = 1024-mod;
    else temp  = 2048- mod;

    inputBlock+="1";

    for( li i = 0; i<temp-129; i++) inputBlock+="0";

    string len_bits = bitset<128>(strLen).to_string();

    inputBlock+=len_bits;


     li totalBlocks = inputBlock.length()/1024;
     li blockNum = 0;
    string blocks[totalBlocks+1];

    for( li i = 0; i<inputBlock.length(); i+=1024, blockNum++) blocks[blockNum]= inputBlock.substr(i, 1024);

     li A = 0x6a09e667f3bcc908;
     li B = 0xbb67ae8584caa73b;
     li C = 0x3c6ef372fe94f82b;
     li D = 0xa54ff53a5f1d36f1;
     li E = 0x510e527fade682d1;
     li F = 0x9b05688c2b3e6c1f;
     li G = 0x1f83d9abfb41bd6b;
     li H = 0x5be0cd19137e2179;

     li AA, BB, CC, DD, EE, FF, GG, HH;

    for( li i=0; i<totalBlocks; i++){

        divideBlocks (blocks[i]);

        AA = A;
        BB = B;
        CC = C;
        DD = D;
        EE = E;
        FF = F;
        GG = G;
        HH = H;

         li cnt=0;

        for( li j=0; j<10; j++){
             func(A, B, C, D, E, F, G, H, cnt);
            cnt++;
             func(H, A, B, C, D, E, F, G, cnt);
            cnt++;
             func(G, H, A, B, C, D, E, F, cnt);
            cnt++;
             func(F, G, H, A, B, C, D, E, cnt);
            cnt++;
             func(E, F, G, H, A, B, C, D, cnt);
            cnt++;
             func(D, E, F, G, H, A, B, C, cnt);
            cnt++;
             func(C, D, E, F, G, H, A, B, cnt);
            cnt++;
             func(B, C, D, E, F, G, H, A, cnt);
            cnt++;
        }

        A += AA;
        B += BB;
        C += CC;
        D += DD;
        E += EE;
        F += FF;
        G += GG;
        H += HH;

    }

    stringstream outputString;

    outputString<<decToHex(A);
    outputString<<decToHex(B);
    outputString<<decToHex(C);
    outputString<<decToHex(D);
    outputString<<decToHex(E);
    outputString<<decToHex(F);
    outputString<<decToHex(G);
    outputString<<decToHex(H);

    return outputString.str();
}

int main()
{
    string str = "hashing is fun";

    string sha = SHA(str);

    cout<<"Given string: "<<str<<endl;
    cout<<"Hash value: "<<sha<<endl;
}
