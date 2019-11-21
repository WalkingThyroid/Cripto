#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc , char* argv[])
{

	/* ADVICE: USE SAME PASSWORD ALWAYS TO BE EASIER */

	const char *cmd;
	int gen_ca;
	string text;


	if( argc != 3)
  	{
    	fprintf(stderr, "Usage: [ADMIN] [1/0 - Generate CA Certficate] [USER_ID]\n");
    	exit(1);
  	}

  	/*Converting argument to string object*/
  	string user_id(argv[2]);

  	gen_ca = atoi(argv[1]);

	/*Allow everything to everyone cuz its easier and i have a headache*/
	system("sudo chmod -R a=rwx ~/Desktop/Tally_Vote");
	system("cd /Desktop/Tally_Vote");


	if (gen_ca == 1)
	{
		/*Generating CA Certificate*/
		system("sudo openssl genrsa -des3 -out vote-ca.key 2048");
		system("sudo openssl req -new -x509 -days 3650 -key vote-ca.key -out vote-ca.crt");

		/*Converting to .PEM format*/
		system("sudo openssl x509 -in vote-ca.crt -out vote-ca.pem -outform PEM");
	}

	/*Generating a RSA key pair for the client*/
	text = "sudo openssl genrsa -des3 -out " + user_id + ".key 2048";
	cmd = text.c_str();
	system(cmd);

	/*Exporting private and public keys*/
	
	// text = "sudo openssl rsa in " + user_id + ".pem -outform PEM -pubout -out public_" + user_id + ".pem";
	// cmd = text.c_str();
	// system(cmd);


	/*Exporting private key*/

	text = "sudo openssl rsa -in " + user_id + ".key -outform PEM -out private_" + user_id + ".pem";
	cmd = text.c_str();
	system(cmd);

	/*Generating certificate*/
	text = "sudo openssl req -new -key " + user_id + ".key -out " + user_id + ".csr";
	cmd = text.c_str();
	system(cmd);
	
	/*Signing the certificate*/
	text = "sudo openssl x509 -req -in " + user_id + ".csr -out " + user_id + ".crt -sha1 -CA vote-ca.crt -CAkey vote-ca.key -CAcreateserial -days 3650"; 
	cmd = text.c_str();
	system(cmd);

	/*Doing stuff*/
	text = "sudo openssl pkcs12 -export -in " + user_id + ".crt -inkey " + user_id + ".key -name \"" + user_id + "\" -out " + user_id + ".p12";
	cmd = text.c_str();
	system(cmd);

	/*Doing stuff nr2*/
	text = "sudo openssl pkcs12 -in " + user_id + ".p12 -clcerts -nokeys";
	cmd = text.c_str();
	system(cmd);

	/*Making file readable for everyone*/
	text = "sudo chmod 444 " + user_id + ".p12";
	cmd = text.c_str();
	system(cmd);


  	exit(0);
}