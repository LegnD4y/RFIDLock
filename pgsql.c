#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <string.h>

int
main()
{
  /*Objeto de conexão*/
  PGconn *conn = NULL;

  /*Ponteiro de resultado*/
  PGresult *result;

  /*Arquivo que irá conter o fluxo de saída*/
  FILE *output_stream;

  /*Estrutura de opções*/
  PQprintOpt print_options;

  // Estabelecendo conexao com o PSQL
  conn = PQconnectdb("dbname=crime user=postgres password=postgres host=localhost port=5432");

  // Check if the connection is successful
  if (PQstatus(conn) != CONNECTION_OK)
  {
    // If not successful, print the error message and finish the connection
    printf("Error while connecting to the database server: %s\n", PQerrorMessage(conn));

    // Finish the connection
    PQfinish(conn);

    // Exit the program
    exit(1);
  }

  // We have successfully established a connection to the database server
  printf("Connection Established\n");
  printf("Port: %s\n", PQport(conn));
  printf("Host: %s\n", PQhost(conn));
  printf("DBName: %s\n", PQdb(conn));

  // Exec Query
  result = PQexec(conn, "select * from crime limit 10;");

  if(!result)
  {
    printf("Erro executando comando.\n");
  }
  else
  {
    switch(PQresultStatus(result))
    {
      case PGRES_TUPLES_OK:
        printf("O comando foi bem sucedido e dados podem ter sido retornados.\n");
        break;
      case PGRES_COPY_OUT:
        printf("Uma cópia para um arquivo externo estava em andamento.\n");
        break;
      case PGRES_COPY_IN:
        printf("Uma cópia de um arquivo externo estava em andamento.\n");
        break;
      case PGRES_BAD_RESPONSE:
        printf("Erro inesperado.\n");
        break;
      case PGRES_NONFATAL_ERROR:
        printf("Erro não fatal.\n");
        break;
      case PGRES_EMPTY_QUERY:
        printf("Nada aconteceu.\n");
        break;
      case PGRES_FATAL_ERROR:
        printf("Error in query: %s\n", PQresultErrorMessage(result));
        break;
      case PGRES_COMMAND_OK:
        printf("%s linhas afetadas.\n", PQcmdTuples(result));
        break;
      default:
        printf("Algum outro resultado ocorreu.\n");
        break;
    }

    /*Define o nosso arquivo de saída*/
    output_stream = fopen("/home/gustavo/Programs/RFIDLock/sql.out", "w");

    if(output_stream == NULL)
    {
      printf("Erro abrindo o arquivo.\n");
    }
    else
    {
      memset(&print_options, '\0', sizeof(print_options));

      print_options.header = 1;
      print_options.align = 1;
      print_options.html3 = 0;
      print_options.fieldSep = "|";
      print_options.fieldName = NULL;

      PQprint(output_stream, result, &print_options);
    }

    /*Libera o nosso objeto*/
    PQclear(result);
  }

  if(conn != NULL)
  {
    PQfinish(conn);
  }

  return 0;
}
