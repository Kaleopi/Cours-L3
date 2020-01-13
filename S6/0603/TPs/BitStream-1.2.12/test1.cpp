//
// Created by Thomas on 06/01/2020.
//
#include <iostream>
#include <iomanip>
#include <limits>
#include "BitFloat.h"
#include "BitBase.h"
#include "BitBlock.h"
#include "BitStream.h"
#include <vector>

using namespace std;

int main(){
    const int val = 1350;
    int x = val;
    cout << "entier x = " << x << endl;
    cout << "en binaire: " << Bits::Binary(x) << endl;
    cout << "en binaire par paquet de 8: " << Bits::Binary(x,8) << endl;
    cout << "en binaire à partir du 24ème bit: " << Bits::Binary(x,8,24) << endl;
    cout << endl;

    // block de bits (taille fixe, support dépendant du nombre de bits à la déclaration)
    Bits::Block<12>  y(val);
    cout << "Bloc binaire de taille constante" << endl;
    cout << "Bits::Block y = " << y << endl;
    cout << "value = " << y.get() << endl;
    cout << "taille du support = " << sizeof(Bits::Block<12>::Type) << " bytes" << endl;
    cout << endl;

    // block de bits (taille variable)
    Bits::varBlock  z(12,val);
    cout << "Bloc binaire de taille variable" << endl;
    cout << "Bits::varBlock z = " << z << endl;
    cout << "value = " << z.get() << endl;
    cout << "taille du support = " << sizeof(Bits::varBlock::Type) << " bytes" << endl;
    cout << "changement du nombre de bits valides à 4 bits" << endl;
    z.set_valid(4);
    cout << "Bits::varBlock z = " << z << endl;
    cout << "value = " << z.get() << endl;
    cout << endl;




    const int NbValues = 24;
    vector<int>  v;
    v.reserve(NbValues);

    for(int i=0;i<NbValues;++i) v.push_back( get(y,i) );

    // affichage des valeurs dans le vecteur
    cout << "Valeurs du vecteur: ";
    for(int x : v) cout << x << " ";
    cout << endl;

    // codage dans des blocks de 5 bits
    cout << "Copie dans un vecteur de Bit::Block<8>" << endl;
    vector<Bits::Block<8>>    vIn,vOut;
    using StorageType = Bits::Block<8>::Type; // = uint8_t, uint16_t, uint32_t ou uint64_t suivant le nb de bits
    // note: cast pour éviter les warnings int -> uintX_t avec X=8 ou 16.
    for(int x : v) vIn.push_back( StorageType(x) );
    cout << "Valeurs du vecteur: ";
    for(auto x : vIn) cout << x << " ";
    cout << endl;






    cout << "creation bitstream"<<endl;
    cout << "Creation du Bit::Stream 1" << endl;
    Bits::Stream			stream1;
    cout << "Ecriture du vecteur Bit::Block<5> dans le stream" << endl;
    for(auto x : vIn) stream1 << x;
    cout << "Taille stockée dans le stream = 8 x "
         << vIn.size() << " = " << stream1.get_bit_size() << " bits" << endl;

    // affichage direct du contenu du stream
    cout << "Contenu de stream1: " << stream1 << endl;
    cout << "Contenu de stream1 (par paquets de 8): " << Binary(stream1,8) << endl;
    cout <<"FIIIN"<<endl;
    return 0;
}
