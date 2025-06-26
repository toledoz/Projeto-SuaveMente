#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// ===================== CONFIG =====================
#define MAX_PACIENTES 100
#define MAX_CONSULTAS 100
#define MAX_PRONTUARIOS 100
#define MAX_ENTRADAS 10

// ===================== STRUCTS =====================
typedef struct {
    char nome[100];
    char cpf[15];
    int idade;
    char telefone[20];
} Paciente;

typedef struct {
    char cpfPaciente[15];
    char data[11];
    char hora[6];
    char profissional[100];
    int ativo;
} Consulta;

typedef struct {
    char descricao[1000];
    char data[11];
} EntradaProntuario;

typedef struct {
    char cpfPaciente[15];
    EntradaProntuario entradas[MAX_ENTRADAS];
    int totalEntradas;
} Prontuario;

// ===================== VARIÁVEIS =====================
Paciente pacientes[MAX_PACIENTES];
int totalPacientes = 0;

Consulta consultas[MAX_CONSULTAS];
int totalConsultas = 0;

Prontuario prontuarios[MAX_PRONTUARIOS];
int totalProntuarios = 0;

// ===================== FUNÇÕES DE SUPORTE =====================
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void exibirPaciente(Paciente p) {
    printf("Nome: %s\n", p.nome);
    printf("CPF: %s\n", p.cpf);
    printf("Idade: %d\n", p.idade);
    printf("Telefone: %s\n", p.telefone);
}

void exibirConsulta(Consulta c) {
    printf("CPF do paciente: %s\n", c.cpfPaciente);
    printf("Data: %s\n", c.data);
    printf("Hora: %s\n", c.hora);
    printf("Profissional: %s\n", c.profissional);

    // Cores ANSI: verde para agendada, vermelho para cancelada
    if (c.ativo) {
        printf("Status: \033[0;32mAgendada\033[0m\n");
    } else {
        printf("Status: \033[0;31mCancelada\033[0m\n");
    }
}


