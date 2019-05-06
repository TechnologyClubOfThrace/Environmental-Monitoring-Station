### Περιβαλλοντικός σταθμός επιτήρησης

Ο περιβαλλοντικός σταθμός επιτήρησης ειναι μια κατασκευή βασισμένη στο arduino και σε ανοιχτές τεχνολογίες με σκοπό την καταγραφή περιβαλλοντικών μετρήσεων, όπως ενδεικτικά, η ποιότητα του αέρα που αναπνέουμε, η καθαρότητα του νερού που πίνουμε, τα επίπεδα της ραδιενέργειας και η ηλεκτρομαγνητική ακτινοβολία.

Στην Ελλάδα πέρα απο κάποιες μετρήσεις για την ατμοσφαιρική ρύπανση που γίνονται κυρίως στην Αθήνα και την θεσσαλονίκη, δεν γνωρίζουμε σε πραγματικό χρόνο τι συμβαίνει στην ατμόσφαιρα.

![](https://github.com/TechnologyClubOfThrace/Environmental-Monitoring-Station/blob/master/environmental-monitoring-station.jpg)


### Το hardware
Η κατασκευή βασίζεται στο [ESP32-DevKitC](https://www.espressif.com/en/products/hardware/development-boards "ESP32-DevKitC") που εχει ενσωματωμένο WiFi ώστε να μπορούμε να αποστείλουμε τα δεδομένα στον [Thingboard IoT server](https://thingsboard.io/ "Thingboard IoT server").

###### Οι αισθητήρες που χρησιμοποιούνται ειναι:

    Αισθητήρας μικρόσωματιδίων MP 10 και MP 2.5
    Αισθητήρας αζώτου
    Αισθητήρας διοξειδίου του άνθρακα
    Αισθητήρας μονοξειδίου του άνθρακα
    Αισθητήρας UV ακτινοβολίας
    Αισθητήρας θερμοκρασίας
    Αισθητήρας υγρασίας
    Αισθητήρας ατμοσφαιρικής πίεσης 

Οταν θα εχει ολοκληρωθεί η σύνδεση των αισθητήρων θα δημοσιεύσουμε εδώ αναλυτικές οδηγίες σχετικά με τον τρόπο σύνδεσης στο ESP32 ώστε να μπορει οποίος θέλει να κατασκευάσει τον δικό του σταθμό και αν θέλει να στέλνει τα δεδομένα στον υπάρχον IoT server για να εχουμε μια ακομα καλύτερη εικόνα του περιβάλλοντος απο διάφορες περιοχές.


### Το software 
Ο κώδικας που τρέχει στο ESP32 βρίσκεται μέσα στο φάκελο [src/EnvironmentalMonitoringStation](https://github.com/TechnologyClubOfThrace/Environmental-Monitoring-Station/tree/master/src/EnvironmentalMonitoringStation "src/EnvironmentalMonitoringStation") και μπορείτε να τον ανοίξετε με το Arduino IDE.

Για να γινει compile θα πρεπει να εγκαταστήσετε αρχικά τους οδηγούς για το ESP32 και στη συνεχεια και όλα τα header files που θα σας εμφανίσει οτι λείπουν το Arduino IDE. Τα header files θα πρεπει να τα αντιγράψετε απο τον φάκελο arduino_libraries μέσα στο φάκελο libraries του Arduino IDE. Την τοπική διαδρομή στο μηχάνημα σας μπορείτε να την δείτε απο τα preferences του Arduino IDE.

Πέρα απο το λογισμικό που τρέχει μέσα στο ESP32, υπάρχει και το server side κομμάτι όπου συλλέγονται και παρουσιάζονται όλες οι μετρήσεις του σταθμού. Για τον σκοπό χρησιμοποιούμε το [Thingsboard](https://thingsboard.io/ "Thingsboard") το οποίο εχουμε εγκαταστήσει στον Debian GNU/Linux server του συλλόγου. 

#### Το dashboard όπου απεικονίζονται όλα τα δεδομένα που συλλέγονται είναι διαθέσιμο από [εδώ](http://chat.steth.gr:8080/dashboard/d9e7bd60-6f2f-11e9-97d0-1f977088dab9?publicId=ab4913f0-6f2f-11e9-97d0-1f977088dab9)


### Ατμοσφαιρική ρύπανση
Η ευρωπαϊκή επιτροπή εχει δημοσιεύσει αναλυτικά τα επιτρεπτά όρια σχετικά με την ατμοσφαιρική ρύπανση.
[EU Air Quality Standards](http://ec.europa.eu/environment/air/quality/standards.htm "EU Air Quality Standards")

United Stated Environmental Protection Agency - [NAAQS Table](https://www.epa.gov/criteria-air-pollutants/naaqs-table "NAAQS Table")

USA Labor Department - [Ποιότητα αέρα εσωτερικών χώρων](https://www.osha.gov/SLTC/indoorairquality/ "Ποιότητα αέρα εσωτερικών χώρων")


### Σταθμοί παρακολούθησης της ατμοσφαιρικής ρύπανσης σε όλο τον κόσμο
[European Air Quality Index](http://airindex.eea.europa.eu/ "European Air Quality Index")

[World's Air Pollution: Real-time Air Quality Index](https://waqi.info/ "World's Air Pollution: Real-time Air Quality Index")
Ο συγκερκιμένος οργανισμός εχει αναλάβει την κατασκευή σταθμών και τη συλλογή δεδομένων τους. [Εχει δημοσιεύσει και αρκετά στοιχεια](https://aqicn.org/sensor/ "Εχει δημοσιεύσει και αρκετά στοιχεια") σχετικά με τους αισθητήρες που χρηαιμοποιουνται. Κάποιους απο αυτούς τους αισθητήρες τους χρησιμοποιούμε και εμείς.

[https://opensensemap.org](https://opensensemap.org "https://opensensemap.org")
Ο συγκεκριμένος οργανισμός κατασκευάζει και τον περιβαλλοντικό σταθμό αισθητήρων **senseBox** και έχει δημοσιεύσει αναλυτικά τους αισθητήρες που χρησιμοποιεί εδώ: [https://www.sensebox.de/en/products](https://www.sensebox.de/en/products "https://www.sensebox.de/en/products")

[http://safecast.org/tilemap/](http://safecast.org/tilemap/ "http://safecast.org/tilemap/")
Ο [οργανισμός SafeCast](https://blog.safecast.org "οργανισμός SafeCast") δημιουργήθηκε από εθελοντές μετά το πυρηνικό ατύχημα στη Fucushima το 2011. Έχουν κατασκευάσει περιβαλλοντικούς σταθμούς καταγραφής  των επιπέδων της ραδιενέργειας και άλλων δεδομένων και έχουν ανεβάσει τα πάντα στο [github ώς open source και open hardware](https://github.com/Safecast "github ώς open source και open hardware").
Τα kit των συσκευών υπάρχουν εδώ: [https://github.com/Safecast/General/wiki/Safecast-Devices](https://github.com/Safecast/General/wiki/Safecast-Devices "https://github.com/Safecast/General/wiki/Safecast-Devices")

[http://maps.luftdaten.info/](http://maps.luftdaten.info/ "http://maps.luftdaten.info/")
 Πληροφορίες για την κατασκευή του **Fine Dust Sensor** που αποστέλει δεδομένα για τον παραπάνω χάρτη υπάρχουν εδώ: [https://luftdaten.info/en/construction-manual/](https://luftdaten.info/en/construction-manual/ "https://luftdaten.info/en/construction-manual/")

[EPA AirData Air Quality Monitors](https://epa.maps.arcgis.com/apps/webappviewer/index.html?id=5f239fd3e72f424f98ef3d5def547eb5&extent=-146.2334,13.1913,-46.3896,56.5319 "EPA AirData Air Quality Monitors")
Δεδομένα που συλλέγονται από το [United Stated Environmental Protection Agency](https://www.epa.gov/outdoor-air-quality-data/interactive-map-air-quality-monitors "United Stated Environmental Protection Agency")


### Προμήθεια hardware
Παρακάτω είναι οι δύο πίνακες με την αναλυτική περιγραφή του κόστους καθώς και σύνδεσμοι αγοράς για τους αισθητήρες και τα υλικά που χρειάζονται για την κατασκευή του σταθμού.

###### Πίνακας 1

|  Αισθητήρας | Μοντέλο | Arduino API | Κόστος | Αγορά από  |
| ------------ | ------------ | ------------ | ------------ | ------------ |
| Θερμοκρασίας  | DS18B20   | [ΝΑΙ - Library Manager](https://www.arduinolibraries.info/libraries/dallas-temperature)  |  3.50 | [eBay MAKERSHOP](https://www.ebay.com/itm/3x-DS18B20-Wasserdicht-Digital-Temperatur-Fuhler-Sensor-Raspberry-Pi-Arduino/253585471592?hash=item3b0adf3868:g:Wr8AAOSwxLdb3Zdt "eBay MAKERSHOP")  |
| Υγρασίας  | BME280  | [ΝΑΙ - Library Manager](https://www.arduinolibraries.info/libraries/bme280)  | 5.75  | [eBay MAKERSHOP](https://www.ebay.com/itm/BME280-Temperatur-Sensor-Luftdruck-Feuchtigkeit-I2C-5V-Barometer-Arduino-Digital/253107395109?hash=item3aee605a25:g:Ol8AAOSwHWtb3znL "eBay MAKERSHOP") |
| Ατμοσ. πίεσης  | BME280 | [ΝΑΙ - Library Manager](https://www.arduinolibraries.info/libraries/bme280) | 5.75 | [eBay MAKERSHOP](https://www.ebay.com/itm/BME280-Temperatur-Sensor-Luftdruck-Feuchtigkeit-I2C-5V-Barometer-Arduino-Digital/253107395109?hash=item3aee605a25:g:Ol8AAOSwHWtb3znL "eBay MAKERSHOP")  |
| Μικροσωματιδίων MP 10 + 2.5 |  PMS7003 | [ΝΑΙ - Github](https://github.com/fu-hsi/PMS) | 15.44 | [Aliexpress](https://www.aliexpress.com/item/PLANTOWER-Laser-PM2-5-DUST-SENSOR-PMS7003-G7-Thin-shape-Laser-digital-PM2-5-sensor-Inculd/32784279004.html?spm=2114.search0604.3.9.14ec3794G5sCkA&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=fab9744e-8fdf-46f4-a08f-b32e40ab44f8-1&algo_pvid=fab9744e-8fdf-46f4-a08f-b32e40ab44f8 "Aliexpress")  |
| Μονοξειδίου του άνθρακα | MQ-7 | [ΝΑΙ - Github - Χρειάζεται έλεγχος](https://github.com/swatish17/MQ7-Library) |  3.99 | [eBay MAKERSHOP](https://www.ebay.com/itm/MQ-7-Kohlenmonoxid-Sensor-CO-Gas-Sensor-Modul-Raspberry-Pi-Arduino/252715061610?hash=item3ad6fdd16a:g:OoIAAOSwUpFb4cC4 "eBay MAKERSHOP")  |
| Διοξειδίου του άνθρακα  |  MH-Z19 | [ΝΑΙ - Library Manager (2 βιβλιοθήκες)](https://www.arduinolibraries.info/libraries/mh-z19) |  18.14 | [Aliexpress](https://www.aliexpress.com/item/MH-Z19-infrared-co2-sensor-for-co2-monitor-carbon-dioxide-sensor-UART-PWM-serial-output-0/32916782044.html?spm=2114.search0604.3.2.131712c0k5jgr2&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=4933ca2c-6944-4ce4-a4d8-526522e070d7-0&algo_pvid=4933ca2c-6944-4ce4-a4d8-526522e070d7)  |
| Διοξειδίου του άνθρακα  |  MG811 with analog | [ΝΑΙ - Github - Θέλει δουλειά το calibration κλπ](https://sandboxelectronics.com/?p=147) |  25.70 | [Aliexpress](https://www.aliexpress.com/item/MG811-Carbon-Dioxide-Gas-CO2-Sensor-Module-Detector-With-Analog-Signal-Output-0-2V/32859295115.html?spm=2114.search0604.3.2.45c515873oy8F8&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=9a1ea977-22df-4c78-8b9a-8b2115acc860-0&algo_pvid=9a1ea977-22df-4c78-8b9a-8b2115acc860 "Aliexpress")  |
| Διοξειδίου του άνθρακα  |  MG811 | [ΝΑΙ - Github - Θέλει δουλειά το calibration κλπ](https://github.com/avkghost/MG811_sensor_library)  |  21.40 | [Aliexpress](https://www.aliexpress.com/item/wholesale-MG811-carbon-dioxide-sensor-CO2-sensor-gas-sensor-module-free-shipping/1160134439.html?spm=2114.search0604.3.9.45c515873oy8F8&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=9a1ea977-22df-4c78-8b9a-8b2115acc860-1&algo_pvid=9a1ea977-22df-4c78-8b9a-8b2115acc860 "Aliexpress") |
| Αζώτου  | MQ131 πλαστικό (low concentration of ozone)  | [ΝΑΙ - Github](https://github.com/ostaquet/Arduino-MQ131-driver) | 14.61 |  | [Aliexpress](https://www.aliexpress.com/item/MQ131-ozone-sensor-ozone-gas-detection-sensor-module-free-shipping/1159957338.html?spm=2114.search0604.3.2.742b79786EZfOC&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=4e1feea9-1857-43e6-8fb2-2302f84d31eb-0&algo_pvid=4e1feea9-1857-43e6-8fb2-2302f84d31eb "Aliexpress")  |
| Ραδιενέργειας |   | [ΝΑΙ - Θέλει δουλειά - Υπάρχει παράδειγμα κώδικα](https://rhelectronics.net/store/radiation-detector-geiger-counter-diy-kit-second-edition.html)  | 38.23  | [eBay](https://www.ebay.com/itm/DIY-Nuclear-Radiation-Detector-GM-Assembled-Geiger-Counter-Kit-AHS/303029621778?hash=item468df91412:m:m8ONIcW9PE1UFVKfkgYXmHQ "eBay")|
| Ραδιενέργειας |   | [ΝΑΙ - Θέλει δουλειά - Υπάρχει παράδειγμα κώδικα](https://rhelectronics.net/store/radiation-detector-geiger-counter-diy-kit-second-edition.html) | 38.23  | [Aliexpress](https://www.ebay.com/itm/DIY-Nuclear-Radiation-Detector-GM-Assembled-Geiger-Counter-Kit-AHS/303029621778?hash=item468df91412:m:m8ONIcW9PE1UFVKfkgYXmHQ "Aliexpress")|
| Ηχορύπανση | digital  | Ψηφιακό μάλον δεν μας κάνει | 1.95 | [eBay MAKERSHOP](https://www.ebay.com/itm/Gerauschsensor-Mikrofon-Sound-Sensor-Modul-Raspberry-Pi-Arduino-Lautstarke/252748930718?hash=item3ad9029e9e:g:2dUAAOSwqRlb4cCg "eBay MAKERSHOP") |
| Ηχορύπανση | analog+digital | Χρήση analogRead | 2.90 | [eBay MAKERSHOP](https://www.ebay.com/itm/Analog-Sound-Sensor-Gerauschsensor-Sensor-Mikrofon-Modul-Arduino-Raspberry-Pi/252909274219?hash=item3ae291446b:g:pvcAAOSw2-pb4H2j "eBay MAKERSHOP") |
| Ηχορύπανση | MAX9814 | ? | 5.25 | [eBay MAKERSHOP](https://www.ebay.com/itm/MAX9814-Sound-Sensor-Gerauschsensor-Mikrofon-Microphone-Module-Arduino-Raspbe/253890621317?hash=item3b1d0f6f85:g:Y1UAAOSwdrdb6kFF "eBay MAKERSHOP") |


- Για τον αισθητήρα θερμοκρασίας υπάρχουν αναφορές για μή ακριβείς μετρήσεις του BME280 λόγω θέρμανσης του αισθητήρα. Αντί αυτού θα χρησιμοποιήσουμε τον αδιάβροχο DS18B20 γιατί χρειάζεται να βρίσκεται και έξω από το κουτί, εκτεθειμένος. Ο αισθητήρας θερμοκρασίας του BME280 θα χρησιμοποιείται ώς εφεδρικός.

- Για τον αισθητήρα ηχορύπανσης να διαλέξουμε ένα από τους τρείς

- Να προσέξουμε ώστε να υπάρχουν βιβλιοθήκες για την λήψη των μετρήσεων από τους αισθητήρες που θα επιλέξουμε

- Ο αισθητήρας CO2 MH-Z19 πιθανότατα είναι καλύτερος από τον MG811. Το API του έχει τη δυνατότητα αυτόματου calibration,  είναι φθηνότερος, υποστηρίζει το πρωτόκολλο UART, είναι ποιό σταθεροποιημένος και έχει 2 βιβλιοθήκες έτοιμες προς χρήση στον library manager του arduino IDE.

- Για τον κώδικα που απαιτείται για λήψη δεδομένων απο το geiger counter, ίσως είναι καλύτερα να δούμε τί έχουν υλοποιήσει στον σταθμό του safecast.org 

- Κάποιοι από τους αισθητήρες θέλουν έρευνα για να καταλάβουμε πώς λειτουργούν και πώς μπορούμε να πάρουμε ακριβείς μετρήσεις, καθώς δεν συνοδεύνται απο API. Για αυτό τον λόγο θα πρέπει να έχουμε ένα πρόχειρο arduino device ώστε να κάνουμε έλεγχο ένα-ένα αυτους αισθητήρες μέχρι να γράψουμε τον σωστό κώδικα. Στη συνέχεια μπορούμε να δημιουργήσουμε ένα library και να το προσφέρουμε και στην κοινότητα των arduino developers.

###### Πίνακας 2

| Υλικό  | Περιγραφή  | Κόστος  | Αγορά από  |
| ------------ | ------------ | ------------ | ------------ |
| ESP32  | Ο μικροελεγκτής όπου συνδέονται όλα   | 8.35  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Espressif-ESP32-WLAN-Dev-Kit-Board-Development-Bluetooth-Wifi-v1-WROOM32-NodeMCU/253059783728?hash=item3aeb89dc30:g:5-8AAOSwAThb3MaZ "eBay MAKERSHOP")  |
| Jumper wire male-female  |   | 2.49  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Jumper-Wire-Steckbrucken-Steckbrett-Kabel-20p-male-female-mannlich-weiblich/252715145677?hash=item3ad6ff19cd:m:mz_Na6LfgzHzHslqexs0NfQ&var=551695342124 "eBay MAKERSHOP") |
| Jumper wire male-male  |   | 2.49  |   |
| Breadboard 400 | Για τη σύνδεση του ESP32 και των αισθητήρων  | 3.85  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Premium-Steckbrett-400-Kontakte-Breadboard-Transparent-durchsichtig-transparent/252715004864?hash=item3ad6fcf3c0:g:E5wAAOSwXOhb5H0n "eBay MAKERSHOP") |
| Breadboard 830  | Για τη σύνδεση του ESP32 και των αισθητήρων  |  3.75 |  [eBay MAKERHSOP](https://www.ebay.com/itm/MB-102-830-Kontakte-Breadboard-gros-Steckbrett-Raspberry-Pi-Experimentier/252860727462?hash=item3adfac80a6:g:wC4AAOSwn01b3zoN "eBay MAKERHSOP") |

Σύμφωνα με τα παραπάνω, το συνολικό κόστος για την κατασκευή ενός περιβαλλοντικού σταθμού είναι περίπου 130€

Για την αρχική υλοποίηση αρκούν τα υλικά του παρακάτω πίνακα 3, κυρίως λόγω του ότι το API είναι σχετικά εύκολο στην υλοποίηση και μας αρκούν για την περιβαλλοντική παρατήρηση. Στη συνέχεια μπορούμε να παραγγείλουμε και τους άλλους αισθητήρες οι οποίει θα κάνουν τον σταθμό ακόμα καλύτερο αλλά και που αυξάνουν και την πολυπλοκότητα του κώδικα.

###### Πίνακας 3

| Υλικό  | Περιγραφή  | Κόστος  | Αγορά από  |
| ------------ | ------------ | ------------ | ------------ |
| ESP32  | Ο μικροελεγκτής όπου συνδέονται όλα   | 8.35  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Espressif-ESP32-WLAN-Dev-Kit-Board-Development-Bluetooth-Wifi-v1-WROOM32-NodeMCU/253059783728?hash=item3aeb89dc30:g:5-8AAOSwAThb3MaZ "eBay MAKERSHOP")  |
| Jumper wire male-female  | Καλώδια σύνδεσης | 2.49  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Jumper-Wire-Steckbrucken-Steckbrett-Kabel-20p-male-female-mannlich-weiblich/252715145677?hash=item3ad6ff19cd:m:mz_Na6LfgzHzHslqexs0NfQ&var=551695342124 "eBay MAKERSHOP") |
| Jumper wire male-male  |  Καλώδια σύνδεσης | 2.49  |   |
| Breadboard 400 | Για τη σύνδεση του ESP32 και των αισθητήρων  | 3.85  |  [eBay MAKERSHOP](https://www.ebay.com/itm/Premium-Steckbrett-400-Kontakte-Breadboard-Transparent-durchsichtig-transparent/252715004864?hash=item3ad6fcf3c0:g:E5wAAOSwXOhb5H0n "eBay MAKERSHOP") |
| Breadboard 830  | Για τη σύνδεση του ESP32 και των αισθητήρων  |  3.75 |  [eBay MAKERHSOP](https://www.ebay.com/itm/MB-102-830-Kontakte-Breadboard-gros-Steckbrett-Raspberry-Pi-Experimentier/252860727462?hash=item3adfac80a6:g:wC4AAOSwn01b3zoN "eBay MAKERHSOP") |
| DS18B20 | Αισθητήρας Θερμοκρασίας | 3.50 | [eBay MAKERSHOP](https://www.ebay.com/itm/3x-DS18B20-Wasserdicht-Digital-Temperatur-Fuhler-Sensor-Raspberry-Pi-Arduino/253585471592?hash=item3b0adf3868:g:Wr8AAOSwxLdb3Zdt "eBay MAKERSHOP") |
| BME280 | Αισθητήρας Υγρασίας / Ατμοσ. πίεσης | 5.75 | [eBay MAKERSHOP](https://www.ebay.com/itm/BME280-Temperatur-Sensor-Luftdruck-Feuchtigkeit-I2C-5V-Barometer-Arduino-Digital/253107395109?hash=item3aee605a25:g:Ol8AAOSwHWtb3znL "eBay MAKERSHOP") |
| PMS7003 | Αισθητήρας Μικροσωματιδίων MP2.5/10 | 15.44 | [Aliexpress](https://www.aliexpress.com/item/PLANTOWER-Laser-PM2-5-DUST-SENSOR-PMS7003-G7-Thin-shape-Laser-digital-PM2-5-sensor-Inculd/32784279004.html?spm=2114.search0604.3.9.14ec3794G5sCkA&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=fab9744e-8fdf-46f4-a08f-b32e40ab44f8-1&algo_pvid=fab9744e-8fdf-46f4-a08f-b32e40ab44f8 "Aliexpress")  |
| MQ-7 | Αισθητήρας Μονοξειδίου του άνθρακα | 3.99 | [eBay MAKERSHOP](https://www.ebay.com/itm/MQ-7-Kohlenmonoxid-Sensor-CO-Gas-Sensor-Modul-Raspberry-Pi-Arduino/252715061610?hash=item3ad6fdd16a:g:OoIAAOSwUpFb4cC4 "eBay MAKERSHOP") |
| MH-Z19 | Αισθητήρας Διοξειδίου του άνθρακα | 18.14 | [Aliexpress](https://www.aliexpress.com/item/MH-Z19-infrared-co2-sensor-for-co2-monitor-carbon-dioxide-sensor-UART-PWM-serial-output-0/32916782044.html?spm=2114.search0604.3.2.131712c0k5jgr2&ws_ab_test=searchweb0_0,searchweb201602_6_10065_10068_319_10059_10884_317_10887_10696_321_322_10084_453_10083_454_10103_10618_10304_10307_10820_10821_537_10302_536,searchweb201603_52,ppcSwitch_0&algo_expid=4933ca2c-6944-4ce4-a4d8-526522e070d7-0&algo_pvid=4933ca2c-6944-4ce4-a4d8-526522e070d7) |
|  | Αισθητήρας Ηχορύπανσης | 2.90 | [eBay MAKERSHOP](https://www.ebay.com/itm/Analog-Sound-Sensor-Gerauschsensor-Sensor-Mikrofon-Modul-Arduino-Raspberry-Pi/252909274219?hash=item3ae291446b:g:pvcAAOSw2-pb4H2j "eBay MAKERSHOP") |
|  | Συνολικό κόστος:  | 70.65 |  |
