
////////////////////////////////////////////////////////
//                                                    //
//  Universidade Federal do Agrestre de Pernambuco    // 
//      Bacharelado em Ciencia da Computacao          //
//                                                    //
//  Projeto de Introducao a Programacao               //
//                                                    //
//  Estudantes:                                       //
//  Robert Freire de Melo                             //                 
//  William Batista Couto dos Santos                  //
//                                                    //
////////////////////////////////////////////////////////

// O projeto a ser desenvolvido neste codigo e uma locadora de veiculos!
// Onde é possivel cadastrar/editar/remover/atulizar/ler dados de cliente, veiculos, e ordens de aluguel


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////STUCTS /////////////////////
struct Veiculo{
    char modelo[50];
    char placa[15];
    int ano_de_fabricacao;
    char chassi[17];
    int codigocarro;
    float valor;
    int dispo;

};
struct Cliente{

char nome_completo[101];
char cpf[15];
char telefone[15];
int codigocliente[50];
};

struct alugar{
    float valor_diaria;
    float valor_Total_aluguel;
    int tempo_aluguel;
    struct Cliente pessoa;
    struct Veiculo carro;
    int codigo_aluguel;
    int ativo;
};

struct repositorio{
struct alugar Ordem_Aluguel[50];
struct Veiculo carro[100];
struct Cliente pessoa[100];
int prox_carro;
int prox_cliente;
int prox_aluguel;


};

struct repositorio RW_Veiculos;

//funcao para verificar cpf
int VerificarCPF (char *cpf)
{
    int i, verificacao =-1; //caso nao encontre o cpf retorna -1
    for(i=0; i < RW_Veiculos.prox_cliente; i++)
        {
            if (strcmp (cpf,RW_Veiculos.pessoa[i].cpf)==0)
            {
                verificacao = i; //caso encontre o cpf retorna a posicao
            }
        }
        return verificacao;
}

//funcao para verificar codigo do cliente 
int VerificarCodigoCliente (int codigo)
{
    printf("COD %d\n", codigo);
    int i, verificacao = -1;          //caso nao encontre a posicao do cliente retorna -1

    for(i=0; i < RW_Veiculos.prox_cliente; i++)
    {
            if (codigo == RW_Veiculos.pessoa[i].codigocliente[i])
            {
                verificacao = i;    //caso encontre o codigo do cliente retorna a posicao do cliente
            }
    }
    return verificacao;

}

//tela padrao para  erros de cliente
void TelaClienteNaoEncontrado (){

        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |             RW Veiculos              |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" |        Cliente nao encontrado.       |\n");
        printf(" |______________________________________|\n\n\n\n");

}


//fucao que lista todos os clientes
void ListarClientes(){
    int i;
    for (i=0; i<RW_Veiculos.prox_cliente;i++)
    {
        printf(" | Codigo do cliente: #%d | CPF: %s | NOME: %s \n", RW_Veiculos.pessoa[i].codigocliente[i] ,RW_Veiculos.pessoa[i].cpf, RW_Veiculos.pessoa[i].nome_completo);
    }
}

//funcao para listar todos os veiculos (incluso alugados)
void ListaVeiculos (){
    int i;
    for (i=0; i<RW_Veiculos.prox_carro;i++)
        {
            printf("Codigo do Veiculo: #%d | PLACA: %s | MODELO: %s \n", RW_Veiculos.carro[i].codigocarro ,RW_Veiculos.carro[i].placa, RW_Veiculos.carro[i].modelo);
        }
}

//fucao que lista os veiculos que ainda estao disponiveis para alugar
void ListaVeiculosDisponiveis(){
    int k;

        for (k=0; k<RW_Veiculos.prox_carro;k++)
        {
            if(RW_Veiculos.carro[k].dispo==0) //apenas veiculos disponiveis seram listados - dispo 0 = disponivel
             {
                printf(" | VALOR DIARIO: %.2f   PLACA: %s   MODELO: %s\n", ((RW_Veiculos.carro[k].valor)*0.005) ,RW_Veiculos.carro[k].placa, RW_Veiculos.carro[k].modelo);
            }
        }
}

//funcao para registrar um cliente
void RegistrarCliente (char *nome, char *cpf, char *telefone){

    strcpy(RW_Veiculos.pessoa[RW_Veiculos.prox_cliente].nome_completo,nome);
    strcpy(RW_Veiculos.pessoa[RW_Veiculos.prox_cliente].cpf, cpf);
    strcpy(RW_Veiculos.pessoa[RW_Veiculos.prox_cliente].telefone,telefone);
    RW_Veiculos.prox_cliente++;
    RW_Veiculos.pessoa[RW_Veiculos.prox_cliente].codigocliente[RW_Veiculos.prox_cliente]= RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].codigocliente[RW_Veiculos.prox_cliente-1] + 1;

}

//funcao para registrar um veiculo
void RegistrarVeiculo (char *modelo, char *placa, int ano, char *chassi, float valor)
{
    
    strcpy(RW_Veiculos.carro[RW_Veiculos.prox_carro].modelo, modelo);
    strcpy(RW_Veiculos.carro[RW_Veiculos.prox_carro].placa, placa);
    RW_Veiculos.carro[RW_Veiculos.prox_carro].ano_de_fabricacao = ano;
    strcpy(RW_Veiculos.carro[RW_Veiculos.prox_carro].chassi, chassi);
    RW_Veiculos.carro[RW_Veiculos.prox_carro].valor = valor;
    RW_Veiculos.carro[RW_Veiculos.prox_carro].dispo=0;

    if(RW_Veiculos.prox_carro != 0)
    {
        RW_Veiculos.carro[RW_Veiculos.prox_carro].codigocarro= RW_Veiculos.carro[RW_Veiculos.prox_carro-1].codigocarro + 1;
    }
    RW_Veiculos.prox_carro++;


}

