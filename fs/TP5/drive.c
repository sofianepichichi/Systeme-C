#include <stdio.h>
#include <stdlib.h>
#include "drive.h"
#include<string.h>





//fonction pour deplcer dans la téte  de secteur
void seek(unsigned int cyl,unsigned int sec){
  _out(HDA_DATAREG,(cyl >> 8) & 0xFF);
  _out(HDA_DATAREG+1,cyl & 0xFF);
  _out(HDA_DATAREG+2,(sec >> 8) & 0xFF);
  _out(HDA_DATAREG+3,sec & 0xFF);
  _out(HDA_CMDREG,CMD_SEEK);
  _sleep(HDA_IRQ);
}




// fonction pour formater
void format(unsigned int cyl, unsigned int sec, unsigned int nbsec, unsigned nbcyl){
   seek(cyl,sec);
  _out(HDA_DATAREG,(nsec >> 8) & 0xFF);
  _out(HDA_DATAREG+1,nsec & 0xFF);
  _out(HDA_DATAREG,(cyl >>8) & 0xFF);
  _out(HDA_DATAREG+1,1);
  _out(HDA_DATAREG+2,(val >>24) & 0xFF);
  _out(HDA_DATAREG+3),
  _out(HDA_DATAREG+4),(val >> 8) &0xFF);
  _out(HDA_CMDREG,CMD_FRMT);

  for(unsigned int j=0;j<nsec;j++){
      _sleep(HDA_IRQ);
}

}
