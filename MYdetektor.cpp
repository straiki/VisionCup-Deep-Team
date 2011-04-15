#include "MYdetektor.h"
#include "MYdisplay.h"
MYdetektor::MYdetektor(IplImage * ctor)
{
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
    cout << "Hledam Obliceje" << endl;
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

        // Loop the number of faces found.
        for( int i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            obl1.x = r->x*scale;
            obl2.x = (r->x+r->width)*scale;
            obl1.y = r->y*scale;
            obl2.y = (r->y+r->height)*scale;
            // Nasteveni ROI
          //  MYdisplay::ShowImage(MyFrame,'q');
            cvSetImageROI( this->MyFrame,cvRect( obl1.x, obl1.y + r->height, r->width, r->height));

MYdisplay::ShowImage(MyFrame,'q');

             CvSeq* eyes = cvHaarDetectObjects( this->MyFrame, cascade, storage,
                                            1.15, 3, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(25, 15) );
            if(eyes->total > 0){
                cout << "mam ocicka "<< eyes->total << endl;
                for( int j = 0; j < (eyes ? eyes->total : 0); j++ )
                    {
                       // Create a new rectangle for drawing the face
                        CvRect* e = (CvRect*)cvGetSeqElem( eyes, j );

                        // Find the dimensions of the face,and scale it if necessary
                        pt1.x = e->x*scale;
                        pt2.x = (e->x+e->width)*scale;
                        pt1.y = e->y*scale;
                        pt2.y = (e->y+e->height)*scale;
                            cvRectangle( this->MyFrame, pt1, pt2, CV_RGB(0,125,255), 2, 8, 0 );
                    }

                xicht oblicej;
                    oblicej.a = obl1;
                    oblicej.b = obl2;

                    sezOblic.push_back(oblicej);
            }
            cvResetImageROI(this->MyFrame);
        }
MYdisplay::ShowImage(MyFrame,'q');
    return sezOblic.size(); // vraci pocet nalezenych obliceju

}

int MYdetektor::FindEyes(IplImage * imROI){
    cout << "Hledam Ocicka" << endl;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascEyes, 0, 0, 0 );

    if( !cascade ){ // kontrola nacteni cascade
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }
    storage = cvCreateMemStorage(0); // vynulovani pametoveho uloziste
    int scale = 1; // skala, nejaky pomer zvetseni dejme tomu == zmensieni obrazku podil velikosti


    CvPoint pt1, pt2;
    int i;

    cvClearMemStorage( storage );

    //prochazim jednotlive vyrezy


        CvSeq* eyes = cvHaarDetectObjects( imROI, cascade, storage,
                                            1.15, 3, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(25, 15) );

        // Loop the number of faces found.
        for( i = 0; i < (eyes ? eyes->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( eyes, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

//            xicht oblicej;
//                oblicej.a = pt1;
//                oblicej.b = pt2;
//
//                sezOblic.push_back(oblicej);

                cvRectangle( imROI, pt1, pt2, CV_RGB(0,125,255), 2, 8, 0 );
        }

    return sezOblic.size(); // vraci pocet nalezenych obliceju


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

