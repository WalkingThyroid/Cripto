/******************************************************************************
 *
 * File Name: vote.c
 *        
 * Authors:   CSC 23
 *
 *
 * COMMENTS
 *    Main program
 *
 *****************************************************************************/

#include <cstring>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define NR_CANDIDATES 10
#define MAX_NAME_LENGTH 100     /*WARNING: when changing this change scanf function!*/


char* encrypt_vote(int i, int vote,char* election_key);
char* sign_vote(char* user_key,const char* filenameTemp);
int check_cert(char* user_id, char* ca_certificate);
string system_listen(string cmd);

int main(int argc, char *argv[])
 
{

 int i, vote, new_ele;
 const char *filenameOut = "ballot_box.vt", *filenameTemp= "vote.temp", *cmd;
 char *ca_certificate, *user_certficate, *user_key, *cifer, *election_key, *signed_vote;
 char user_id[MAX_NAME_LENGTH];
 FILE *fidOut, *fidTemp;
 string text;

 // IMPORTANTE!! FALTA IMPLEMENTAR AS TIMESTAMPS!! 

 char raw_vote[500000];


  /* check if the program was correctly executes */

  if( argc != 5)
  {
    fprintf(stderr, "Usage: [VOTE] [CA_CERTIFICATE - PEM FILE] [ELECTION KEY] [USER_KEY] [IS_NEW_ELECTION]\n");
    exit(1);
  }

  ca_certificate = argv[1];
  election_key = argv[2];
  user_key = argv[3];
  new_ele = atoi(argv[4]);

	
  fprintf(stdout,"Please insert your voter ID (your ID must be coerent with your certificate ID): ");
  scanf("%100s", user_id);

  if (check_cert(user_id, ca_certificate) != 0)
  {
    fprintf(stderr, "\nInvalid user certificate, exiting...\n");
    exit(1);
  }

  fidTemp  = fopen(filenameTemp, "w");

  if (fidTemp == NULL)   
  {
      fprintf(stderr, "\nError opening temporary file - %s", filenameTemp);
      exit(1);
  }

   /* if new flag is one, then its a new election process and the ballot box will be REWRITEN, if not, the votes will
   be added to the ballot box */

  if (new_ele == 1)
  {
    fidOut = fopen(filenameOut, "w");

    if (fidOut == NULL)   
    {
      fprintf(stderr, "\nError opening output file - %s", filenameOut);
      exit(1);
    }
    
  }
    
  else                 
  {
    fidOut = fopen(filenameOut, "a");
    if (fidOut == NULL)   
    {
      fprintf(stderr, "\nError opening output file - %s", filenameOut);
      exit(1);
    }
  }
  
  sprintf(raw_vote, "%s:", user_id);
  

  for (i=0; i<NR_CANDIDATES ; i++)

  {
    fprintf(stdout, "\nInsert your vote for Candidate %d: ", i+1);
    cin  >> vote;
    cifer = encrypt_vote(i,vote, election_key);
    sprintf(raw_vote, "%s Candidate%d %s",raw_vote, i+1, cifer);
 	}

  fprintf(fidTemp, "%s", raw_vote);

  signed_vote = sign_vote(user_key, filenameTemp);

  fprintf(fidOut, "%s %s\n" ,raw_vote, signed_vote);

  /* close files */
  if (fclose (fidTemp) != 0)
  {
    fprintf(stderr, "\nError closing temporary vote file - %s", filenameTemp);
  }

  if (fclose (fidOut)!= 0)
  {
    fprintf(stderr, "\nError closing output file - %s", filenameOut);
  }

  /*consider disabling this for purposes of debugging*/

  /*cleaning up sginature file*/
  text = "sudo rm *.sha256";
  cmd = text.c_str();
  system(cmd);

  /*cleaning up temporary files*/
  text = "sudo rm *.temp";
  cmd = text.c_str();
  system(cmd);


  exit(0);
}


/******************************************************************************
 *
 * encrypt_vote
 *
 *****************************************************************************/


char* encrypt_vote(int i, int vote, char* election_key)
{
	return NULL;
}



/******************************************************************************
 *
 * sign_vote
 *
 *****************************************************************************/

char* sign_vote(char* user_key,const char *filenameTemp)
{
  const char* cmd, *sign;
  char *signature;
  int i;
  FILE* fid;
  string key(user_key);
  string file(filenameTemp);

  signature = (char*) malloc(2048);

  /*signing vote*/
  string text = "sudo openssl dgst -sha256 -sign " + key + " -out " + file + ".sha256 " + filenameTemp;
  string filename = file + ".sha256";

  sign = filename.c_str();
  cmd = text.c_str();
  system(cmd);

  /*opening signature file*/
  fid = fopen(sign,"r");
  
  i = 0;

  /*copies file to variable*/

  while(!feof(fid))       signature[i++] = fgetc(fid);


  /*closing file*/
  if (fclose(fid)!= 0)
  {
    fprintf(stderr, "\nError closing signature vote file");
  }

  /*returns signature*/
  return signature;
}



int check_cert(char* user_id, char* ca_certificate)

{

  const char* cmd;
  
  string user(user_id);
  string ca(ca_certificate);
  string out;
  string text = "sudo openssl verify -verbose -CAfile " + ca + " " + user + ".crt";
  string okay = "OK";


  cmd = text.c_str();


  out = system_listen(cmd);

  if (out.find(okay) != string::npos)
  {
    printf("The certificate validation was completed...\n");
    return 0;
  }

  else 
    return -1;

}



string system_listen(string cmd)
{
    string data;
    FILE *stream;
    const int max_buffer = 512;
    char buffer [max_buffer];

    stream = popen(cmd.c_str(), "r");

    if (stream)
    {
      while(!feof(stream))
      {
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
      }

      pclose(stream);
    }

    return data;
}