//funcao para cadastrar um veiculo
void CadastrarVeiculo ()
{

    int controle_placa, i,opccontrole_placa;
    float valor;

    do{
        controle_placa=0; // variavel de controle, é alterada para alternar entre tela, e tela de erro
        opccontrole_placa=1;
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n\n");
        printf("------- Cadastrar Veiculo-------\n\n");
        printf("Informe a placa do veiculo: \n");
        scanf("%s", RW_Veiculos.carro[RW_Veiculos.prox_carro].placa);

        for (i=0;i<RW_Veiculos.prox_carro; i++)
        {
            if(strcmp(RW_Veiculos.carro[RW_Veiculos.prox_carro].placa ,RW_Veiculos.carro[i].placa)== 0)
            {
                /////////////// TELA VEICULO CADASTRADO ////////////////
                system("cls");
                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |              RW Veiculos             |\n");
                printf(" |______________________________________|\n");
                printf(" |                                      |\n");
                printf(" | Este veiculo ja esta cadastrado!     |\n");
                printf(" |                                      |\n");
                printf(" | 1 ......... Cadastrar outro veiculo  |\n");
                printf(" | 2 ......... Menu inicial\n           |\n");
                printf(" |______________________________________|\n");
                scanf("%d", &opccontrole_placa);
                system("cls");
                

                    if(opccontrole_placa == 1) // opcao para cadastrar novo veiculo
                    {
                        controle_placa=1;
                    }
                    else if(opccontrole_placa == 2) //opcao para voltar para menu inicial
                    {
                    controle_placa == 0;
                    }
            }
        }

        if(opccontrole_placa ==1)
        {
            /////////////// CADASTRAR VEICULO////////////////
            printf("\nInforme o modelo do veiculo:\n");
            getchar();
            scanf("%[^\n]", RW_Veiculos.carro[RW_Veiculos.prox_carro].modelo);

            printf("\nInforme o ano de fabricacao do veiculo: \n");
            scanf("%d", &RW_Veiculos.carro[RW_Veiculos.prox_carro].ano_de_fabricacao);

            printf("\nInforme o numero do Chassi do veiculo: \n");
            getchar();
            scanf("%s", RW_Veiculos.carro[RW_Veiculos.prox_carro].chassi);
            printf("\nInforme O valor do veiculo: \n");
            scanf("%f", &RW_Veiculos.carro[RW_Veiculos.prox_carro].valor );
            RW_Veiculos.carro[RW_Veiculos.prox_carro].dispo=0;
            system("cls");
            

            ///////////////TELA APOS CADASTRAR VEICULO////////////////
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |              RW Veiculos             |\n");
            printf(" |______________________________________|\n");
            printf(" |                                      \n");
            printf(" |         Veiculo Cadastrado           \n");
            printf(" |                                      \n");
            printf(" |Placa: %s\n", RW_Veiculos.carro[RW_Veiculos.prox_carro].placa);
            printf(" |Modelo: %s\n", RW_Veiculos.carro[RW_Veiculos.prox_carro].modelo);
            printf(" |Ano de Fabricacao: %d\n", RW_Veiculos.carro[RW_Veiculos.prox_carro].ano_de_fabricacao);
            printf(" |Chassi: %s\n", RW_Veiculos.carro[RW_Veiculos.prox_carro].chassi);
            printf(" |Valor: RS %.2f \n", RW_Veiculos.carro[RW_Veiculos.prox_carro].valor);
            printf(" |______________________________________|\n\n\n\n");
            system("pause");
            

            if(RW_Veiculos.prox_carro != 0)
            {
                    RW_Veiculos.carro[RW_Veiculos.prox_carro].codigocarro = RW_Veiculos.carro[RW_Veiculos.prox_carro-1].codigocarro + 1;
            }
            RW_Veiculos.prox_carro++;

        }
    }while(controle_placa != 0);
}


//funcao para visualizar  veiculos
void VisualizarVeiculo(){

    int opcaoveiculo, i,j,opc3,tela;
    char placa[20];

    do {
        tela=0;
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |1 ...... Visualizar todos os veiculos |\n");
        printf(" |2 ...... Buscar veiculo               |\n");
        printf(" |3 ...... Remover veiculo              |\n");
        printf(" |______________________________________|\n");
        scanf("%d", &opcaoveiculo);

        if(opcaoveiculo ==1 )
        {
            system("cls");
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |              RW Veiculos             |\n");
            printf(" |______________________________________|\n");
            printf(" |\n");
            printf(" |---- LISTA DE VEICULOS CADASTRADOS: ----\n");
            printf(" |\n");
                for (i=0; i < RW_Veiculos.prox_carro; i++) //lista todos os veiculos cadastrados
                {

                        printf(" | Placa: %s\n", RW_Veiculos.carro[i].placa);
                        printf(" | Modelo: %s\n", RW_Veiculos.carro[i].modelo);
                        printf(" | Ano de Fabricacao: %d\n", RW_Veiculos.carro[i].ano_de_fabricacao);
                        printf(" | Chassi: %s\n", RW_Veiculos.carro[i].chassi);
                        printf(" | Codigo do Veiculo: %d\n", RW_Veiculos.carro[i].codigocarro);
                        printf(" | Valor: RS %.2f\n", RW_Veiculos.carro[i].valor);
                        printf(" |_______________________________________\n");
                        printf(" |\n");
                }
        }
        else if (opcaoveiculo == 2)
        {
            system("cls");
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |              RW Veiculos             |\n");
            printf(" |______________________________________|\n\n");
            printf(" Qual veiculo deseja visualizar? \n\n");

            for (i=0; i<RW_Veiculos.prox_carro;i++) //lista a placa e modelo dos veiculos para auxiliar a busca
            {
                printf(" | PLACA: %s | MODELO: %s\n", RW_Veiculos.carro[i].placa, RW_Veiculos.carro[i].modelo);
            }
            printf("\n Informe a placa do Veiculo.\n");
            scanf("%s", &placa);

                for (j=0; j<RW_Veiculos.prox_carro; j++)
                {
                    if(strcmp(placa, RW_Veiculos.carro[j].placa)==0)
                    {
                        tela=1; //faz nao executar a tela "veiculo nao foi encontrado"
                        system("cls");
                        printf("  ______________________________________\n");
                        printf(" |                                      |\n");
                        printf(" |              RW Veiculos             |\n");
                        printf(" |______________________________________|\n\n");
                        printf("\n Veiculo Encontrado!\n\n\n");
                        printf("  _____________________________________________\n");
                        printf(" |\n");
                        printf(" |Placa:............... %s\n", RW_Veiculos.carro[j].placa);
                        printf(" |Modelo:.............. %s\n", RW_Veiculos.carro[j].modelo);
                        printf(" |Ano :................ %d\n", RW_Veiculos.carro[j].ano_de_fabricacao);
                        printf(" |Chassi:.............. %s\n", RW_Veiculos.carro[j].chassi);
                        printf(" |Codigo do Veiculo:... %d\n", RW_Veiculos.carro[j].codigocarro);
                        printf(" |Valor:............... RS %.2f\n", RW_Veiculos.carro[i].valor);
                        printf(" |_____________________________________________\n\n");
                    }
                }

            if (tela == 0){  //caso o veiculo nao seja encontrado exibira esta tela
                system("cls");
                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |              RW Veiculos             |\n");
                printf(" |______________________________________|\n\n");
                printf("\nVeiculo nao encontrado!\n");
                printf("Confira os dados informados e tente novamente.\n");
            }
        }

    if(opcaoveiculo == 3) //remover um veiculo
    {
        RemoverVeiculo(); //chama a funcao que remove o veiculo
    }

    printf("\n\n\n  _________________________________\n");
    printf(" |4 - Buscar outro veiculo.        |\n");
    printf(" |5 - Editar Veiculo               |\n");
    printf(" |6 - Remover Veiculo              |\n");
    printf(" |7 - Voltar para o Menu inicial.  |\n");
    printf(" |_________________________________|\n");
    scanf("%d", &opcaoveiculo);

    if(opcaoveiculo == 3){
        RemoverVeiculo();
    }
    if(opcaoveiculo == 5){
        EditarVeiculo();
    }
    if (opcaoveiculo == 6){
        RemoverVeiculo();
    }

    }while(opcaoveiculo != 7);

}


