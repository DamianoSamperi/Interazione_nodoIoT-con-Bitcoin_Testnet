# Iterazione_nodoIoT-con-Bitcoin_Testnet

Questo è un progetto realizzato con Arduino IDE utilizzando la board Esp32 Wroom32 che monitora un movimento continuo tramite sensore PIR in caso il movimento duri per un tempo di 10 secondi viene creata,firmata e inviata una transazione .
Nella transazione viene utilizzato uno script OP_RETURN che mi inserisce nella transazione una stringa "true" in formato esadecimale (è possibile inviare una qualunque stringa, invito a informarsi sul funzionamento dello scritp OP_RETURN)

## Come usare la libreria uBitcoin con la modifica al Network
questo progetto utilizza una libreria modificata, per via di un oggetto omonimo Network nelle librerie Wifi.h e uBitcoin.h ; La libreria è inclusa nel repository nella cartella `libraries/ubitcoin`.

1. Clona o scarica il repository.
2. Apri il progetto con l'IDE di Arduino.
3. Assicurati che la libreria sia correttamente inclusa nel progetto. Non è necessario installare la libreria separatamente.
   
## Visualizzare board Esp32 su Arduino IDE
Andare su preferenze e nella sezione "Additional board manager URLs" inserire questo:  "https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json" ;
Sulla board manager di Arduino IDE installare "esp32 by Espressif System".
Potrebbe essere necessario installare un driver per rilevare la board dal sistema operativo:
nel caso di Windows: https://www.wch-ic.com/downloads/ch341ser_exe.html
nel caso di Linux: https://www.wch-ic.com/downloads/CH341SER_LINUX_ZIP.html
Sempre su Windows potrebbe essere necessario scaricare il driver per far rilevare le porte da Windows: CP210x_Universal_Windows_Driver

## Procedure per l'utilizzo del progetto
Registrarsi su BlockCypher e copiare il proprio token nel progetto.
Il Progetto richiede due wallet Bitcoin Testnet(non indirizzi Sigw32 poichè la procedura di signature non lo gestisce),
è possibile anche utilizzare un solo wallet mittente e creare una transazione verso una faucet.
Ovviamente il wallet mittente deve avere assets all'interno, puoi ricaricare il tuo wallet bitcoin testnet tramite il faucet: https://coinfaucet.eu/en/btc-testnet/
Il progetto utilizza un led e un sensore Groove PIR si possono modificare i PIN in base alle esigenze, il sensore PIR deve essere impostato in modalità N_retrig per monitorare un movimento continuo.
## Dipendenza
Dal library manager di Arduino IDE
- installare libreria ArduinoJson
