Sistema baseado em IoT desenvolvido para monitorar 
níveis de ruído em ambientes de estudo e trabalho de maneira prática e eficiente. O protótipo 
utiliza um microcontrolador ESP32 e um sensor de som simulado para coletar os dados do 
ambiente, enviá-los via MQTT e processá-los no Node-RED. As informações são 
armazenadas na nuvem por meio do banco InfluxDB e exibidas em tempo real em 
dashboards configurados no Grafana. O sistema também se integra à API do Telegram para 
enviar alertas automáticos sempre que o nível de ruído ultrapassa um limite definido, 
permitindo que o usuário tome providências rapidamente.
