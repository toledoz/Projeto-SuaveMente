# Projeto Final – UC 4: Analisar Programação Estruturada e Orientada a Objetos

## ⚠️ Aviso aos Alunos

Todos os projetos finais deverão conter este cabeçalho institucional no início do arquivo `README.md`. A ausência desse cabeçalho poderá impactar na avaliação final do trabalho.

---

**SENAC DF – Centro de Educação Profissional Jó Rufino e Carlos Aguiar – Taguatinga**  
**Curso:** Técnico em Desenvolvimento de Sistemas  
**Turma:** 2025.08.53  
**Unidade Curricular:** UC 4 – Analisar Programação Estruturada e Orientada a Objetos  
**Professor Orientador:** Hudson Neves  

**Aluno(a):** Gabriel Toledo de Faria 
**Data:** 06/26/2025

📋 Sistema de Atendimento e Prontuário Médico
Este projeto é um sistema simples, desenvolvido em linguagem C, que permite gerenciar pacientes, consultas e prontuários médicos. Ele simula um fluxo de atendimento básico para clínicas ou consultórios médicos.

📌 Funcionalidades
O sistema é baseado em um menu principal que dá acesso às seguintes funcionalidades:

Cadastrar Paciente
Permite registrar novos pacientes, armazenando dados como nome, e-mail, RG, endereço e se o paciente possui plano de saúde.

Listar Pacientes
Exibe todos os pacientes cadastrados no sistema.

Atualizar Cadastro
Permite editar os dados de um paciente previamente cadastrado.

Agendar Consulta
Realiza o agendamento de uma nova consulta com data e hora para um paciente existente.

Listar Todas as Consultas
Exibe todas as consultas cadastradas no sistema, independentemente do paciente.

Listar Consultas por Paciente
Mostra as consultas específicas de um paciente, permitindo filtragem individual.

Cancelar Consulta
Permite o cancelamento de uma consulta previamente agendada.

Criar Prontuário
Gera um prontuário médico vinculado a uma consulta específica.

Adicionar ao Prontuário
Insere novas anotações ou informações médicas ao prontuário existente de um paciente.

Exibir Prontuário
Visualiza o histórico de prontuários e atendimentos de um paciente.

Sair
Encerra o programa e finaliza o sistema.

📊 Fluxo do Sistema
O diagrama mostra o fluxo principal do sistema:

O usuário inicia no Menu Principal, onde escolhe uma das opções.

Após cada operação, o sistema retorna ao menu.

O processo termina ao selecionar a opção Sair.

🛠 Tecnologias Utilizadas
Linguagem: C

Ambiente de Desenvolvimento: Qualquer compilador C (Code::Blocks, Dev-C++, GCC, etc.)

Interface: Terminal (modo texto)

🧪 Como Usar
Compile o código-fonte em C com seu compilador favorito.

Execute o programa.

Navegue pelo menu digitando o número da opção desejada.

Siga as instruções exibidas na tela para cada funcionalidade.

📂 Estrutura Recomendada
bash
Copiar
Editar
projeto/
├── main.c
├── pacientes.h / pacientes.c
├── consultas.h / consultas.c
├── prontuarios.h / prontuarios.c
├── README.md
