
String user = "Tren"; //CHANGE THIS AFTER PULLING
//String user = "Arham";
//String user = "Omar";
//String user = "Audrey";

/* Changes color sensor config and device adress for each team member.

*/
void userConfig() {

  if (user == "Tren") {


    double rt[] = {852, 755, 814, 0, 0, 0};
    double blt[] = {757, 700, 863, 0, 0, 0};
    double gt[] = {844, 634, 858, 0, 0, 0};
    double brt[] = {853, 754, 858, 0, 0, 0};
    double yet[] = {831, 523, 739, 0, 0, 0};
    double orat[] = {845, 735, 751, 0, 0, 0};
    double emptyt[] = {852, 766, 860, 0, 0, 0};
    double wheelt[] = {0, 0, 0, 0, 0, 0};

    int lightError = 50;

    deviceAddress = 0;

    memcpy(rv, rt, 6);
    memcpy(blv, blt, 6);
    memcpy(gv, gt, 6);
    memcpy(brv, brt, 6);
    memcpy(yev, yet, 6);
    memcpy(orv, orat, 6);
    memcpy(emptyv, emptyt, 6);
    memcpy(wheelv, wheelt, 6);

  } else if (user == "Arham") {


    double rt[] = {852, 755, 814, 0, 0, 0};
    double blt[] = {757, 700, 863, 0, 0, 0};
    double gt[] = {844, 634, 858, 0, 0, 0};
    double brt[] = {853, 754, 858, 0, 0, 0};
    double yet[] = {831, 523, 739, 0, 0, 0};
    double orat[] = {845, 735, 751, 0, 0, 0};
    double emptyt[] = {852, 766, 860, 0, 0, 0};
    double wheelt[] = {0, 0, 0, 0, 0, 0};

    int lightError = 50;

    deviceAddress = 1;

    memcpy(rv, rt, 6);
    memcpy(blv, blt, 6);
    memcpy(gv, gt, 6);
    memcpy(brv, brt, 6);
    memcpy(yev, yet, 6);
    memcpy(orv, orat, 6);
    memcpy(emptyv, emptyt, 6);
    memcpy(wheelv, wheelt, 6);


  } else if (user == "Audrey") {

    double rt[] = {852, 755, 814, 0, 0, 0};
    double blt[] = {757, 700, 863, 0, 0, 0};
    double gt[] = {844, 634, 858, 0, 0, 0};
    double brt[] = {853, 754, 858, 0, 0, 0};
    double yet[] = {831, 523, 739, 0, 0, 0};
    double orat[] = {845, 735, 751, 0, 0, 0};
    double emptyt[] = {852, 766, 860, 0, 0, 0};
    double wheelt[] = {0, 0, 0, 0, 0, 0};

    int lightError = 50;

    deviceAddress = 2;

    memcpy(rv, rt, 6);
    memcpy(blv, blt, 6);
    memcpy(gv, gt, 6);
    memcpy(brv, brt, 6);
    memcpy(yev, yet, 6);
    memcpy(orv, orat, 6);
    memcpy(emptyv, emptyt, 6);
    memcpy(wheelv, wheelt, 6);


  } else if (user == "Omar") {


    double rt[] = {852, 755, 814, 0, 0, 0};
    double blt[] = {757, 700, 863, 0, 0, 0};
    double gt[] = {844, 634, 858, 0, 0, 0};
    double brt[] = {853, 754, 858, 0, 0, 0};
    double yet[] = {831, 523, 739, 0, 0, 0};
    double orat[] = {845, 735, 751, 0, 0, 0};
    double emptyt[] = {852, 766, 860, 0, 0, 0};
    double wheelt[] = {0, 0, 0, 0, 0, 0};

    int lightError = 50;

    deviceAddress = 3;

    memcpy(rv, rt, 6);
    memcpy(blv, blt, 6);
    memcpy(gv, gt, 6);
    memcpy(brv, brt, 6);
    memcpy(yev, yet, 6);
    memcpy(orv, orat, 6);
    memcpy(emptyv, emptyt, 6);
    memcpy(wheelv, wheelt, 6);

  }

}
