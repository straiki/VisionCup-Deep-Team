#include "MYdetektor.h"
#include "MYdisplay.h"
MYdetektor::MYdetektor(IplImage * ctor)
{
    cout << "Nastaveni obrazku a klasifikatoru" << endl;
    this->MyFrame = ctor; // natahnuti obrazku
    this->_setHaars();
}

MYdetektor::~MYdetektor()
{
    //dtor
}

void MYdetektor::_setHaars(){
    cascFace = "haarcascades/haarcascade_frontalface_alt.xml";
    cascEyes = "haarcascades/haarcascade_eye.xml";
}

void MYdetektor::setFrame(IplImage * setter){
    this->MyFrame = setter;
}

// Create memory for calculations
static CvMemStorage* storage = 0;
// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

int MYdetektor::FindFaces(){
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
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
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

            if (FindEyes(this->MyFrame) > 1){
                cvResetImageROI(this->MyFrame);
                cvRectangle( this->MyFrame, obl1, obl2, CV_RGB(255,25,55), 2, 8, 0 );
//                MYdisplay::ShowImage(MyFrame,'q');
            }
            else{
                cvResetImageROI(this->MyFrame);
            }

        }
    return sezOblic.size(); // vraci pocet nalezenych obliceju

}

int MYdetektor::FindEyes(IplImage * imROI){

static CvMemStorage* storageEye = 0;
static CvHaarClassifierCascade* cascadeEye = 0;


    cout << "Hledam Ocicka" << endl;
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

return eyes->total;
}

CvPoint MYdetektor::_findEyeCenter(CvPoint a, CvPoint b){
    CvPoint stred = cvPoint(a.x + abs(a.x-b.x)/2, a.y + abs(a.y-b.y)/2);
    MYdisplay::DrawPoint(MyFrame,stred);

}

int MYdetektor::DrawFaces(){
    cout << "Hledam ksich" << endl;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascEyes, 0, 0, 0 );
    // Check whether the cascade has loaded successfully. Else report and error and quit


    storage = cvCreateMemStorage(0);

    int scale = 1;

    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(this->MyFrame->width/scale,this->MyFrame->height/scale), IPL_DEPTH_32F, 3 );

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( this->MyFrame, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            xicht oblicej;
                oblicej.a = pt1;
                oblicej.b = pt2;

                sezOblic.push_back(oblicej);
        }
    }
    // Release the temp image created.
    MYdisplay::ShowImage(temp,"wind");
    cvReleaseImage( &temp );


}

void MYdetektor::DrawSezOblic(){

    for(int i = 0; i < sezOblic.size() ; i++){
    	cvRectangle( this->MyFrame, sezOblic.at(i).a, sezOblic.at(i).b, CV_RGB(255,125,0), 2, 8, 0 );
    	//MYdisplay::ShowImage(this->MyFrame,'n');
    	OrezPic(sezOblic.at(i).a,sezOblic.at(i).b);
    }

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

