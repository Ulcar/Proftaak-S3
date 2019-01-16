# Wash&Go
## Proftaak Semester 3 Technology

Hieronder worden de verschillende programma's in dit project uitgelegd.




## Server

Deze is te vinden in de map [Server/Mainserver](Server/Mainserver).

### Beschrijving

Deze code is te compileren met het bijgeleverde Makefile en in gesschreven in C++.
De Server is **het** belangrijkste onderdeel van dit project. 
Hierin worden alle logica afgehandeld met betrekking tot verbindingen, berichten en bijhouden van statussen.

### StartUp

Bij de startup zullen er 4 threads aangemaakt worden deze threads hebben ieder hun eigen taak die hieronder uitgelegd worden.
Verder zal de server zich binden aan het vooraf ingestelde ip-adres met poort.

### Uitleg

#### Thread 1: consoleThread

In deze thread wordt de terminal afgehandeld. Dit komt omdat het uilezen van de terminal blocking code is.
Als er een commando uitgelezen wordt handeld deze thread ook het uitvoeren hiervan uit.

#### Thread 2: SocketThread

In deze thread wordt het verzenden en ontvangen van berichten op de sockets afgehandeld. 
De ingelezen berichten worden in een buffer gezet zodat een andere thread deze uit kan lezen.
De te verzenden berichten leest hij uit een andere buffer waar andere threads berichten in gezet hebben.

Op het moment dat er een nieuwe verbinding binnenkomt handeld deze thread het aanmaken van de benodigde data af binnen de server.

#### Thread 3: protoclThread

Deze thread handelt alle logica binnen de server af. Hij leeft namelijk de binnengekomen berichten uit de buffers en handeld deze af, maar ook houd deze bij waar welke was is en start programma's op Clients als deze vol zitten.

#### Thread 4: main

Deze thread wordt als eerste standaard opgestart en beheert ook alle gemaakte data.
Bij het afsluiten zorgt deze thread er ook voor dat alles netjes afgesloten wordt.

#### Logger

De server bevalt een geavanceerd logging-systeem. Dit systeem houd naugezet bij welke acties er gebeuren en slaat deze ook op in een file.
Het loggen gebeurd op twee verschillende niveaus, Error en Debug. 
Standaard wordt elke message die wordt opgeslagen uitgeprint in de terminal, maar dit is heel makkelijk uit te zetten.

### Commandos

Hieronder een lijst met de beschikbare commando's die de server begrijpt.
Als er meerdere commando's op een regel staan zijn is dat een alias voor de eerste.

| commando | Subcommando | alias | Parameters | Beschrijving |
|--------|------|------|------------|------------|
| `quit` | | `exit`, `q` | | Stop de Server |
| `ping` | | `p` | | Pong |
| `clear` | | `clr`, `c` | | Maakt het scherm leeg |
| `errorlogger`| | `el` | | Laat alle subcommando's zien |
| `errorlogger`| `display` | `d`| | Laat de 20 laatste Error-berichten zien |
| `errorlogger`| `save` | `s` | | Sla het alle Error-berichten op als bestand |
| `errorlogger`| `live` | `l` | | Toggle het live schrijven van Error messages in de terminal |
| `debuglogger`| | `dl` | | Laat alle subcommando's zien |
| `debuglogger`| `display` | `d`| | Laat de 20 laatste Debug-berichten zien |
| `debuglogger`| `save` | `s` | | Sla het alle Debug-berichten op als bestand |
| `debuglogger`| `live` | `l` | | Toggle het live schrijven van Debug messages in de terminal |
| `debuglogger`| `heartbeat` | `hb` | | Toggle het live schrijven van de verzonden en ontvangen HeartBeats in de terminal |
| `laundry`| | `l` | | Laat alle subcommando's zien |
| `laundry`| `add` | `a`| `<kg> <temperature> <color> <list machines>` | Voeg niewe was toe aan de server |
| `laundry`| `remove` | `r`| `<ID>` | Verwijder bepaalde was uit de server |
| `laundry`| `display` | `d`| | Laat alle was zien die zich in het systeem bevind |






## ControlPanel

Deze is te vinden in de map [Interface/Server_Interface](Interface/Server_Interface).

### Beschrijving

Deze code is te compileren met Visual Studio en in gesschreven in C#.
De keuze voor C# is omdat het in C++ erg mogelijk om een mooite GUI te maken.
Het Controlpanel is **DE** grafische omgeving van de server om alle data te zien en aan te passen op afstand.

#### Startup

Na het opstarten wordt je om een ip-adres gevraagt in combinatie met een poort.
Na het invullen wordt gekeken of dit een geldige verbinding is, zo niet wordt je opnieuw om een ip-adres en poort gevraagt.
Als deze gegevens wel valide zijn verbind het Control panel met de server.

### Overzicht

Als je ingelogd bent zie je de onderstaande elementen op het scherm.
Een toolbar bovenin, een Client gedeelte linksboven, een Laundry gedeelte linksonder en een console gedeelte rechts.

#### Toolbar

In de toolbar staan een paar handige dingen. Aan de linkerkant is het huidige Water en Powerverbruik te zien.
Aan de rechterkant staat een drietal knoppen.
* De Reload-knop herlaad alle gegevens van de Clients
* De Disable All-knop schakelt alle Clients in 1x uit
* De Disconnect-knop disconnect het Control panel van de server.

#### Client overzicht

In dit gedeelte is te zien welke Clients zijn verbonden met de server.
Als je meer informatie wilt over een Client druk je op deze in de lijst.
Als je het wilt is het mogelijk om een enkele Client uit te schakelen of weer in te schakelen.

#### Laundry overzicht

