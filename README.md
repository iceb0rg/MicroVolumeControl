# MicroVolumeControl
# 🎚️ Arduino + Linux Serial Volume Controller

Tento projekt umožňuje ovládat systémovou hlasitost v Linuxu pomocí **Arduino zařízení**.  
Arduino čte hodnoty z potenciometru nebo senzoru, posílá je po **USB sériovém portu** do počítače, a Python skript následně upravuje hlasitost pomocí **PulseAudio**.  
Součástí je i **mute tlačítko** s LED indikací.

---

## 📂 Struktura projektu
├── arduino/volume_controller.ino # Arduino kód
├── linux/volume_controller.py # Python skript pro Linux
└── README.md # Dokumentace


---

## ⚙️ Arduino část

### ✨ Funkce
- Čtení hodnot z **potenciometru** na pinu A0
- Vyhlazení signálu pomocí klouzavého průměru
- Přemapování hodnot (0–1023) → (0–100)
- Tlačítko (pin 2) pro **mute/unmute**
- LED (pin 9) signalizující stav mute
- Odesílání hodnot přes **Serial (115200 baud)**

### 🔌 Zapojení
- **A0** → střed potenciometru
- **GND / 5V** → krajní piny potenciometru
- **D2** → tlačítko (INPUT_PULLUP)
- **D9** → LED (+ rezistor)

### 🚀 Použití
Nahraj `arduino/volume_controller.ino` na Arduino (např. Uno, Leonardo, Micro).

---

## 🐧 Linux část

### 📋 Požadavky
- Linux s **PulseAudio**
- Python 3.x
- Balíčky:
```bash
pip install pulsectl pyserial

