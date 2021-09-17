#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int main(int argc, char **argv)
{
  short int i, c, d, dpos, mpos, qzeros;
  short int pretnd = FALSE;
  long int casdes = 2;
  short int rtn = 0;
  short int quiet = FALSE;
  char *p_casdes;
  char regex[] = "-[0-9]?[0-9]?[0-9]\.[[:alpha:]]{3}";
  char *p_regex = regex;
  char nvnome[30];
  char msgbuf[100];
  regex_t rgx;

//----/ Tratamento de parâmetros /----
  opterr = 0;
  while ((c = getopt (argc, argv, "qVhpr:z:")) != -1)
    switch (c)
    {
      case 'p':
        pretnd = TRUE;
        break;
      case 'z':
        casdes = strtol(optarg,&p_casdes,0);
        break ;
      case 'r':
        strcpy(p_regex,optarg);
        break ;
      case 'q':
        ++quiet;
        break ;
      case '?':
        fprintf(stderr, "Opção desconhecida '-%c'.\n", optopt);
        rtn = 1;
      case 'h':
        printf("Uso: %s [opção]... <arquivo>...\n",argv[0]);
        printf("\n");
        printf("  -p, --pretend               exibe o que fará sem renomar\n");
        printf("  -r, --regex 'REGEX'         Altera o REGEX padrão.\n");
        printf("  -z, --casas-decimais n      'n' casas decimais. Padrão: 1\n");
        printf("  -V, --version               mostra a versão e sai\n");
        printf("  -h, --help                  mostra esta ajuda e sai\n");
        printf("\n");
        printf("REGEX:\n");
        printf("%s -r '.*[1-9][0-9]\\.[[:alpha:]].*'\n",argv[0]);
        exit(rtn);
      case 'V':
        printf("%s 0.01\n",argv[0]);
        exit(0);
      default:
        abort ();
    }

  if (argc < 2)
  {
    printf("Argumentos errados. Uso correto é: %s <arq-1.ext> [arq-2.ext] ...\n",argv[0]);
    printf("Use '%s --help' ou 'man %s' para maiores detalhes.\n",argv[0],argv[0]);
    return(1);
  }
  //

  for (i=optind;i<argc;i++)
  {
    //Se não existe arquivo, pula para o próximo
    if (access( argv[i], W_OK ) != 0)
    {
      printf("Arquivo '%s' não existe, cabeção!\n",argv[i]);
      continue;
    }
    
    //Regex valida se o arquivo precisa ser renomeado ou não
    c = regcomp(&rgx, regex, REG_EXTENDED);
    if (c) 
    {
      fprintf(stderr,"Erro no regex\n");
      exit(1);
    }

    c = regexec(&rgx, argv[i], 0, NULL, 0);
    if (!c)
    {
      //Acha os ultimos '-' e '.'
      for (int a=0;a<strlen(argv[i]);a++)
      {
        if (argv[i][a] == '-')
          mpos = a+1;
        if (argv[i][a] == '.')
          dpos = a;
      }

      //Calcula a qtd de zeros que deve colocar à direita
      qzeros = casdes - (dpos - mpos) ;
      //Adiciona os zeros à direita respeitando o num. de casas decimais
      c = d = 0;
      while (argv[i][c] != '\0')
      {
        if (c != mpos)
        {
          nvnome[d] = argv[i][c];
        } else {
          for (int j=0;j<qzeros;j++)
          {
            nvnome[d] = '0';
            d++;
          }
          nvnome[d] = argv[i][c];
        }
        c++;
        d++;
      }
      nvnome[d] ='\0';
      //Parâmetro '-p | --pretend'
      if (pretnd)
      {
        if (quiet == 0) 
          printf("%s --> %s\n", argv[i], nvnome);
      } else {
        rename(argv[i],nvnome);
      }
    } else if (c == REG_NOMATCH) {
      if (quiet <= 1) printf("Ignorado: %s\n",argv[i]);
    } else {
      regerror(c, &rgx, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Erro no regex(else): %s\n", msgbuf);
      exit(1);
    }
    regfree(&rgx);
  }

  return(0);
}
