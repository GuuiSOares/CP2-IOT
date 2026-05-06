# Monitoramento Inteligente com IoT - CP2 FIAP

## 👥 Desenvolvido por TriCode:
* Guilherme Soares de Almeida | 563143 |
* Lucas Silva Gastão Pinheiro | 563960 |
* Geovanne Coneglian Passos | 562673 |

## 📝 Descrição do Projeto
Este projeto consiste em uma solução de monitoramento em tempo real de variáveis ambientais e de processo (temperatura, umidade e distância) utilizando conceitos de IoT. A solução abrange desde a coleta de dados via sensores em um microcontrolador ESP32 até a persistência em banco de dados e exibição em um dashboard interativo.

O sistema foi desenvolvido para atender aos requisitos do Checkpoint 2 (CP2), demonstrando a integração entre hardware simulado, protocolos de comunicação, serviços de nuvem, APIs externas e armazenamento de dados.

## 🏗️ Arquitetura da Solução
A arquitetura segue o modelo de camadas para IoT:
1.  **Dispositivo (Edge):** ESP32 simulado no Wokwi, realizando a leitura de sensores de Temperatura/Umidade (DHT22) e Distância (Ultrassônico).
2.  **Protocolo de Comunicação:** MQTT utilizando o broker público HiveMQ para o envio das mensagens.
3.  **Back-end (Ingestão e Processamento):** Node-RED atuando como o orquestrador, recebendo os dados via MQTT, consumindo dados climáticos externos via API e processando a lógica de negócio.
4.  **Integração Externa:** Consumo da API Open-Meteo para obter a temperatura real da cidade de São Paulo.
5.  **Persistência (Storage):** Banco de Dados Relacional SQLite para armazenamento do histórico de medições.
6.  **Visualização (Dashboard):** Interface gráfica desenvolvida no Node-RED Dashboard com indicadores (gauges), gráficos e informações textuais.

## 🛠️ Tecnologias Utilizadas
* **Hardware:** ESP32 (Simulação Wokwi)
* **Protocolo:** MQTT (Broker HiveMQ)
* **Ferramenta de Fluxo:** Node-RED
* **Banco de Dados:** SQLite (escolhido pela portabilidade e eficiência em ambientes de laboratório)
* **API Externa:** Open-Meteo (Dados Climáticos)
* **Linguagens:** C++ (Arduino IDE/Wokwi), JavaScript (Node-RED Functions), SQL

## 🚀 Instruções de Execução

### 1. Simulação do Hardware (Wokwi)
1.  Acesse o projeto no Wokwi.
2.  Garanta que o código do ESP32 esteja configurado para conectar ao broker `broker.hivemq.com` nos tópicos:
    * `fiap/guilherme/temperatura`
    * `fiap/guilherme/umidade`
    * `fiap/guilherme/distancia`
3.  Inicie a simulação.

### 2. Configuração do Node-RED
1.  Importe o arquivo JSON do fluxo para o seu Node-RED.
2.  Certifique-se de que os nós `mqtt in` estão apontando para o mesmo broker e tópicos da simulação.
3.  **Banco de Dados:** O nó `sqlite` (banco.db) criará automaticamente o arquivo na primeira execução. Clique no nó `timestamp` conectado à função de criação de tabela para garantir a estrutura inicial.
4.  Dê o **Deploy** no fluxo.

### 3. Visualização
1.  Acesse o dashboard pelo endereço: `http://localhost:1880/ui`.
2.  Verifique se os medidores de Temperatura, Umidade e Distância estão atualizando.
3.  Confirme se o campo "Clima Real SP" está exibindo os dados vindos da API externa.
4.  Para validar o banco de dados, clique no nó "Ver Banco" e verifique a saída no painel de debug.
