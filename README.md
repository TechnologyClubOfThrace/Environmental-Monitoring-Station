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

[http://maps.luftdaten.info/](http://maps.luftdaten.info/ "http://maps.luftdaten.info/")
 Πληροφορίες για την κατασκευή του **Fine Dust Sensor** που αποστέλει δεδομένα για τον παραπάνω χάρτη υπάρχουν εδώ: [https://luftdaten.info/en/construction-manual/](https://luftdaten.info/en/construction-manual/ "https://luftdaten.info/en/construction-manual/")

[EPA AirData Air Quality Monitors](https://epa.maps.arcgis.com/apps/webappviewer/index.html?id=5f239fd3e72f424f98ef3d5def547eb5&extent=-146.2334,13.1913,-46.3896,56.5319 "EPA AirData Air Quality Monitors")
Δεδομένα που συλλέγονται από το [United Stated Environmental Protection Agency](https://www.epa.gov/outdoor-air-quality-data/interactive-map-air-quality-monitors "United Stated Environmental Protection Agency")


### Προμήθεια hardware
Οι παραγγελίες για το υλικό έχουν γινει απο τα παρακάτω σημεία: [Εκκρεμούν σύνδσοι και αισθητήρες]
ESP32:  
Αισθητήρας θερμοκρασίας 