// funcao para atualizar dados de um veiculo
void EditarVeiculo(){

    float novo_valor;
    int i,j, codigo, tela =0, novo_ano;
    char nova_placa[20],novo_modelo[50], novo_chassi[50];
    system("cls");

    printf(" ______________________________________\n");
    printf("|                                      |\n");
    printf("|              RW Veiculos             |\n");
    printf("|______________________________________|\n");
    printf("\n---- LISTA DE VEICULOS CADASTRADOS: ----\n\n");

    for (i=0; i<RW_Veiculos.prox_carro;i++)
    {
        printf("CODIGO: %d   PLACA: %s   MODELO: %s\n", RW_Veiculos.carro[i].codigocarro,RW_Veiculos.carro[i].placa, RW_Veiculos.carro[i].modelo);
    }
    printf("_________________________________________\n");
    printf("Informe o codigo do veiculo que deseja editar\n");
    scanf("%d", &codigo);

    for(j=0; j< RW_Veiculos.prox_carro;j++)
    {

        if(codigo == RW_Veiculos.carro[j].codigocarro){
            tela =1;
            printf(" ______________________________________\n");
            printf("|                                      |\n");
            printf("|    Editando Veiculo COD: #%d       |\n", codigo);
            printf("|______________________________________|\n\n");
            printf("Informe a nova Placa:\n");
            getchar();
            scanf("%[^\n]", nova_placa);
            printf("\nInforme o novo Modelo:\n");
            getchar();
            scanf("%[^\n]", novo_modelo);
            printf("\nInforme o novo chassi:\n");
            getchar();
            scanf("%[^\n]", novo_chassi);
            printf("\nInforme o novo ano de Fabricacao:\n");
            scanf("%d", & novo_ano);
            printf("\nInforme o novo Valor:\n");
            scanf("%f", &novo_valor);

                strcpy(RW_Veiculos.carro[j].placa, nova_placa);
                strcpy(RW_Veiculos.carro[j].modelo, novo_modelo);
                strcpy(RW_Veiculos.carro[j].chassi, novo_chassi);
                RW_Veiculos.carro[j].ano_de_fabricacao = novo_ano;
                RW_Veiculos.carro[j].valor = novo_valor;

        }
    }
    if(tela== 0){
        system("cls");
        printf("\n  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n\n");
        printf("\nVeiculo nao encontrado!\n");
        printf("Confira os dados informados e tente novamente.\n\n\n\n\n\n-");
        system("pause");

    }
}



void RemoverVeiculo(){
    system("cls");
    int k,j,i;
    int removerVeiculo;
    int telaCarro= 0;

    printf("  ______________________________________\n");
    printf(" |                                      |\n");
    printf(" |              RW Veiculos             |\n");
    printf(" |______________________________________|\n\n");
    printf("\n---- LISTA DE VEICULOS CADASTRADOS: ----\n\n");

        for (i=0; i<RW_Veiculos.prox_carro;i++) //lista apenas codigo, placa e modelo dos veiculos castrados (disponiveis ou nao para aluguel)
        {
            printf("CODIGO: %d   PLACA: %s   MODELO: %s\n", RW_Veiculos.carro[i].codigocarro,RW_Veiculos.carro[i].placa, RW_Veiculos.carro[i].modelo);
        }

    printf("__________________________________________\n\n");
    printf("Informe o codigo do veiculo que deseja remover:\n");
    getchar();
    scanf("%d", &removerVeiculo);

    for (k=0; k < RW_Veiculos.prox_carro; k++) //inicio do processo de remocao de veiculo
    {
        if (removerVeiculo == RW_Veiculos.carro[k].codigocarro)
        {
            telaCarro=1; // faz com que a  tela de erro de "Veiculo nao encontrado" nao seja exibida
            for(j=k; j <= RW_Veiculos.prox_carro; j++)
            {

                strcpy(RW_Veiculos.carro[j].placa, RW_Veiculos.carro[j+1].placa);
                strcpy(RW_Veiculos.carro[j].modelo, RW_Veiculos.carro[j+1].modelo);
                strcpy(RW_Veiculos.carro[j].chassi, RW_Veiculos.carro[j+1].chassi);
                RW_Veiculos.carro[j].ano_de_fabricacao = RW_Veiculos.carro[j+1].ano_de_fabricacao;
                RW_Veiculos.carro[j].valor = RW_Veiculos.carro[j+1].valor;

            }

            system("cls");
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |              RW Veiculos             |\n");
            printf(" |______________________________________|\n");
            printf(" |                                      |\n");
            printf(" |    Veiculo removido com sucesso!     |\n");
            printf(" |                                      |\n");
            printf(" |______________________________________|\n");
            system("pause");
            RW_Veiculos.prox_carro--;
        }
    }

    if(telaCarro == 0)
    {
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" |   Codigo do Veiculo nao encontrado.  |\n");
        printf(" |                                      |\n");
        printf(" |______________________________________|\n");
        system("pause");
    }

}

