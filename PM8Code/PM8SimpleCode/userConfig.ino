
String user = "Tren"; //CHANGE THIS AFTER PULLING

/* Changes color sensor config and device adress for each team member.

*/
void userConfig() {

  if (user == "Tren") {


    double rt[] = {852, 755, 814};
    double blt[] = {757, 700, 863};
    double gt[] = {844, 634, 858};
    double brt[] = {853, 754, 858};
    double yet[] = {831, 523, 739};
    double orat[] = {845, 735, 751};
    double emptyt[] = {852, 766, 860};
    double wheelt[] = {0, 0, 0};

    deviceAddress = 0;

    memcpy(r, rt, 3);
    memcpy(bl, blt, 3);
    memcpy(g, gt, 3);
    memcpy(br, brt, 3);
    memcpy(ye, yet, 3);
    memcpy(ora, orat, 3);
    memcpy(empty, emptyt, 3);
    memcpy(wheel, wheelt, 3);

  } else if (user == "Arham") {


    double rt[] = {852, 755, 814};
    double blt[] = {757, 700, 863};
    double gt[] = {844, 634, 858};
    double brt[] = {853, 754, 858};
    double yet[] = {831, 523, 739};
    double orat[] = {845, 735, 751};
    double emptyt[] = {852, 766, 860};
    double wheelt[] = {0, 0, 0};

    deviceAddress = 1;

    memcpy(r, rt, 3);
    memcpy(bl, blt, 3);
    memcpy(g, gt, 3);
    memcpy(br, brt, 3);
    memcpy(ye, yet, 3);
    memcpy(ora, orat, 3);
    memcpy(empty, emptyt, 3);
    memcpy(wheel, wheelt, 3);


  } else if (user == "Audrey") {

    double rt[] = {852, 755, 814}; 
    double blt[] = {757, 700, 863}; 
    double gt[] = {844, 634, 858}; 
    double brt[] = {853, 754, 858}; 
    double yet[] = {831, 523, 739}; 
    double orat[] = {845, 735, 751}; 
    double emptyt[] = {852, 766, 860}; 
    double wheelt[] = {0,0,0};

    deviceAddress = 2;

    memcpy(r, rt, 3);
    memcpy(bl, blt, 3);
    memcpy(g, gt, 3);
    memcpy(br, brt, 3);
    memcpy(ye, yet, 3);
    memcpy(ora, orat, 3);
    memcpy(empty, emptyt, 3);
    memcpy(wheel, wheelt, 3);


  } else if (user == "Omar") {


    double rt[] = {852, 755, 814}; 
    double blt[] = {757, 700, 863}; 
    double gt[] = {844, 634, 858}; 
    double brt[] = {853, 754, 858}; 
    double yet[] = {831, 523, 739}; 
    double orat[] = {845, 735, 751}; 
    double emptyt[] = {852, 766, 860}; 
    double wheelt[] = {0,0,0};

    deviceAddress = 3;

    memcpy(r, rt, 3);
    memcpy(bl, blt, 3);
    memcpy(g, gt, 3);
    memcpy(br, brt, 3);
    memcpy(ye, yet, 3);
    memcpy(ora, orat, 3);
    memcpy(empty, emptyt, 3);
    memcpy(wheel, wheelt, 3);

  }

}
