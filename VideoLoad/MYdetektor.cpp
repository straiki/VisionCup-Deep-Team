#include "MYdetektor.h"
#include "MYdisplay.h"
#include "MYmaska.h"
#include "MYvideo.h"




MYdetektor::MYdetektor(IplImage * ctor)
{
    cout << "Nastaveni obrazku a klasifikatoru" << endl;
    this->MyFrame = ctor; // natahnuti obrazku
    this->_setHaars();

    Xakt.eye1 = {0,};
    Xakt.eye2 = {0,};
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
int FaceCounter = 0;
// Vytvoreni a naloadovani Klasifikatoru pro oblicej
CvHaarClassifierCascade* cascade = 0;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascFace, 0, 0, 0 );
// Vytvoreni pametoveho mista
CvMemStorage* storage = 0;
    storage = cvCreateMemStorage(0);
    cvClearMemStorage(storage);

    if( !cascade ){ // kontrola nacteni cascade
        cerr << "ERROR:  nenacten Klasifikator Obliceje" << endl;
        return -1;
    }

    //prochazim jednotlive vyrezy
        CvSeq* faces = cvHaarDetectObjects( this->MyFrame, cascade, storage,
                                            1.2, 4, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        for(int i = 0; i < faces->total ; i++){
           // cout << "Nasel facy" << endl;
            CvRect *face = (CvRect*)cvGetSeqElem(faces, i);

            cvSetImageROI(this->MyFrame,cvRect(face->x,face->y + (face->height/4.5), face->width,face->height/2.0));
            //cvSetImageROI(this->MyFrame,*face);

            if(FindEyes() > 0){// hledam oci v ramci ksichtu
                MYdisplay::ShowImage(MyFrame,'x');
                cvResetImageROI(this->MyFrame);
                //cvRectangle( this->MyFrame, cvPoint(face->x,face->y), cvPoint(face->x+face->width,face->y+face->height), CV_RGB(255,25,55), 2, 8, 0 );
                Xakt.rFace = *face;
                Xakt.eye1.x += Xakt.rFace.x;
                Xakt.eye1.y += Xakt.rFace.y + (face->height/4.5);
                Xakt.eye2.x += Xakt.rFace.x;
                Xakt.eye2.y += Xakt.rFace.y + (face->height/4.5);
                sX.push_back(Xakt);
            }
            else{
                cvResetImageROI(this->MyFrame);
            }

            FaceCounter++;
        }



    cvReleaseHaarClassifierCascade(&cascade);
    cvReleaseMemStorage(&storage);

    return FaceCounter; // vracim pocet nalezenych ksichtu (i s ocima)
}

int MYdetektor::FindEyes(){

int ZARAZ = 1;
int eyeCounter = 0;
CvHaarClassifierCascade * cascadeEye = 0;
    cascadeEye = (CvHaarClassifierCascade*)cvLoad( cascEyes, 0, 0, 0 );
CvMemStorage * storageEye = 0;
    storageEye = cvCreateMemStorage(0);
    cvClearMemStorage(storageEye);

    if(!cascadeEye){
        cerr << "ERROR:  nenacten Klasifikator Oci" << endl;
        return -1;
    }


    CvSeq* eyes = cvHaarDetectObjects( this->MyFrame, cascadeEye, storageEye,
                                        1.25, 4, 0,
                                        cvSize(35, 15) ); // 1.25 4.0

     for(int i = 0; i < (eyes ? eyes->total : 0); i++ )
        {
            CvRect* eye = (CvRect*)cvGetSeqElem(eyes, i);

            if(i == 0){
                Xakt.eye1 = *eye;
            }
            else{
//                if( _prusecik(*eye,Xakt.eye1) > 0){
//                    ZARAZ ++;
//                }
                Xakt.eye2 = *eye;
            }

            cvRectangle(this->MyFrame, cvPoint(eye->x,eye->y), cvPoint(eye->x+eye->width,eye->y+eye->height), CV_RGB(0,25,255), 2, 8, 0 );
            eyeCounter++;

            if(i == ZARAZ) {
                ZARAZ = 1;
                break; //! ochrana, pouze dve oci!
            }
        }

    cvReleaseHaarClassifierCascade(&cascadeEye);
    cvReleaseMemStorage(&storageEye);
    if( eyeCounter < 2) return 0; // pokud najdu mene nez jedno oko.
    return eyeCounter;
}


int MYdetektor::_prusecik(CvRect A, CvRect B){

    if(A.x >= B.x && A.x <= B.x + B.width) return 1;
    if(A.y >= B.y && A.y <= B.y + B.height) return 1;

    return 0;

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
//
//
//    if( xicht.prave_oko_x == 0){
//        xicht.prave_oko_x = stred.x;
//        xicht.prave_oko_y = stred.y;
//    }
//    else if( xicht.leve_oko_x == 0){
//        xicht.leve_oko_x = stred.x;
//        xicht.leve_oko_y = stred.y;
//    }
//
//
//
//    MYdisplay::DrawPoint(MyFrame,stred);

}

void MYdetektor::DrawSezOblic(){
    for(int i = 0; i < sX.size() ; i++){

        // Vykresleni Obliceje
        CvPoint h1 = cvPoint(sX.at(i).rFace.x,sX.at(i).rFace.y);
        CvPoint h2 = cvPoint(sX.at(i).rFace.x+sX.at(i).rFace.width,sX.at(i).rFace.y+sX.at(i).rFace.height);
    	cvRectangle(this->MyFrame,h1,h2,CV_RGB(255,25,60), 2, 8, 0);

    	//Vykresleni Oci
        h1 = cvPoint(sX.at(i).eye1.x,sX.at(i).eye1.y);
        h2 = cvPoint(sX.at(i).eye1.x+sX.at(i).eye1.width,sX.at(i).eye1.y+sX.at(i).eye1.height);
    	cvRectangle(this->MyFrame,h1,h2,CV_RGB(0,0,255), 2, 8, 0);

        h1 = cvPoint(sX.at(i).eye2.x,sX.at(i).eye2.y);
        h2 = cvPoint(sX.at(i).eye2.x+sX.at(i).eye2.width,sX.at(i).eye2.y+sX.at(i).eye2.height);
    	cvRectangle(this->MyFrame,h1,h2,CV_RGB(0,90,200), 2, 8, 0);
    }
    sX.clear(); // vymaz seznam
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

//    FindEyes(img2);
cvResetImageROI(MyFrame);
    MYdisplay::ShowImage(MyFrame,"aj");
MYdisplay::ShowImage(img2,'n');
//cvWaitKey();


}