////////FIM DAS FUNCOES PARA VEICULOS//////////



/////////////INICIO DAS FUNCOES PARA CLIENTE///////////

//funcao para cadastrar um cliente
void CadastrarCliente(){
    char cpf[20], nome [100], telefone[20];
    int k;

    system("cls");
    printf("  ______________________________________\n");
    printf(" |                                      |\n");
    printf(" |          Cadastrar Cliente           |\n");
    printf(" |______________________________________|\n\n");

    printf("\nInforme o CPF do cliente:\n");
    scanf("%s", cpf);

    k = VerificarCPF(cpf); //verifica o cpf, caso encontre retorna a posicao do mesmo

    if (k < 0) // quando o cpf nao e encontrado significa que ainda n esta cadastrado e a vaiavel
    {         // k recebe -1
        printf("\nInforme o nome completo do cliente:\n");
        getchar();
        scanf(" %[^\n]", nome);

        printf("\nInforme o telefone do cliente:\n");
        getchar();
        scanf("%[^\n]", telefone);
        system ("cls");

        RegistrarCliente(nome,cpf,telefone); //envia os dados recebidos para o resistro ser efetuado.

        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |          Cliente Cadastrado          |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" | Nome Completo: %s\n", RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].nome_completo);
        printf(" | CPF: %s\n", RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].cpf);
        printf(" | Telefone: %s\n", RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].telefone);
        printf(" | Codigo do cliente: # %d\n", RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].codigocliente[RW_Veiculos.prox_cliente-1]);
        printf(" |______________________________________\n\n\n");
        RW_Veiculos.pessoa[RW_Veiculos.prox_cliente].codigocliente[RW_Veiculos.prox_cliente]= RW_Veiculos.pessoa[RW_Veiculos.prox_cliente-1].codigocliente[RW_Veiculos.prox_cliente-1] + 1;

    }
    else if (k > -1 ){ //k representa a posicao do CPF, quando o mesmo n e encontardo o valor -1 é enviado
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |        Cliente Ja Cadastrado!        |\n");
        printf(" |______________________________________|\n\n\n\n");
    }

    system ("pause");
    system ("cls");
}



void ConsultarCliente (){

    int opcaoCliente;
    int i, j, k;
    char buscarCpf[15];


    do{
        opcaoCliente =0;
        k = -2;
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" | 1 - Visualizar todos os clientes.    |\n");
        printf(" | 2 - Buscar cliente.                  |\n");
        printf(" | 3 - Voltar                           |\n");
        printf(" |______________________________________|\n");

        scanf("%d", &opcaoCliente);

        if (opcaoCliente == 3)
        {
            opcaoCliente = 6;
        }

        system("cls");

        if (opcaoCliente == 1)
        {
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |          Todos os clientes           |\n");
            printf(" |______________________________________|\n\n\n");
            printf(" |____________________________________________________\n");

            for(i = 0; i < RW_Veiculos.prox_cliente; i++)
            {
                printf(" |Nome Completo: %s\n", RW_Veiculos.pessoa[i].nome_completo);
                printf(" |CPF: %s\n", RW_Veiculos.pessoa[i].cpf);
                printf(" |Telefone: %s\n", RW_Veiculos.pessoa[i].telefone);
                printf(" |Codigo do cliente: # %d\n", RW_Veiculos.pessoa[i].codigocliente[i]);
                printf(" |____________________________________________________\n");
                printf(" |\n");
            }

            system("pause");
        }
        if (opcaoCliente == 2)
        {
            system("cls");
            printf("  ______________________________________\n");
            printf(" |                                      |\n");
            printf(" |              RW_Veiculos             |\n");
            printf(" |______________________________________|\n");
            printf(" | Informe o CPF do cliente:            |\n");
            printf(" |");
            getchar();
            scanf("%[^\n]", buscarCpf);
            system("cls");

            k = VerificarCPF(buscarCpf); // quando um CPF n e encontrado k recebe a posicao do CPF, quando n é encontrado K recebe -1 

            if(k>-1)
            {
                j=k; //j recebe o valor de k, que representa a posicao em que o CPF esta salvo no repositorio
                    printf("  ______________________________________\n");
                    printf(" |                                      |\n");
                    printf(" |        Informacoes do Cliente        |\n");
                    printf(" |______________________________________|\n");
                    printf(" |Nome Completo: %s\n", RW_Veiculos.pessoa[j].nome_completo);
                    printf(" |CPF: %s\n", RW_Veiculos.pessoa[j].cpf);
                    printf(" |Telefone: %s\n", RW_Veiculos.pessoa[j].telefone);
                    printf(" |Codigo do cliente: # %d\n", RW_Veiculos.pessoa[j].codigocliente[j]);
                    printf(" |_______________________________________\n");
                }
            }

            if (k == -1) // quando um CPF n e encontrado k recebe o valor -1
            {
                TelaClienteNaoEncontrado(); //chama a tela de erro de cliente
            }

        if (opcaoCliente != 6 )
        {
            printf("\n\n\n  ________________________________\n");
            printf(" |3 - Visualizar novo cliente.    |\n");
            printf(" |4 - Editar Cliente              |\n");
            printf(" |5 - Remover Cliente             |\n");
            printf(" |6 - Voltar para o menu anterior.|\n");
            printf(" |________________________________|\n");
            scanf("%d", &opcaoCliente);
        }

        if(opcaoCliente == 4 )
        {
            EditarCliente();
        }
        if(opcaoCliente == 5)
        {
            RemoverCliente();
        }

        system("cls");
    }while(opcaoCliente != 6);
        system("cls");

}

