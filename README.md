# Projeto de Comunicação UDP: Sender & Receiver

Este projeto implementa uma comunicação simples via protocolo **UDP** entre dois programas em C: um **emissor (sender)** e um **receptor (receiver)**. O emissor lê o conteúdo de um arquivo de texto e envia as linhas por meio de pacotes UDP para o receptor, que os exibe no terminal.

---

## 📁 Estrutura do Projeto

```
.src
├── sender.c
├── receiver.c
├── text.txt
└── Makefile
```

---

## ⚙️ Compilação

Utilize o `Makefile` incluso para compilar os dois programas:

```bash
make all
```

Para remover os arquivos objeto e executáveis gerados:

```bash
make clean
```

---

## 🧠 Funcionamento

### Receiver (Receptor)

- Cria um socket UDP na porta `8080`.
- Aguarda por mensagens enviadas por um cliente.
- Imprime cada mensagem recebida no terminal.
- Permanece rodando indefinidamente até ser interrompido manualmente.

### Sender (Emissor)

- Lê o conteúdo do arquivo `text.txt`.
- Envia linha por linha para o endereço `127.0.0.1` na porta `8080`.
- Ao final, envia uma mensagem "EOF" indicando o fim da transmissão.

---

## 🧪 Como Usar

1. Compile os arquivos:

```bash
make all
```

2. Em um terminal, execute o receptor:

```bash
./receiver
```

3. Em outro terminal, execute o emissor:

```bash
./sender
```

4. O receptor exibirá as mensagens recebidas, linha por linha.

---

## 📝 Observações

- Certifique-se de que o arquivo `text.txt` esteja presente na raiz do projeto e contenha o conteúdo desejado.
- O IP `127.0.0.1` indica que a comunicação ocorre localmente. Para testar em máquinas diferentes, substitua esse IP no código do `sender.c` pelo IP do receptor.

---

## 📚 Tecnologias Utilizadas

- Linguagem C
- Sockets UDP
- Sistema Linux (recomendado para compilação e testes)

