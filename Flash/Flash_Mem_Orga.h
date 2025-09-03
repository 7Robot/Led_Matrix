
#ifndef __FLASH_MEM_ORGA_H
#define __FLASH_MEM_ORGA_H


// flash pico = 32 secteurs

// flash pour le code standard : 4 premiers ser
#define FL_CODE_AREA_BLOCK  0
#define FL_CODE_AREA_LENGTH 4

#define FL_REPROG_CODE_BLOCK  4
#define FL_REPROG_CODE_LENGTH 4

// fichier setup en block 8
#define FL_SETUP_FILE_BLOCK 8

#define FL_LOGFILE_BLOCK        9         // secteur de d�but du fichier log        
#define FL_LOGFILE_LENGTH       23         // longeur max du fichier log pour ne pas rentrer dans le prochain truc


#endif