//funcao para remover um cliente
void RemoverCliente(){
    system("cls");
    int k,j, removerCliente;

    printf("  ______________________________________\n");
    printf(" |                                      |\n");
    printf(" |              RW_Veiculos             |\n");
    printf(" |______________________________________|\n");
    printf(" | -- LISTA DE CLIENTES CADASTRADOS: -- |\n");
    printf(" |\n");

    ListarClientes();

    printf("\nInforme o codigo do cliente que deseja remover:\n");
    scanf("%d", &removerCliente);

    k = VerificarCodigoCliente(removerCliente); //k recebe a posicao do cliente, caso n encontre retorna -1

        if(k>-1) //k recebe a posicao do cliente, caso n encontre retorna -1
        {
            for(j=k; j <= RW_Veiculos.prox_cliente; j++)
                {
                    strcpy(RW_Veiculos.pessoa[j].nome_completo, RW_Veiculos.pessoa[j+1].nome_completo);
                    strcpy(RW_Veiculos.pessoa[j].cpf, RW_Veiculos.pessoa[j+1].cpf);
                    strcpy(RW_Veiculos.pessoa[j].telefone, RW_Veiculos.pessoa[j+1].telefone);
                }

                system("cls");
                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |             RW Veiculos              |\n");
                printf(" |______________________________________|\n");
                printf(" |                                      |\n");
                printf(" |     Cliente removido com sucesso!    |\n");
                printf(" |______________________________________|\n");
                system("pause");
                RW_Veiculos.prox_cliente--;
        }

        if(k < 0) //k recebe a posicao do cliente, caso n encontre retorna -1
        {
            TelaClienteNaoEncontrado(); 
            system("pause");
        }

}

//funcao para editar um cliente
void EditarCliente(){

    system("cls");

    char novo_nome[101];
    char novo_cpf[15];
    char novo_telefone[15];
    int codigo,i,k;

        printf(" ______________________________________\n");
        printf("|                                      |\n");
        printf("|              RW Veiculos             |\n");
        printf("|______________________________________|\n");
        printf("\n---- LISTA DE CLIENTES CADASTRADOS: ----\n\n");

        ListarClientes();
        printf("\n_________________________________________\n");
        printf("Informe o codigo do cliente que deseja editar: \n");
        scanf("%d", &codigo);

        k = VerificarCodigoCliente(codigo); //k recebe a posicao do cliente, caso n encontre retorna -1

        if(k>-1)
        {

                system("cls");
                printf(" ______________________________________\n");
                printf("|                                      |\n");
                printf("|      Editando CLIENTE COD: #%d     |\n", codigo);
                printf("|______________________________________|\n\n");

                printf("Informe o novo nome: \n");
                getchar();
                scanf("%[^\n]", novo_nome);
                printf("Informe o novo CPF: \n");
                getchar();
                scanf("%[^\n]", novo_cpf);
                printf("Informe o novo telefone: \n");
                getchar();
                scanf("%[^\n]", novo_telefone);

                strcpy(RW_Veiculos.pessoa[k].nome_completo, novo_nome);
                strcpy(RW_Veiculos.pessoa[k].cpf, novo_cpf);
                strcpy(RW_Veiculos.pessoa[k].telefone, novo_telefone);
                system("cls");

                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |           Cliente Editado!           |\n");
                printf(" |______________________________________|\n");
                printf(" |                                      |\n");
                printf(" | Nome Completo: %s\n", RW_Veiculos.pessoa[k].nome_completo);
                printf(" | CPF: %s\n", RW_Veiculos.pessoa[k].cpf);
                printf(" | Telefone: %s\n", RW_Veiculos.pessoa[k].telefone);
                printf(" | Codigo do cliente: # %d\n", RW_Veiculos.pessoa[k].codigocliente[k]);
                printf(" |______________________________________\n");
                system("pause");

        }
        if(k < 0) //k recebe a posicao do cliente, caso n encontre retorna -1
        {
            TelaClienteNaoEncontrado();
            system("pause");
        }

}


/////////////FIM DAS FUNCOES PARA CLIENTE////////////////

////////FUNCOES PARA ALUGUEL ///////////

//funcao que resgitra um aluguel

void RegistrarAluguel(int cliente, int veiculo,int dias, float valor_aluguel ){

    //as variaveis cliente e veiculo recebem a posicao dos mesmo no repositorio

    if(RW_Veiculos.prox_aluguel != 0){
      RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].codigo_aluguel = RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel-1].codigo_aluguel+1;
    }

    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].pessoa = RW_Veiculos.pessoa[cliente];
    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].carro = RW_Veiculos.carro[veiculo];
    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].tempo_aluguel = dias;
    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].valor_Total_aluguel = valor_aluguel;
    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].valor_diaria = RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].carro.valor*0.005;
    RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel].ativo =0;
    RW_Veiculos.carro[veiculo].dispo = 1; //faz com que o carro fique indisponivel pois, ja esta alugado
    RW_Veiculos.prox_aluguel++;


}

