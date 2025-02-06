# Interazione_nodoIoT-con-Bitcoin_Testnet

Questo progetto utilizza **Arduino IDE** e la board **ESP32 Wroom32** per monitorare il movimento continuo tramite un sensore **PIR**. Quando il movimento viene rilevato per un periodo di almeno 10 secondi, viene generata, firmata e inviata una transazione Bitcoin.

La transazione sfrutta uno **script OP_RETURN**, che permette di inserire una stringa (ad esempio, "true") in formato esadecimale all'interno della transazione. È possibile personalizzare la stringa da inviare. Per ulteriori dettagli sul funzionamento dello script OP_RETURN, ti consiglio di approfondire il suo utilizzo nella documentazione di Bitcoin.

   
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

Per utilizzare questo progetto, è necessario installare la libreria **ArduinoJson** tramite il **Library Manager** dell'Arduino IDE:

1. **Arduino IDE** > **Sketch** > **Include Library** > **Manage Libraries**
2. Cerca e installa la libreria **ArduinoJson**.

### Come Usare la Libreria uBitcoin con la Modifica al Network

Questo progetto utilizza una versione modificata della libreria **uBitcoin** a causa di un conflitto con l'oggetto omonimo `Network`, presente sia nelle librerie **Wifi.h** che in **uBitcoin.h**. Pertanto, è necessario includere correttamente la libreria modificata nell'IDE di Arduino.

1. **Clona o scarica il repository**:
   - Puoi clonare il repository tramite Git o scaricare il file ZIP direttamente dalla pagina del progetto su GitHub.

2. **Apri il progetto con l'IDE di Arduino**:
   - Una volta scaricato o clonato il repository, apri il file `.ino` nel tuo Arduino IDE.

3. **Aggiungi la libreria uBitcoin modificata**:
   - Vai su **Sketch** > **Include Library** > **Add .ZIP Library**.
   - Seleziona il file ZIP della libreria **uBitcoin** dalla cartella del progetto.

### Note:
- Assicurati di avere le librerie necessarie (come **ArduinoJson**) correttamente installate prima di iniziare.
- In caso di problemi con la libreria **uBitcoin**, controlla che la versione corretta (modificata) sia stata inclusa.
## :warning: ATTENZIONE :warning:

Per caricare il codice sull'ESP32, **è necessario tenere premuto il pulsante "BOOT"** per **tutta la durata del caricamento**.


