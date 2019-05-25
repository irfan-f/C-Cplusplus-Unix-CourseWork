#include "cipher.h"

#define UPPER_CASE(r) ((r) - ('a' - 'A'))

// Error when using negative offset. a's will become w's and b's will become x's
// Only error that I have found through testing


struct Cipher::CipherCheshire {
    string cipherText;
};

Cipher::Cipher()
{
    smile = new CipherCheshire;
    smile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
}
Cipher::Cipher(string in)
{
    smile = new CipherCheshire;
    smile->cipherText = in;
}
string Cipher::encrypt(string raw)
{
    string retStr;
    cout << "Encrypting..." << endl;
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = 1;
        }
        if(upper) {
            retStr += UPPER_CASE(smile->cipherText[pos]);
        } else {
            retStr += smile->cipherText[pos];
        }
    }
    cout << "Done" << endl;

    return retStr;
}

string Cipher::decrypt(string enc)
{
    string retStr;
    
	cout << "Decrpyting..." << endl;
    // Fill in code here
	// Set string alphabet to reference, easier than making new Cipher 
	string alph = "abcdefghijklmnopqrstuvwxyz ";
	// Loop through each char
	for(unsigned int i = 0; i < enc.size(); i++) {
		// Search for the char in sipherText, tolower makes it a lowercase, so it matches
		std::size_t pos = smile->cipherText.find(tolower(enc[i]));
		// If it exists, search for it in pos in alphabet. add to str
		// Change case if in enc string the char is uppercase, UPPER_CASE(char)
		if(pos != std::string::npos) {
		    if(enc[i] <= 'Z' && enc[i] != ' ') {
				retStr += UPPER_CASE(alph[pos]);
			} else {
			    retStr += alph[pos];
			}
		}	
	}
    return retStr;
}




struct CaesarCipher::CaesarCipherCheshire : CipherCheshire {
     int rot;
};

CaesarCipher::CaesarCipher()
{
    // Fill in code here
	// New struct, set base text to alph, and rot to 0
	CaesarSmile = new CaesarCipherCheshire;;
	CaesarSmile->cipherText = "abcdefghijklmnopqrstuvwxyz ";
	CaesarSmile->rot = 0;;
}

CaesarCipher::CaesarCipher(string in, int rot)
{
    // Fill in code here
	// New struct, set text with in, and rot with rot.
	CaesarSmile = new CaesarCipherCheshire;
	CaesarSmile->cipherText = in;
	CaesarSmile->rot = rot;
}

string CaesarCipher::encrypt(string raw)
{
	// Exact same encrypt but you change postion by rot and modulo so it wraps
    string retStr;
    cout << "Encrypting..." << endl;
    // Fill in code here
    for(unsigned int i = 0; i < raw.size(); i++) {
        unsigned int pos;
        bool upper = false;
        if(raw[i] == ' ') {
            pos = 26;
        } else if(raw[i] >= 'a') {
            pos = raw[i] - 'a';
        } else {
            pos = raw[i] - 'A';
            upper = true;
        }
		if(upper == true) {
        	retStr += UPPER_CASE(CaesarSmile->cipherText[(pos + CaesarSmile->rot) % 27]);
       	} else {
           	retStr += CaesarSmile->cipherText[(pos + CaesarSmile->rot) % 27];
		}
	}
    cout << "Done" << endl;

    return retStr;

}

string CaesarCipher::decrypt(string enc)
{
	// Exact same decrypt as above, except postion is shifted by rot negatively
	// That will give the decipher
    string retStr;
    cout << "Decrpyting..." << endl;
    // Fill in code here
	string alph = "abcdefghijklmnopqrstuvwxyz ";
	for(unsigned int i = 0; i < enc.size(); i++) {
		std::size_t pos = CaesarSmile->cipherText.find(tolower(enc[i]));
		if(pos != std::string::npos) {
			int x = pos;
			x = (x - CaesarSmile->rot) % 27;
			// Edge case for negatives
			if (x < 0) {
				x += 27;
			}
			if(x == 26) {
				retStr += ' ';
			} else if(enc[i] <= 'Z' && enc[i] != ' ') {
				retStr += UPPER_CASE(alph[x]);
			} else {
				retStr += alph[x];
			}
		}		
	}
    return retStr;
}
// Implementation of extra credit
// No comments because look at it
// Simple, rest is in cipher.h, just declared the funcs.
void CaesarCipher::operator++() {
	CaesarSmile->rot += 1;
}

void CaesarCipher::operator--() {
	CaesarSmile->rot -= 1;
}