//funcao para imprimir os dados do aluguel
void VisualizarAluguel(char *nome, char *cpf, char *telefone, int codcarro, char *placa, char *modelo, char *chassi,int ano, float valor, float valord, int dias, float valor_aluguel ){

        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |        RW Aluguel de Veiculos        |\n");
        printf(" |______________________________________|\n");
        printf(" |\n");
        printf(" |     Dados do Cliente: \n");
        printf(" |\n");
        printf(" | CLIENTE............. %s\n", nome);
        printf(" | CPF................. %s\n", cpf );
        printf(" | TELEFONE:........... %s\n", telefone);
        printf(" |\n");
        printf(" |     DADOS DO VEICULO \n");
        printf(" |\n");
        printf(" | CODIGO DO VEICULO:.. #%d\n",codcarro);
        printf(" | PLACA............... %s\n", placa);
        printf(" | MODELO.............. %s\n", modelo);
        printf(" | CHASSI.............. %s\n", chassi);
        printf(" | ANO................. %d\n", ano);
        printf(" | VALOR DO VEICULO.... RS %.2f\n", valor);
        printf(" |\n");
        printf(" |     DADOS DO ALUGUEL    \n");
        printf(" |\n");
        printf(" | VALOR DA DIARIA........ RS %.2f\n", valord);
        printf(" | QUANT. DIAS............ #%d\n", dias);
        printf(" | VALOR TOTAL DO ALUGUEL. RS %.2f\n", valor_aluguel);

}

//funcao que gerencia os procedimentos do aluguel
void Alugar(){

    int telaERRO, opcao_tela_0,dias, i,j,k,L, Verificacao_CPF, cliente, veiculo, continuar;
    float valor_aluguel;
    char cpf[20], placa [20];

    do{
        system("cls");
        telaERRO=0; //por pre definicao as telas de erro estao ativadas = 0
        opcao_tela_0=0; //faz com que o loop continue ate que seja solicitada a saida

        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |        RW Aluguel de Veiculos        |\n");
        printf(" |______________________________________|\n");
        printf("\n\nClientes: \n\n");

        //printa os clietes
        ListarClientes();

        printf("\nInforme o CPF do Cliente\n");
        scanf("%s", cpf);

        //verificando CPF
        Verificacao_CPF = VerificarCPF(cpf); // Verificacao_CPF recebe a posicao do cpf, caso n encontre retorna -1

         if (Verificacao_CPF > -1) 
        {
            system("cls");
        //CPF Encontardo
                j = Verificacao_CPF ;// recebe o indice do CPF no repositorio
                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |        RW Aluguel de Veiculos        |\n");
                printf(" |______________________________________|\n\n");
                //printa os dados do cliente selecionado
                printf(" |CLIENTE: CPF: %s NOME: %s\n\n", RW_Veiculos.pessoa[j].cpf, RW_Veiculos.pessoa[j].nome_completo);
                printf(" |Veiculos Disponiveis: \n\n");

                ListaVeiculosDisponiveis(); //lista apenas os veiculos que podem ser alugados

                printf("\n\nInforme a placa do veiculo escolhido: \n");
                scanf("%s", placa);

                // verifica o veiculo e se ele esta disponivel
                for (L=0; L<RW_Veiculos.prox_carro;L++)
                {
                    if (strcmp(placa, RW_Veiculos.carro[L].placa)==0 && RW_Veiculos.carro[L].dispo==0)
                    {
                        //VEiculo encontrado
                        telaERRO = 1; //faz com que a tela de erro 2 nao seja executada
                        printf("\n\nPor quantos dias deseja alugar o veiculo?\n");
                        scanf("%d", &dias);
                        valor_aluguel = dias * (RW_Veiculos.carro[L].valor*0.005);

                        /// Imprime A pagina padrao com os dados do aluguel
                        VisualizarAluguel(RW_Veiculos.pessoa[j].nome_completo, RW_Veiculos.pessoa[j].cpf, RW_Veiculos.pessoa[j].telefone, RW_Veiculos.carro[L].codigocarro,
                                          RW_Veiculos.carro[L].placa, RW_Veiculos.carro[L].modelo, RW_Veiculos.carro[L].chassi, RW_Veiculos.carro[L].ano_de_fabricacao,
                                           RW_Veiculos.carro[L].valor, RW_Veiculos.carro[L].valor*0.005, dias, valor_aluguel);
                        // fim da fucao visualizarAluguel

                        printf(" |\n");
                        printf(" |___________________________\n");
                        printf(" | 1 - Concluir Aluguel.     |\n");
                        printf(" | 2 - Cancelar.             |\n");
                        printf(" |___________________________|\n");
                        scanf("%d", &continuar);


                        if(continuar == 1){ //caso os dados sejam confirmados sao entao encaminhados para o registro ser efetuado
                        cliente = j; //j e a posicao do cliente que foi retornada na verificacao
                        veiculo = L; //L e a posicao do veiculo que foi retornada na verificacao

                        RegistrarAluguel(cliente, veiculo, dias, valor_aluguel); //dados sao enviado para o resistro

                        system("cls");
                        printf("  ______________________________________\n");
                        printf(" |                                      |\n");
                        printf(" |        RW Aluguel de Veiculos        |\n");
                        printf(" |______________________________________|\n");
                        printf(" |                                      |\n");
                        printf(" |     Veiculo Alugado com Sucesso!     |\n");
                        printf(" |                                      |\n");
                        printf(" | CODIGO DA OPERACAO: #%d             |\n", RW_Veiculos.Ordem_Aluguel[RW_Veiculos.prox_aluguel-1].codigo_aluguel);
                        printf(" |______________________________________|\n\n\n");

                        opcao_tela_0 = 2; //faz com que apos concluir saia do loop do while
                        }
                        else { //caso tenha sido escolhido cancelar
                            system("cls");
                            printf("  ______________________________________\n");
                            printf(" |                                      |\n");
                            printf(" |         Operacao Cancelada!          |\n");
                            printf(" |______________________________________|\n\n");

                            opcao_tela_0 = 2; // faz voltar para o meni inicial
                        }

                        system("pause");

                    }
                }
                if (telaERRO ==0) //tela de erro para quando o veiculo ja esta alugado ou nao foi encontrado
                {
                    system("cls");
                    opcao_tela_0 =2; //faz com que saia da tela de aluguel
                    printf("  ______________________________________\n");
                    printf(" |                                      |\n");
                    printf(" |             RW Veiculos              |\n");
                    printf(" |______________________________________|\n");
                    printf(" |                                      |\n");
                    printf(" |      Veiculo nao encontrado ou       |\n");
                    printf(" |    indisponivel, tente novamente     |\n");
                    printf(" |                                      |\n");
                    printf(" |______________________________________|\n\n\n");
                    system("pause");
                }
        }
        if (Verificacao_CPF < 0)
        {
            TelaClienteNaoEncontrado();
            printf("  ______________________________________\n");
            printf(" | 1 - Cadastrar Cliente.               |\n");
            printf(" | 2 - Menu Inicial.                    |\n");
            printf(" |______________________________________|\n");

            scanf("%d", &opcao_tela_0);
            if (opcao_tela_0 == 1)
            {
                CadastrarCliente();
            }
        }

    }while(opcao_tela_0 != 2);
    system("cls");

}

