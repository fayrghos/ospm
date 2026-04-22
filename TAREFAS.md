# Tarefas

## Obrigatórias

- [x] Permitir informar a quantidade de processos (N)
- [x] Permitir informar, para cada processo: tempo de CPU e tempo de disco (E/S)
- [x] Permitir informar, a quantidade de rodadas de execuções para cada processo.
- [x] Permitir definir o quantum da CPU
- [x] Permitir definir o tempo total de simulação

## Regras

- [X] Os processos devem ser organizados em uma fila circular (FIFO)
- [X] Cada processo executa por no máximo o quantum definido
- [X] Se terminar antes do quantum, sai da CPU
- [X] Se não terminar, volta ao final da fila
- [X] Processos que entram em E/S devem ir para uma fila de espera e retornar depois
- [X] A simulação deve ocorrer em unidades discretas de tempo

## Saídas

- [x] Linha do tempo da execução dos processos
- [ ] Tempo de espera, resposta para cada processo
- [ ] Uso da CPU (%)
- [ ] Quantidade de processos finalizados
- [ ] Tempo médio de espera
