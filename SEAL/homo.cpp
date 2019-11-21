#include "seal/seal.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace seal;

int main(int argc, char* argv[])
{	
	const char * private_out = "homo.private" , *public_out = "homo.public";

	ofstream fidOut1;
	ofstream fidOut2;

	/*SEAL_BYTE*/
	

	/*opening files*/
	fidOut1.open(private_out, ofstream::out | ofstream::trunc );
	fidOut2.open(public_out, ofstream::out | ofstream::trunc );


	/*initializing parameters using the BFV scheme*/
	EncryptionParameters parms(scheme_type::BFV);


	/*assigning poly_modulus degree*/
	size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);


    /*setting plain text modulus*/
    parms.set_plain_modulus(256);


    /*setting coef_modulus*/
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    /* noise budget : ~ log2(coeff_modulus/plain_modulus)  = (bits) */

    /*creating context*/
    auto context = SEALContext::Create(parms);


    /*creating key generator*/
    KeyGenerator keygen(context);


    /*generating homomorphic key pair*/
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
  	
    /*saving key to files*/
  	secret_key.save(fidOut1);
  	public_key.save(fidOut2);

  	/*closing files*/
  	fidOut1.close();
    fidOut2.close();

	return 0;
}
