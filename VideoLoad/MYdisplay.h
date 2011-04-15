#ifndef MYDISPLAY_H
#define MYDISPLAY_H

#include <cv.h>
#include <highgui.h>

class MYdisplay
{
    public:
        MYdisplay();
        virtual ~MYdisplay();

        /**
          * Zobrazi obrazek v okne
          * volitelne parametry: jmeno okna, souradnice okna
          * @param image zobrazivsi obrazek
          * @param winName nazev okna obrazku - defaultne == "image"
          * @param x,y souradnice pro umisteni okna - defaultne 0,0
        */
        static char ShowImage(IplImage * image, const char * winName = "image", int x = 0, int y = 0);
        /**
          * Zobrazi obrazek v okne - s tim ze obrazek se zavre stisknutim klavesy cvKey
          * Pokud je cvKey == 0 - po jakekoliv klavese se okno zavre
          * Pokud je cvKey != 0 - zavre se okno po klavese cvKey
          * @return vraci vzdy hodnotu cvKey
          * volitelne parametry: jmeno okna, souradnice okna
          * @param image zobrazivsi obrazek
          * @param cvKey - klavesa pro ukonceni obrazku - 0 znamena jakakoliv
          * @param winName nazev okna obrazku - defaultne == "image"
          * @param x,y souradnice pro umisteni okna - defaultne 0,0
        */
        static char ShowImage(IplImage * image, char cvKey, const char * winName = "image",int x = 0, int y = 0);
        /**
          * Do obrazku vykresli bod - krizek s danymi parametry
          * @param image cilovy obrazek
          * @param P bod, ktery se vykresli
          * @param delka delka krizku pri vizualizaci bodu
          * @param tloustka tloustka cark krizku
          * @param barva krizku
        */
        static void DrawPoint(IplImage * image, CvPoint P, int delka = 3, int tloustka = 1,CvScalar barva = cvScalar(0,0,255));
    protected:
    private:
};

#endif // MYDISPLAY_H