int buscarPacientePorCPF(char cpf[]) {
    for (int i = 0; i < totalPacientes; i++) {
        if (strcmp(pacientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

// ===================== MÓDULO PACIENTES =====================
void cadastrarPaciente() {
    limparTela();

    if (totalPacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }

    Paciente novo;
    printf("\n=== Cadastro de Paciente ===\n");
    printf("Nome: ");
    getchar();
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("CPF (somente numeros): ");
    scanf("%s", novo.cpf);

    if (buscarPacientePorCPF(novo.cpf) != -1) {
        printf("Paciente ja cadastrado.\n");
        return;
    }

    printf("Idade: ");
    scanf("%d", &novo.idade);
    printf("Telefone: ");
    scanf("%s", novo.telefone);

    pacientes[totalPacientes++] = novo;
    printf("\033[1;32mPaciente cadastrado com sucesso!\033[0m\n"); //***************************************************************** 
}

void listarPacientes() {
    limparTela();

    if (totalPacientes == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    char voltar;
    do {
        limparTela();
        printf("\n=== Lista de Pacientes ===\n");
        for (int i = 0; i < totalPacientes; i++) {
            printf("\nPaciente %d:\n", i + 1);
            exibirPaciente(pacientes[i]);
        }
        printf("\nDigite 'v' para voltar ao menu: ");
        getchar();
        scanf("%c", &voltar);
    } while (voltar != 'v');
}

void atualizarCadastroPaciente() {
    limparTela();

    char cpf[15];
    printf("\n=== Atualizar Cadastro de Paciente ===\n");
    printf("Digite o CPF do paciente: ");
    scanf("%s", cpf);

    int indice = buscarPacientePorCPF(cpf);
    if (indice == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    Paciente *p = &pacientes[indice];

    printf("\nNovo nome: ");
    getchar();
    fgets(p->nome, sizeof(p->nome), stdin);
    p->nome[strcspn(p->nome, "\n")] = 0;

    printf("Nova idade: ");
    scanf("%d", &p->idade);

    printf("Novo telefone: ");
    scanf("%s", p->telefone);

    printf("\n\033[1;32mCadastro atualizado com sucesso!\033[0m\n"); // *************************************************************************************
}

// ===================== MÓDULO CONSULTAS =====================
void agendarConsulta() {
    limparTela();

    if (totalConsultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    char cpf[15];
    printf("\n=== Agendar Consulta ===\n");
    printf("CPF do paciente: ");
    scanf("%s", cpf);

    if (buscarPacientePorCPF(cpf) == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    Consulta nova;
    strcpy(nova.cpfPaciente, cpf);
    printf("Data (dd/mm/aaaa): ");
    scanf("%s", nova.data);
    printf("Hora (hh:mm): ");
    scanf("%s", nova.hora);
    getchar();
    printf("Profissional: ");
    fgets(nova.profissional, sizeof(nova.profissional), stdin);
    nova.profissional[strcspn(nova.profissional, "\n")] = 0;
    nova.ativo = 1;

    consultas[totalConsultas++] = nova;
    printf("\033[1;32mConsulta agendada com sucesso!\033[0m\n"); //aquiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
}

void listarConsultasPorPaciente() {
    char cpf[15];

    while (1) {
        limparTela();
        printf("\n=== Consultas por Paciente ===\n");
        printf("Digite o CPF ou '0' para voltar: ");
        scanf("%s", cpf);
        if (strcmp(cpf, "0") == 0) return;

        int encontrou = 0;
        for (int i = 0; i < totalConsultas; i++) {
            if (strcmp(consultas[i].cpfPaciente, cpf) == 0) {
                printf("\nConsulta %d:\n", i + 1);
                exibirConsulta(consultas[i]);
                encontrou = 1;
            }
        }
        if (!encontrou) {
            printf("Nenhuma consulta encontrada.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); getchar();
    }
}

void listarTodasConsultas() {
    limparTela();

    if (totalConsultas == 0) {
        printf("Nenhuma consulta cadastrada.\n");
        printf("\nPressione Enter para voltar...");
        getchar(); getchar();
        return;
    }

    printf("\n=== TODAS AS CONSULTAS AGENDADAS ===\n");
    for (int i = 0; i < totalConsultas; i++) {
        printf("\nConsulta %d:\n", i + 1);
        exibirConsulta(consultas[i]);
    }

    printf("\nPressione Enter para voltar...");
    getchar(); getchar();
}

void cancelarConsulta() {
    limparTela();

    char cpf[15], data[11], hora[6];
    printf("\n=== Cancelar Consulta ===\n");
    printf("CPF: ");
    scanf("%s", cpf);
    printf("Data: ");
    scanf("%s", data);
    printf("Hora: ");
    scanf("%s", hora);

    for (int i = 0; i < totalConsultas; i++) {
        if (strcmp(consultas[i].cpfPaciente, cpf) == 0 &&
            strcmp(consultas[i].data, data) == 0 &&
            strcmp(consultas[i].hora, hora) == 0 &&
            consultas[i].ativo == 1) {
            consultas[i].ativo = 0;
            printf("\033[1;32mConsulta cancelada com sucesso.\033[0m\n"); // *****************************************************************
            return;
        }
    }
    printf("Consulta nao encontrada.\n");
}

// ===================== MÓDULO PRONTUÁRIOS =====================
void criarProntuario() {
    limparTela();

    if (totalProntuarios >= MAX_PRONTUARIOS) {
        printf("Limite de prontuarios atingido.\n");
        return;
    }

    char cpf[15];
    printf("\n=== Criar Prontuario ===\n");
    printf("CPF do paciente: ");
    scanf("%s", cpf);

    if (buscarPacientePorCPF(cpf) == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    for (int i = 0; i < totalProntuarios; i++) {
        if (strcmp(prontuarios[i].cpfPaciente, cpf) == 0) {
            printf("Prontuario ja existe.\n");
            return;
        }
    }

    Prontuario novo;
    strcpy(novo.cpfPaciente, cpf);
    novo.totalEntradas = 0;
    prontuarios[totalProntuarios++] = novo;
    printf("\033[1;32mProntuario criado.\033[0m\n"); // *******************************************************************
}

void adicionarInformacaoProntuario() {
    limparTela();

    char cpf[15];
    printf("\n=== Adicionar ao Prontuario ===\n");
    printf("CPF do paciente: ");
    scanf("%s", cpf);

    for (int i = 0; i < totalProntuarios; i++) {
        if (strcmp(prontuarios[i].cpfPaciente, cpf) == 0) {
            if (prontuarios[i].totalEntradas >= MAX_ENTRADAS) {
                printf("Limite de entradas atingido.\n");
                return;
            }

            EntradaProntuario nova;
            printf("Data (dd/mm/aaaa): ");
            scanf("%s", nova.data);
            getchar();
            printf("Descricao: ");
            fgets(nova.descricao, sizeof(nova.descricao), stdin);
            nova.descricao[strcspn(nova.descricao, "\n")] = 0;

            prontuarios[i].entradas[prontuarios[i].totalEntradas++] = nova;
            printf("\033[1;32mEntrada adicionada.\033[0m\n");
            return;
        }
    }
    printf("Prontuario nao encontrado.\n");
}

void exibirProntuario() {
    char cpf[15];

    while (1) {
        limparTela();
        printf("\n=== Exibir Prontuario ===\n");
        printf("Digite o CPF ou '0' para voltar: ");
        scanf("%s", cpf);
        if (strcmp(cpf, "0") == 0) return;

        for (int i = 0; i < totalProntuarios; i++) {
            if (strcmp(prontuarios[i].cpfPaciente, cpf) == 0) {
                printf("\nProntuario do paciente %s:\n", cpf);
                for (int j = 0; j < prontuarios[i].totalEntradas; j++) {
                    printf("\nEntrada %d:\n", j + 1);
                    printf("Data: %s\n", prontuarios[i].entradas[j].data);
                    printf("Descricao: %s\n", prontuarios[i].entradas[j].descricao);
                }
                printf("\nPressione Enter para voltar...");
                getchar(); getchar();
                return;
            }
        }
        printf("Prontuario nao encontrado.\n");
        printf("Pressione Enter para tentar novamente...");
        getchar(); getchar();
    }
}

// ===================== MAIN =====================
int main() {
    int opcao;

    do {
        limparTela();
        printf("=========================================\n");
        printf("|           Bem Vindo Membro            |\n");
        printf("|              SuaveMente!              |\n");
        printf("=========================================\n");  
        printf("|                                       |\n");                                               
        printf("| 1. Cadastrar Paciente                 |\n"); 
        printf("| 2. Listar Pacientes                   |\n");  
        printf("| 3. Atualizar Cadastro de Paciente     |\n");  
        printf("| 4. Agendar Consulta                   |\n"); 
        printf("| 5. Listar Todas as Consultas          |\n");
        printf("| 6. Listar Consultas por Paciente      |\n");
        printf("| 7. Cancelar Consulta                  |\n");
        printf("| 8. Criar Prontuario                   |\n");
        printf("| 9. Adicionar ao Prontuario            |\n");
        printf("| 10. Exibir Prontuario                 |\n");
        printf("| 0. Sair                               |\n");
        printf("|                                       |\n"); 
        printf("=========================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarPaciente(); break;
            case 2: listarPacientes(); break;
            case 4: agendarConsulta(); break;
            case 6: listarConsultasPorPaciente(); break;
            case 7: cancelarConsulta(); break;
            case 5: listarTodasConsultas(); break;
            case 8: criarProntuario(); break;
            case 9: adicionarInformacaoProntuario(); break;
            case 10: exibirProntuario(); break;
            case 3: atualizarCadastroPaciente(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida.\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar(); getchar();
    } while (opcao != 0);

    return 0;
}
