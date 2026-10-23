# Sistema de Cadastro de Alunos em C

Sistema de gerenciamento de alunos em linha de comando, com autenticação de usuários e persistência de dados em arquivos de texto.

## 📌 Sobre o projeto

Projeto desenvolvido na disciplina de **Fundamentos de Programação**. O programa permite cadastrar e gerenciar alunos, com acesso protegido por login e senha.

## ⚙️ Funcionalidades

**Autenticação**
- Login com senha criptografada
- Cadastro de novos usuários, sem permitir logins repetidos
- Validação de senha: de 10 a 30 caracteres, com pelo menos 2 letras maiúsculas, 1 minúscula e 1 caractere especial

**Gerenciamento de alunos**
- Inserir aluno, sem permitir matrículas repetidas
- Listar todos, só os ativos ou só os inativos
- Listar ordenado por nome ou matrícula
- Alterar aluno por matrícula
- Alterar aluno pela posição (k-ésimo)
- Remover aluno, com confirmação

## 🧠 Como funciona

- Os dados dos alunos ficam em `aluno.txt` e os usuários em `usuario.txt`, com campos separados por `;`.
- Cada aluno tem matrícula, nome, curso, período, situação, data de nascimento e data de cadastro (preenchida automaticamente).
- As senhas são gravadas com uma criptografia simples, que desloca cada caractere.
- A ordenação usa o algoritmo Bubble Sort.
- Limite de 100 alunos para ordenação e alteração.

## 💻 Como compilar e executar

```bash
gcc main.c -o cadastro
./cadastro
```

No Windows, execute `cadastro.exe`.

## 🛠️ Tecnologias

- Linguagem C
- Structs, manipulação de arquivos e strings

## 📌 Observação

Projeto com fins educacionais. A criptografia de senha é didática e não deve ser usada em sistemas reais.