//funcao que mostra os contratos de aluguel
void VisualizarContratosDeAluguel(){

    int i, x;
    system("cls");
    printf("  ______________________________________\n");
    printf(" |                                      |\n");
    printf(" |              RW Veiculos             |\n");
    printf(" |______________________________________|\n");
    printf("\n |Contratos Ativos:\n\n");

    for(i=0; i<RW_Veiculos.prox_aluguel; i++)
    {
        x=i;
        if(RW_Veiculos.Ordem_Aluguel[x].ativo==0){
            printf("__________________________________________________________________________\n\n");

        //funcao printa os alugueis
        VisualizarAluguel(RW_Veiculos.Ordem_Aluguel[x].pessoa.nome_completo, RW_Veiculos.Ordem_Aluguel[x].pessoa.cpf, RW_Veiculos.Ordem_Aluguel[x].pessoa.telefone,
                          RW_Veiculos.Ordem_Aluguel[x].carro.codigocarro, RW_Veiculos.Ordem_Aluguel[x].carro.placa, RW_Veiculos.Ordem_Aluguel[x].carro.modelo,
                          RW_Veiculos.Ordem_Aluguel[x].carro.chassi, RW_Veiculos.Ordem_Aluguel[x].carro.ano_de_fabricacao, RW_Veiculos.Ordem_Aluguel[x].carro.valor,
                          RW_Veiculos.Ordem_Aluguel[x].carro.valor*0.005, RW_Veiculos.Ordem_Aluguel[x].tempo_aluguel, RW_Veiculos.Ordem_Aluguel[x].valor_Total_aluguel);
        //funcao printa os alugueis
        // Sim, sao 4 linhas de parametro!
        printf(" | CODIGO DA OPERACAO..... #%d\n",RW_Veiculos.Ordem_Aluguel[x].codigo_aluguel);
        printf(" |______________________________________|\n\n");

        }
    }
    system("pause");
}

void FinalizarContrato()
{
    int i,j, codigo, telaErro =0;
    char placa [20];
    printf("  ______________________________________\n");
    printf(" |                                      |\n");
    printf(" |              RW Veiculos             |\n");
    printf(" |______________________________________|\n\n\n");

    for (i=0; i< RW_Veiculos.prox_aluguel; i++)
    {
        if(RW_Veiculos.Ordem_Aluguel[i].ativo==0) //0 representa contratos ativos
        {
            printf(" | CODIGO DO CONTRATO: %d | CPF DO CLIENTE: %s | PLACA DO VEICULO: %s\n", RW_Veiculos.Ordem_Aluguel[i].codigo_aluguel, RW_Veiculos.Ordem_Aluguel[i].pessoa.cpf, RW_Veiculos.Ordem_Aluguel[i].carro.placa);
        }
    }

    printf("\n\n |Informe o codigo do contrato que deseja encerrar:\n");
    scanf("%d", &codigo);

    for (i=0; i< RW_Veiculos.prox_aluguel; i++)
    {
        if(codigo == RW_Veiculos.Ordem_Aluguel[i].codigo_aluguel)
        {
            system("cls");
            telaErro =1;// evita que a tela de erro seja iniciada
            RW_Veiculos.Ordem_Aluguel[i].ativo = 1; // ou seja desativa o contrato
            strcpy(placa, RW_Veiculos.Ordem_Aluguel[i].carro.placa);

            ////// Este For faz com que o carro volte a ficar disponivel apos finalizar contrato.
                for(j=0; j <RW_Veiculos.prox_carro;j++)
                {
                    if(strcmp(placa,RW_Veiculos.carro[j].placa)==0)
                    {
                        RW_Veiculos.carro[j].dispo=0; //dispo 0 significa, disponivel para alugar.
                    }
                }
                printf("  ______________________________________\n");
                printf(" |                                      |\n");
                printf(" |    Contrato Finalizado com Sucesso!  |\n");
                printf(" |______________________________________|\n\n\n");
        }
    }
    if (telaErro ==0)
    {
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |    ERRO: Contrato Nao Enconrado!     |\n");
        printf(" |______________________________________|\n\n\n");
    }


    system("pause");
}
///////////FIM DAS FUNCOES DE CONTRATO ///////////


