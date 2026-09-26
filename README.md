# ☁️ Cloudy Weather Station

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Build%20Passed-orange?logo=platformio)](https://platformio.org/)
[![ESP32-C3](https://img.shields.io/badge/ESP32--C3-Lolin%20C3%20Mini-blue?logo=espressif)](https://www.espressif.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

**Cloudy Weather Station** est une station météo connectée et moniteur de qualité de l'air compact, autonome et moderne basé sur un microcontrôleur **ESP32-C3**.

Elle surveille en continu la température, l'humidité et les polluants intérieurs (AQI, TVOC, eCO₂), fournit un retour visuel en temps réel grâce à un ruban de LEDs RGB adressables (WS2812B), pilote un ventilateur PWM pour le renouvellement de l'air et embarque un serveur Web dynamique complet sans stockage externe.

---

## ✨ Fonctionnalités

- 🌡️ **Mesures environnementales précises** :
  - **AHT21** : Température (°C), humidité relative (%) et calcul automatique du point de rosée.
  - **ENS160** : Indice de qualité de l'air (AQI 1 à 5), composés organiques volatils totaux (TVOC en ppb) et dioxyde de carbone équivalent (eCO₂ en ppm).
- 🌈 **Indicateur lumineux intelligent (FastLED)** :
  - Animation douce en dégradé sur ruban **WS2812B**.
  - La couleur globale s'adapte automatiquement à l'indice AQI (Bleu $\rightarrow$ Vert $\rightarrow$ Jaune $\rightarrow$ Orange $\rightarrow$ Rouge).
  - Codes d'erreur lumineux en cas de coupure WiFi ou de problème capteur.
- 💨 **Contrôle PWM du ventilateur** :
  - 5 vitesses réglables : *Off, Très bas, Bas, Moyen, Haut*.
  - Ajustement direct et réactif via l'interface Web.
- 🌐 **Serveur Web embarqué (AsyncWebServer)** :
  - Interface Web moderne, sombre (*dark mode* avec fond réactif à la qualité de l'air).
  - Horloge temps réel synchronisée et mise à jour périodique des mesures via API JSON (`/data`).
  - Aucun système de fichiers (SPIFFS/LittleFS) requis : l'interface HTML/CSS/JS est servie directement par le firmware.
- 📈 **Télémétrie ThingSpeak (Optionnel)** :
  - Envoi automatique des mesures sur votre canal ThingSpeak.
  - Affichage direct des graphiques dans l'interface Web locale si les clés sont renseignées.
- 🔄 **Mise à jour sans fil (Arduino OTA)** :
  - Mise à jour du microprogramme par WiFi via mDNS (`cloudy-station.local`).

---

## 🛠️ Matériel Requis

| Composant | Description |
| :--- | :--- |
| **Microcontrôleur** | Wemos / Lolin C3 Mini (ESP32-C3 RISC-V, 4MB Flash) |
| **Capteur Temp/Hum** | AHT20 / AHT21 (I2C) |
| **Capteur Qualité d'Air** | ScioSense ENS160 (I2C) |
| **Éclairage** | Ruban LED adressable WS2812B (11 LEDs par défaut) |
| **Ventilation** | Ventilateur 5V avec commande PWM (ou via transistor / MOSFET adapté) |
| **Alimentation** | 5V USB-C |

---

## 🔌 Câblage & Broches (Pinout)

| Périphérique | Broche ESP32-C3 | Description |
| :--- | :--- | :--- |
| **I2C SDA** | `GPIO 3` | Ligne de données partagée (AHT21 + ENS160) |
| **I2C SCL** | `GPIO 4` | Horloge partagée (AHT21 + ENS160) |
| **LED Strip Data** | `GPIO 1` | Entrée signal DIN du ruban WS2812B |
| **Fan PWM** | `GPIO 10` | Signal PWM de commande du ventilateur |
| **Alimentation** | `5V` / `3.3V` / `GND` | Selon les spécifications de vos modules |

> ℹ️ *Les résistances de pull-up I2C sont généralement déjà intégrées sur les modules de capteurs du commerce.*

---

## 🚀 Installation & Démarrage

### 1. Prérequis
- [Visual Studio Code](https://code.visualstudio.com/) avec l'extension [PlatformIO IDE](https://platformio.org/).

### 2. Cloner le projet
```bash
git clone https://github.com/votre-nom/cloudy-weather-station-public.git
cd cloudy-weather-station-public
```

### 3. Configurer vos identifiants
Ouvrez le fichier [`include/credentials.h`](include/credentials.h) et complétez vos paramètres :

```cpp
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// --- Configuration WiFi ---
#define WIFI_SSID "Mon_Reseau_WiFi"
#define WIFI_PASSWORD "Mon_Mot_De_Passe"

// --- Configuration ThingSpeak (laisser vide si non utilisé) ---
#define THINGSPEAK_KEY "VOTRE_CLE_API_ECRITURE"
#define THINGSPEAK_CHANNEL "VOTRE_NUMERO_DE_CANAL"

#endif
```

> 💡 *Si vous n'utilisez pas ThingSpeak, laissez les chaînes vides `""`. Le serveur Web local et toutes les fonctionnalités de la station fonctionneront parfaitement en local.*

### 4. Compilation & Téléversement

#### Premier téléversement (USB) :
Branchez la carte en USB à votre ordinateur.
Si `upload_protocol = espota` est activé dans `platformio.ini`, vous pouvez forcer le téléversement par câble USB :
```bash
pio run -t upload --upload-port COMx   # Remplacez COMx par votre port USB/Série (ex: /dev/ttyUSB0 sous Linux)
```
Ou commentez temporairement les lignes OTA dans `platformio.ini` lors du tout premier flash.

#### Téléversements suivants (OTA sans fil) :
Une fois connecté à votre réseau WiFi :
```bash
pio run -t upload
```
Le téléversement se fera directement en WiFi vers `cloudy-station.local`.

---

## 💻 Utilisation

1. À la mise sous tension, la station initialise les capteurs et se connecte au réseau WiFi.
2. Ouvrez le moniteur série (vitesse `115200 bauds`) pour visualiser l'adresse IP attribuée.
3. Depuis n'importe quel appareil connecté au même réseau WiFi, accédez à :
   ```
   http://<ADRESSE_IP_DE_LA_STATION>
   ou
   http://cloudy-station.local
   ```
4. **Navigation dans l'interface** :
   - **Onglet Monitoring** : Lecture instantanée de la température, humidité, AQI, TVOC, eCO₂ et statut de la station.
   - **Onglet Ventilateur** : Curseur interactif pour régler la puissance de ventilation en temps réel.

---

## 🚨 Diagnostics & Codes d'Erreur LED

En cas d'anomalie, le ruban LED pulse dans une couleur caractéristique pour identifier le problème :

| Couleur LED | Signification | Solution |
| :--- | :--- | :--- |
| **Magenta pulsé** | Échec de connexion au réseau WiFi | Vérifier le SSID et mot de passe dans `credentials.h`. |
| **Rouge pulsé** | Échec d'initialisation des capteurs (I2C) | Vérifier le câblage SDA/SCL et l'alimentation des capteurs. |
| **Orange-Rouge pulsé** | Délai dépassé lors de la lecture des capteurs | Vérifier la stabilité des connexions I2C. |

---

## 📁 Structure du Projet

```text
cloudy-weather-station-public/
├── include/
│   ├── connectivity.h     # Gestion du WiFi, serveur Web et ThingSpeak
│   ├── credentials.h      # Identifiants WiFi et clés d'API (non renseignés)
│   ├── fan.h              # Pilote du ventilateur PWM
│   ├── led.h              # Gestion des animations et couleurs FastLED
│   └── sensor.h           # Pilote I2C des capteurs AHT21 et ENS160
├── src/
│   ├── connectivity.cpp
│   ├── fan.cpp
│   ├── led.cpp
│   ├── main.cpp           # Boucle principale (Setup / Loop)
│   └── sensor.cpp
├── partitions_custom.csv  # Table de partition ESP32 adaptée pour OTA
├── platformio.ini         # Configuration PlatformIO et bibliothèques
├── LICENSE                # Licence MIT
└── README.md              # Documentation du projet
```

---

## 📜 Licence

Ce projet est sous licence MIT — Développé par **Ypsol**.  
Consultez le fichier [LICENSE](LICENSE) pour plus d'informations.