Hier is het mogelijk om een nieuwe was toe te voegen.
Je moet hiervoor wel een gewicht invullen, een kleur en een temperatuur selecteren en tot slot aangeven door welke machines de was heen moet.

#### Console

Het laatste onderdeel is de console, hierin kan je servercommando's uitvoeren en krijg je ook de feedback van de server te zien in de output.
Een lijst met beschikbare commando's is te zien onder het kopje **Server**.





## Client

Deze is te vinden in de map [Clients](clients).

### Benodigdheden

De volgende onderdelen zijn benodigd om de code van de client te kunnen compileren:

- [Arduino IDE](https://www.arduino.cc/en/main/software)
- [Google Test](https://github.com/google/googletest)

In de Arduino IDE dienen ook de volgende libraries geïnstalleerd te worden:

- SD (versie `1.2.3`)
- SPI (versie `1.0.0`)
- WiFi (versie `1.2.7`)
- Wire (versie `1.0.0`)
- ArduinoJson (versie `5.13.4`)
- ArduinoSTL (versie `1.1.0`)
- Centipede

Een aantal van deze libraries zijn standaard al geïnstalleerd tijdens de installatie van de Arduino IDE.

### Project Structuur

De code van de client is opgesplitst in drie delen:

- **includes/**  
  Deze map bevat alle header bestanden (`*.h`), welke weer zijn opgesplitst in drie delen.
  - **client/**  
    Deze map bevat alle header bestanden met betrekking tot de communicatie met de server.
  - **hardware/**  
    Deze map bevat alle header bestanden met betrekking tot de hardware abstraction layer (ofwel HAL).
  - **program/**  
    Deze map bevat alle header bestanden met betrekking tot het beheren van de wasprogramma's.
- **tests/**
  Deze map bevat alle bestanden van de unit tests, welke gebruik maken van [Google Test](https://github.com/google/googletest).
- **/**  
  Deze map bevat alle source bestanden (`*.ino`) en de Makefile om de unit tests te compileren.

### Wasprogramma

De wasprogramma's zijn gedefinieerd als JSON programma's, welke gebruik maken van de volgende structuur:

```json
{
  "program": 0,
  "actions": [
    {
      "action": 7,
      "args": {
        "direction": 0,
        "speed": 1
      }
    },
    {
      "action": 8,
      "args": {
        "ms": 5000
      }
    }
  ]
}
```

Deze bestanden moeten in het volgende formaat worden opgeslagen op de SD kaart: `PROG0002.TXT`, waarbij de laatste 4 cijfers naar wens aangepast kunnen worden.

#### Acties

De volgende acties kunnen gedefinieerd worden in het wasprogramma:

| Nummer | Naam | Parameters |
|--------|------|------------|
| 0 | Soap | **state**: 0 (aan) of 1 (uit); **dispenser**: 0 of 1 |
| 1 | Buzzer | **state**: 0 (aan) of 1 (uit) |
| 2 | Drain Water | _n.v.t._ |
| 3 | Heat | **temp**: 0 (uit), 1 (low), 2 (medium) of 3 (high) |
| 4 | Fill Water | **level**: 0 (leeg), 1 (25%), 2 (50%) of 3 (vol) |
| 5 | Request Power | **power**: 0 - ∞ |
| 6 | Request Water | **liters**: 0 - ∞ |
| 7 | Motor Rotate | **direction**: 0 (links) of 1 (rechts); **speed**: 0 (uit), 1 (low), 2 (medium) of 3 (high) |
| 8 | Delay | **ms**: 0 - ∞ |

### Bekende fouten

Er zitten nog een aantal (kleine) foutjes in de code van de client, deze staan hieronder benoemd.

- **Wi-Fi herverbinden**  
  Wanneer de connectie met de server of het netwerk wegvalt is het de bedoeling dat de Arduino automatisch weer opnieuw probeert te verbinden met het netwerk of de server. Momenteel lukt dit niet altijd, en blijft de Arduino in een infinite loop hangen.
- **SD kaart laadt niet altijd**  
  De wasprogramma's zijn gedefinieerd als JSON bestanden op een SD kaart. Echter, de SD kaart lezer in Arduino verwacht het SD kaartje om in een bepaalde filesysteem te zijn, dit krijgen we echter niet altijd goed waardoor de wasprogramma's niet worden geladen. Hiervoor hebben we momenteel de wasprogramma's hardcoded in de code gezet.

### To Do

We willen graag nog een __watchdog__ toevoegen, die kan merken wanneer of de Arduino of de wasmachine vastloopt zodat deze automatisch herstart kan worden.





## Test_Interfaces

Deze is te vinden in de map [Test_Interfaces](Test_Interfaces).

### Beschrijving

Deze code is te compileren met het bijgeleverde Makefile en in gesschreven in C++.
Met de Test-Interfaces is het mogelijk om de Server en Clients af te testen en ook foutberichten te kunnen versturen.

### Client Acties

Hieronder staan de acties van het menu dat je te zien krijgt als je de testClient opstart.
Waar '`x`' staat wordt je om een variabele gevraagt.

| Nummer | Naam | Parameters |
|--------|------|------------|
| 1 | Connect | Verbind met MACadres `x` |
| 2 | Disconnect | Sluit de verbinding |
| 3 | Request water | Vraagt `x` L water aan |
| 4 | Stop water | Stopt met water |
| 5 | Request Power | Vraagt `x` V power aan |
| 6 | Stop Power | Stopt met power |
| 7 | Program done | Verzend dat hij klaar is met het programma |
| 8 | Response | Accepteer of Deny aangewezen programma |

### Server Acties

Leest berichten uit en hier kan je op antwoorden.

_End Of File_