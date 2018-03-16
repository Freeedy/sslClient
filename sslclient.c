/* ------------------------------------------------------------ *
  Crated by  :  Freedy
 * gcc -o sslClient sslclient.c -lssl -lcrypto                *
 * ------------------------------------------------------------ */

#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>



#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"

#define RESET "\x1B[0m"

int create_socket(char[],char p[],   BIO *);
void DisplayPublicKeyInfo(X509* cert  ,BIO* outbio);
void GetCertSignature(X509* cert  ,BIO* outbio );

/*Show  Certificate Information*/
void ShowCerts(SSL* ssl ,BIO* outbio)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf(GRN"-------------------------Server certificate---------------------------------\n"RESET);
       

        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf(MAG"Subject: %s\n"RESET, line);
        free(line);      
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf(MAG"Issuer: %s\n"RESET, line);

        GetCertSignature(cert ,outbio);
        DisplayPublicKeyInfo(cert,outbio);
        free(line);       
        X509_free(cert);    
    }
    else
        printf(RED" No client certificates ...\n"RESET);

        printf(GRN"-------------------------End Certificate---------------------------------\n"RESET);
}

/*Show Certificate Signature*/
void GetCertSignature(X509* cert  ,BIO* outbio )
{
   printf(YEL "-------------------------Signature------------------------------\n");
  ASN1_STRING     *asn1_sig = NULL;
  X509_ALGOR      *sig_type = NULL;
   size_t          sig_bytes = 0;
  

  sig_type = cert->sig_alg;
  asn1_sig = cert->signature;
  sig_bytes = asn1_sig->length;

   BIO_printf(outbio, "Signature Algorithm:\n");
  if (i2a_ASN1_OBJECT(outbio, sig_type->algorithm) <= 0)
    BIO_printf(outbio, "Error getting the signature algorithm.\n");
  else BIO_puts(outbio, "\n\n");

  BIO_printf(outbio, "Signature Length:\n%d Bytes\n\n", sig_bytes);
   BIO_printf(outbio, "Signature Data:");
  if (X509_signature_dump(outbio, asn1_sig, 0) != 1)
    BIO_printf(outbio, "Error printing the signature \n");

   printf("-------------------------------------------------------\n"RESET);
}

/*Display  Public key Info */
void DisplayPublicKeyInfo(X509* cert  ,BIO* outbio)
{
   printf(CYN"-------------------------Public-Key------------------------------\n");
  EVP_PKEY *pkey = NULL; 


  if ((pkey = X509_get_pubkey(cert)) == NULL)
    BIO_printf(outbio, RED"Error getting public key from certificate"RESET);

 
  if (pkey) {
    switch (pkey->type) {
      case EVP_PKEY_RSA:
        BIO_printf(outbio, "%d bit RSA Key\n\n", EVP_PKEY_bits(pkey));
        break;
      case EVP_PKEY_DSA:
        BIO_printf(outbio, "%d bit DSA Key\n\n", EVP_PKEY_bits(pkey));
        break;
      default:
        BIO_printf(outbio, "%d bit non-RSA/DSA Key\n\n", EVP_PKEY_bits(pkey));
        break;
    }
  }

    if(!PEM_write_bio_PUBKEY(outbio, pkey))
    BIO_printf(outbio,RED "Error writing public key data in PEM format"RESET);

  printf("------------------------------------------------------\n"RESET);
}