//Esta funcao Iniciar foi criada para auxiliar no uso no codigo
//ELa deixa 5 Clientes cadastrado
// 9 Veiculos, dos quais 3 ja alugados (para exemplo)
// 3 registros de aluguel
//VAle salientar que todos esses dados podem ser removidos/alterado quando o programa for iniciado
void iniciar(){

    RegistrarCliente("Robert Freire de Melo", "583.650.824-13", "87 991656586");
    RegistrarCliente("William Batista Couto Dos Santos", "856.583.654-15", "81 995725052");
    RegistrarCliente("Ivan Aparecido Gomes Monteiro", "715.956.780-57", "81 994756810");
    RegistrarCliente("Laura Ribeiro Morais", "426.068.759-54", "81 996581684");
    RegistrarCliente("Jose dos testes", "123", "87 0000000");

    RegistrarVeiculo("Volkswagen Gol 2022", "BRA-3121", 2022, "9BRGOLVOLKS2022", 65000.00);
    RegistrarVeiculo("Volkswagen Voyage 2020", "OYV-0H87", 2020, "9BRVOYAGVOL2020", 68000.00);
    RegistrarVeiculo("Toyota Corolla 2022", "ITH-5M23", 2022, "7BRCOROLTOYO2022", 130000.00);
    RegistrarVeiculo("Fiat Argo 2021", "OGM-4V07", 2021, "7BRCOROLTOYO2022", 65000.00);
    RegistrarVeiculo("Fiat Uno", "WIL-2G98", 2003, "7EUFIATLAR2003", 12000.00);
    RegistrarVeiculo("Fusca", "ROB-8E75", 2022, "5BRFUSCTSA22021", 150000.00);
    RegistrarVeiculo("Range Rover Evoque 2020 ", "RGE-2V09", 2020, "9EURANDROV2020", 500000.00);
    RegistrarVeiculo("Mercedes-AMG GT 63", "MCS-4G78", 2022, "9EURANDROV2020", 1300000.00);
    RegistrarVeiculo("Lamborghini Huracan 2015", "LUI-9S54", 2015, "9EULAMBHUR2015", 2500000.00);
    RegistrarVeiculo("Porsche Cayenne 2021 ", "NOR-4M67", 2021, "9EUPORSHCAY2021", 1500000.00);

    RegistrarAluguel (2, 3,5, 1625.00);
    RegistrarAluguel (1, 6,3, 7500.00);
    RegistrarAluguel (0, 7,3, 19500.00);

}

int main()
{
    
    int opc, opcao2,opc3, opc1; 

    //iniciando variaveis uteis
    RW_Veiculos.Ordem_Aluguel[0].valor_diaria=0.0;
    RW_Veiculos.Ordem_Aluguel[0].valor_Total_aluguel=0.0;
    RW_Veiculos.Ordem_Aluguel[0].tempo_aluguel=0;
    RW_Veiculos.Ordem_Aluguel[0].codigo_aluguel=150;
    RW_Veiculos.prox_carro=0;
    RW_Veiculos.prox_cliente=0;
    RW_Veiculos.pessoa[0].codigocliente[0] = 1322;
    RW_Veiculos.carro[0].codigocarro = 2145;

    iniciar(); //funcao para iniciar dados pre cadastrados

   do{


    //////////////////MENU PRINCIPAL ////////////////
    printf(" ______________________________________\n");
    printf("|                                      |\n");
    printf("|              RW Veiculos             |\n");
    printf("|______________________________________|\n");
    printf("|                                      |\n");
    printf("|1 ......... Contratos.                |\n");
    printf("|2 ......... Clientes.                 |\n");
    printf("|3 ......... Veiculos.                 |\n");
    printf("|4 ......... Alugar veiculo.           |\n");
    printf("|9 ......... Sair.                     |\n");
    printf("|______________________________________|\n");
    scanf("%d", &opc);


    if (opc ==1 ) //contratos
    {
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" |1 .......... Contratos Ativos.        |\n");
        printf(" |2 .......... Novo contrato de Aluguel |\n");
        printf(" |3 .......... Finalizar contrato.      |\n");
        printf(" |5 .......... Voltar                   |\n");
        printf(" |______________________________________|\n");
        scanf("%d", &opc1);

        if(opc1==1)
        {
            VisualizarContratosDeAluguel();
        }
        if(opc1== 2)
        {
            Alugar();
        }
        if(opc1 == 3)
        {
            system("cls");
            FinalizarContrato();
        }

    }
    else if (opc ==2 ) //clientes
    {
        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" |1 .......... Cadastrar Cliente.       |\n");
        printf(" |2 .......... Consultar Cliente.       |\n");
        printf(" |3 .......... Editar Cliente.          |\n");
        printf(" |4 .......... Remover Cliente.         |\n");
        printf(" |5 .......... Voltar                   |\n");
        printf(" |______________________________________|\n");
        scanf("%d", &opcao2);

        system ("cls");

        if (opcao2 == 1 )
        {
            CadastrarCliente();
        }

        if (opcao2 == 2)
        {
            ConsultarCliente();
        }

        if(opcao2 == 3)
        {
            EditarCliente();
        }

        if(opcao2 == 4)
        {
            RemoverCliente();
        }
    }

    else if (opc ==3 ) // veiculos
    {

        system("cls");
        printf("  ______________________________________\n");
        printf(" |                                      |\n");
        printf(" |              RW Veiculos             |\n");
        printf(" |______________________________________|\n");
        printf(" |                                      |\n");
        printf(" |1 .......... Cadastrar Veiculo.       |\n");
        printf(" |2 .......... Consultar Veiculo.       |\n");
        printf(" |3 .......... Editar Veiculo.          |\n");
        printf(" |4 .......... Remover Veiculo.         |\n");
        printf(" |5 .......... Voltar                   |\n");
        printf(" |______________________________________|\n");
        scanf("%d", &opc3);
        system ("cls");

        if (opc3 == 1)
        {
            CadastrarVeiculo();
        }
        else if (opc3 == 2)
        {
            VisualizarVeiculo();
        }
        else if (opc3 == 3)
        {
            EditarVeiculo();
        }
        else if (opc3 == 4)
        {
            RemoverVeiculo();
        }

    }
     else if (opc ==4 ) //alugar
    {
        Alugar();
        opc =11; //para continuar o loop - 11 n existe.
    }

    system("cls");
   }while(opc!=9); //sair do codigo

    system("cls");
    printf("  _____________________________________________________\n");
    printf(" |                                                     |\n");
    printf(" |                      RW Veiculos                    |\n");
    printf(" |_____________________________________________________|\n");
    printf(" |                                                     |\n");
    printf(" |   Universidade Federal do Agrestre de Pernambuco    |\n");
    printf(" |       Bacharelado em Ciencia da Computacao          |\n");
    printf(" |                                                     |\n");
    printf(" | Desenvolvido por:                                   |\n");
    printf(" |                                                     |\n");
    printf(" | Robert Freire de Melo                               |\n");
    printf(" | William Batista Couto dos Santos                    |\n");
    printf(" |                                                     |\n");
    printf(" | Version 0.2.5  Ultimate               19/04/2022    |\n");
    printf(" |_____________________________________________________|\n\n");
    system("pause");

    return 0;
}
