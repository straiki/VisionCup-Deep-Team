#include "MYdetektor.h"
#include "MYdisplay.h"
#include "MYmaska.h"
#include "MYvideo.h"




MYdetektor::MYdetektor(IplImage * ctor)
{
    cout << "Nastaveni obrazku a klasifikatoru" << endl;
    this->MyFrame = ctor; // natahnuti obrazku
    this->_setHaars();
}

MYdetektor::~MYdetektor()
{
    //dtot
}

void MYdetektor::_setHaars(){
    cascFace = "haarcascades/haarcascade_frontalface_alt.xml";
    cascEyes = "haarcascades/haarcascade_eye.xml";
    cascMouth = "haarcascades/haarcascade_mcs_mouth.xml";
}

void MYdetektor::setFrame(IplImage * setter){
    this->MyFrame = setter;
}


int MYdetektor::FindFaces(){
    // Create memory for calculations
static CvMemStorage* storage = 0;
// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;


    //cout << "Hledam Obliceje" << endl;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascFace, 0, 0, 0 );

    if( !cascade ){ // kontrola nacteni cascade
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }
    storage = cvCreateMemStorage(0); // vynulovani pametoveho uloziste
    int scale = 1; // skala, nejaky pomer zvetseni dejme tomu == zmensieni obrazku podil velikosti


    CvPoint pt1, pt2;
    CvPoint obl1,obl2;
    cvClearMemStorage( storage );
    //prochazim jednotlive vyrezy
        CvSeq* faces = cvHaarDetectObjects( this->MyFrame, cascade, storage,
                                            1.2, 4, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );
        for( int i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            obl1.x = r->x*scale;
            obl2.x = (r->x+r->width)*scale;
            obl1.y = r->y*scale;
            obl2.y = (r->y+r->height)*scale;

            cvSetImageROI( this->MyFrame,cvRect( obl1.x, obl1.y, r->width, r->height));

            MYoblicej::zeroesOblicej(&xicht);
            if (FindEyes(this->MyFrame) > 1){ // detekovany oblicej
                xicht.sour_x = obl1.x;
                xicht.sour_y = obl1.y;
                xicht.sirka = r->width;
                xicht.vyska = r->height;

                xicht.vypocti_klicove_body();
                sXichts.push_back(xicht);
               // FindMouth(this->MyFrame);
                cvResetImageROI(this->MyFrame);
                cvRectangle( this->MyFrame, obl1, obl2, CV_RGB(255,25,55), 2, 8, 0 );
                if(i >= 0) break;
            }
            cvResetImageROI(this->MyFrame);




        }

        cvClearMemStorage(storage);
    return sXichts.size(); // vraci pocet nalezenych obliceju

}

int MYdetektor::FindEyes(IplImage * imROI){

CvMemStorage* storageEye = 0;
CvHaarClassifierCascade* cascadeEye = 0;


   // cout << "Hledam Ocicka" << endl;
    cascadeEye = (CvHaarClassifierCascade*)cvLoad( cascEyes, 0, 0, 0 );

    if( !cascadeEye ){ // kontrola nacteni cascade
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }
    storageEye = cvCreateMemStorage(0); // vynulovani pametoveho uloziste
    int scale = 1; // skala, nejaky pomer zvetseni dejme tomu == zmensieni obrazku podil velikosti


    CvPoint pt1, pt2;
    int i;

    cvClearMemStorage( storageEye );
        CvSeq* eyes = cvHaarDetectObjects( imROI, cascadeEye, storageEye,
                                            1.25, 4, 0,
                                            cvSize(35, 15) );
//! dobre paramatry 1.15,4,0=CVHAAR,35,15
    if(eyes->total > 1){ // Pouze pro vice jak jedno Oci :)
        for( i = 0; i < (eyes ? eyes->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( eyes, i );
            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
                cvRectangle( imROI, pt1, pt2, CV_RGB(0,125,255), 2, 8, 0 );
                _findEyeCenter(pt1,pt2);

                if(i == 1) break;
        }
    }
cvClearMemStorage(storageEye);
return eyes->total;
}

int MYdetektor::FindMouth(IplImage * imROI){

static CvMemStorage* storageMouth = 0;
static CvHaarClassifierCascade* cascadeMouth = 0;


    cout << "Hledam Pusinku" << endl;
    cascadeMouth = (CvHaarClassifierCascade*)cvLoad( cascMouth, 0, 0, 0 );

    if( !cascadeMouth ){ // kontrola nacteni cascade
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }
    storageMouth = cvCreateMemStorage(0); // vynulovani pametoveho uloziste
    int scale = 1; // skala, nejaky pomer zvetseni dejme tomu == zmensieni obrazku podil velikosti


    CvPoint pt1, pt2;
    int i;

    cvClearMemStorage( storageMouth );
        CvSeq* mouth = cvHaarDetectObjects( imROI, cascadeMouth, storageMouth,
                                            1.15, 3, 0,
                                            cvSize(25, 10) );
//! dobre paramatry 1.15,4,0=CVHAAR,35,15
    if(mouth->total >= 1){ // Pouze pro vice jak jedno Oci :)
        for( i = 0; i < (mouth ? mouth->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( mouth, i );
            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;
                cvRectangle( imROI, pt1, pt2, CV_RGB(0,255,0), 2, 8, 0 );
                if(i==2)break;
        }
    }


return mouth->total;
}

CvPoint MYdetektor::_findEyeCenter(CvPoint a, CvPoint b){
    CvPoint stred = cvPoint(a.x + abs(a.x-b.x)/2, a.y + abs(a.y-b.y)/2);


    if( xicht.prave_oko_x == 0){
        xicht.prave_oko_x = stred.x;
        xicht.prave_oko_y = stred.y;
    }
    else if( xicht.leve_oko_x == 0){
        xicht.leve_oko_x = stred.x;
        xicht.leve_oko_y = stred.y;
    }



    MYdisplay::DrawPoint(MyFrame,stred);

}

void MYdetektor::DrawSezOblic(){



    for(int i = 0; i < sXichts.size() ; i++){
        MYmaska *maska;
        maska = new MYmaska();
        maska->vytvorKnirek(&sXichts.at(i));

        MYvideo::addMask(MyFrame,maska);
//    	cvRectangle( this->MyFrame, sezOblic.at(i).a, sezOblic.at(i).b, CV_RGB(255,125,0), 2, 8, 0 );
    	//MYdisplay::ShowImage(this->MyFrame,'n');
  //  	OrezPic(sezOblic.at(i).a,sezOblic.at(i).b);
        delete maska;
    }
    sXichts.clear();


}

void MYdetektor::OrezPic(CvPoint pt1, CvPoint pt2){
    cvSetImageROI(MyFrame,cvRect(pt1.x,pt1.y,abs(pt1.x-pt2.x),abs(pt1.y-pt2.y)));

    /* create destination image
   Note that cvGetSize will return the width and the height of ROI */
IplImage *img2 = cvCreateImage(cvGetSize(MyFrame),
                               MyFrame->depth,
                               MyFrame->nChannels);

/* copy subimage */
cvCopy(MyFrame, img2, NULL);

    FindEyes(img2);
cvResetImageROI(MyFrame);
    MYdisplay::ShowImage(MyFrame,"aj");
MYdisplay::ShowImage(img2,'n');
//cvWaitKey();


}