int main(int count, char *strings[]) {


  if ( count < 4 )
    {
        printf(YEL"usage: %s https<hostname> <port(443 or 8443)><requestBody>\n"RESET);
        exit(0);
    }

  char *host =malloc(1024);
  host =strings[1];
  char           *dest_url = malloc(1024); 
  

  sprintf(dest_url,host);
  BIO              *certbio = NULL;
  BIO               *outbio = NULL;
  X509                *cert = NULL;
  X509_NAME       *certname = NULL;
  char *request =malloc(5120);
  char *regparam =malloc(1024); 
  char port[6]  ;
  strcpy(port,strings[2]);
  regparam=strings[3];
  const SSL_METHOD *method;
  SSL_CTX *ctx;
  SSL *ssl;
  int server = 0;
  int ret, i;

 
  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();
  SSL_load_error_strings();

  
  /* Create the I/O BIO's                             */
   
  certbio = BIO_new(BIO_s_file());
  outbio  = BIO_new_fp(stdout, BIO_NOCLOSE);

  
   /* init SSL library            */
  
  if(SSL_library_init() < 0)
    BIO_printf(outbio, "Could not initialize SSL_library_init !\n");

 
   /* Set SSLv2 client hello */
   
  method = SSLv23_client_method();

 
   /* new SSL context                            */
 
  if ( (ctx = SSL_CTX_new(method)) == NULL)
    BIO_printf(outbio, "Unable to create a new SSL context SSL_CTX_new.\n");

  
  SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);

  
   /* Create new SSL connection state                    */
  
  ssl = SSL_new(ctx);

  /*  Make  TCP  connection */
  server = create_socket(dest_url,port, outbio);
  if(server != 0)
    BIO_printf(outbio, "--Successfully made the TCP connection to: %s.\n", dest_url);

  
   /* Attach the SSL session            */
   

  SSL_set_fd(ssl, server);

  
   /* Try to SSL-connect here, returns 1 for success             */
  
  if ( SSL_connect(ssl) != 1 )
    BIO_printf(outbio, RED"!!!Error: Could not build a SSL session to: %s.\n"RESET, dest_url);
  else
    BIO_printf(outbio, "--Successfully enabled SSL/TLS session to: %s.\n", dest_url);

 
  ShowCerts(ssl,outbio);

  
 
    /*----------------------------Send-----------------------------------*/

      char buf[10240];
     
    
      printf(BLU"----------------------------------Request-----------------------------------------\n");
          char *mesg=malloc(5120);
          sprintf(mesg,"GET %s HTTP/1.1\nHost: %s\nConnection: Close\n\n",regparam,host);
          printf(BLU"Request : %s\n"RESET,mesg );
          printf("--Connected ->Encryption:  %s \n", SSL_get_cipher(ssl));
      
      int result = SSL_write(ssl, mesg, strlen(mesg));   /* encrypt & send message */
       printf("Write-Result = %i\n",result);
        printf(BLU"----------------------------end Request---------------------------------\n");
        int  bytes ;
        int s= 0 ; 
         printf(BLU"----------------------------------Response-----------------------------------------\n");
       for (;;) {
       
       
        bytes = SSL_read(ssl, buf, sizeof(buf)); /* get response & decrypt */
            if (bytes == 0) {
            break;
        }
        else if (bytes < 0) {
            
                printf(RED"Read Failed!\n"RESET);
               
                break;
            
        }
        else {
            buf[bytes] = 0;
            printf("%s\n", buf);
        }

            
            }
             printf("---------------------------------------------------------------------------------------------\n"RESET);
            



       
        buf[bytes] = 0;
        


   
  /* Free the structures*/
  SSL_free(ssl);
  close(server);
  X509_free(cert);
  SSL_CTX_free(ctx);
  BIO_printf(outbio, "Finished SSL/TLS connection with Host: %s.\n", dest_url);
  return(0);
}

/* create_socket() : the socket & TCP-connect to server */
 
int create_socket(char h[] ,char p[] , BIO *out ) {
  int sockfd;
  char hostname[256] = "";
  char    portnum[6] ;
  strcpy(portnum,p);
  char      proto[6] = "";
  char      *tmp_ptr = NULL;
  int           port;
  struct hostent *host;
  struct sockaddr_in dest_addr;

 
  strcpy(hostname,h);
  port = atoi(portnum);

  if ( (host = gethostbyname(hostname)) == NULL ) {
    BIO_printf(out, "Error: Cannot resolve hostname %s.\n",  hostname);
    abort();
  }

 
  /* create the basic TCP socket                                */
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  dest_addr.sin_family=AF_INET;
  dest_addr.sin_port=htons(port);
  dest_addr.sin_addr.s_addr = *(long*)(host->h_addr);

  /*reset the  struct*/
  memset(&(dest_addr.sin_zero), '\0', 8);

  tmp_ptr = inet_ntoa(dest_addr.sin_addr);

  /* Try to make the host connection                       */
  if ( connect(sockfd, (struct sockaddr *) &dest_addr,
                              sizeof(struct sockaddr)) == -1 ) {
    BIO_printf(out, "Error: Cannot connect to host %s [%s] on port %d.\n",
             hostname, tmp_ptr, port);
  }

  return sockfd;
}
