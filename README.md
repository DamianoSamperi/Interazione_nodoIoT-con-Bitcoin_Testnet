# Interazione_nodoIoT-con-Bitcoin_Testnet

Questo è un progetto realizzato con Arduino IDE utilizzando la board Esp32 Wroom32 che monitora un movimento continuo tramite sensore PIR in caso il movimento duri per un tempo di 10 secondi viene creata,firmata e inviata una transazione .
Nella transazione viene utilizzato uno script OP_RETURN che mi inserisce nella transazione una stringa "true" in formato esadecimale (è possibile inviare una qualunque stringa, invito a informarsi sul funzionamento dello scritp OP_RETURN)

## Come usare la libreria uBitcoin con la modifica al Network
questo progetto utilizza una libreria modificata, per via di un oggetto omonimo Network nelle librerie Wifi.h e uBitcoin.h ; La libreria è inclusa nel repository nella cartella `libraries/ubitcoin`.

1. Clona o scarica il repository.
2. Apri il progetto con l'IDE di Arduino.
3. Assicurati che la libreria sia correttamente inclusa nel progetto. Non è necessario installare la libreria separatamente.
   
## Visualizzare board Esp32 su Arduino IDE

- Andare su preferenze e nella sezione "Additional board manager URLs" inserire questo:  
  `"https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json"`

  - Sulla board manager di Arduino IDE installare "esp32 by Espressif System".

- Potrebbe essere necessario installare un driver per rilevare la board dal sistema operativo:
  - Nel caso di **Windows**: [Driver CH341 per Windows](https://www.wch-ic.com/downloads/ch341ser_exe.html)
  - Nel caso di **Linux**: [Driver CH341 per Linux](https://www.wch-ic.com/downloads/CH341SER_LINUX_ZIP.html)

- Sempre su **Windows**, potrebbe essere necessario scaricare il driver per far rilevare le porte da Windows: [CP210x Universal Windows Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers).

- All'interno dell'Arduino IDE, se non viene selezionata in automatico, scegli la board **"DOIT ESP32 DEVKIT V1"**.


## Procedure per l'utilizzo del progetto

1. Registrarsi su **BlockCypher** e copiare il proprio token nel progetto.
2. Il progetto richiede due wallet **Bitcoin Testnet** (non indirizzi **SegWit** poiché la procedura di firma non li gestisce).
   - È possibile anche utilizzare un solo wallet mittente e creare una transazione verso una faucet.
   - Ovviamente, il wallet mittente deve avere asset all'interno. Puoi ricaricare il tuo wallet Bitcoin Testnet tramite il faucet: [https://coinfaucet.eu/en/btc-testnet/](https://coinfaucet.eu/en/btc-testnet/).
3. Il progetto utilizza un LED e un sensore **Groove PIR**. 
   - Si possono modificare i PIN in base alle esigenze.
   - Il sensore PIR deve essere impostato in modalità **N_retrig** per monitorare un movimento continuo.

## Dipendenze

Dal library manager di **Arduino IDE**:
- Installare la libreria **ArduinoJson**.

