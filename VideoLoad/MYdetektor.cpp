#include "MYdetektor.h"
#include "MYdisplay.h"
MYdetektor::MYdetektor(IplImage * ctor)
{
    this->MyFrame = ctor; // natahnuti obrazku
}

MYdetektor::~MYdetektor()
{
    //dtor
}

void MYdetektor::setFrame(IplImage * setter){
    this->MyFrame = setter;
}


// Create memory for calculations
static CvMemStorage* storage = 0;

// Create a new Haar classifier
static CvHaarClassifierCascade* cascade = 0;

// Create a string that contains the cascade name
const char* cascade_name =
    "/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
/*    "haarcascade_profileface.xml";*/


int MYdetektor::DrawFaces(){
    cout << "Hledam ksich" << endl;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    // Check whether the cascade has loaded successfully. Else report and error and quit
    if( !cascade )
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return -1;
    }

    storage = cvCreateMemStorage(0);

    int scale = 1;

    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(this->MyFrame->width/scale,this->MyFrame->height/scale), 8, 3 );

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
            // Draw the rectangle in the input image
            //cvRectangle( this->MyFrame, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );


        }
    }

    // Show the image in the window named "result"


    // Release the temp image created.
    cvReleaseImage( &temp );

}

void MYdetektor::DrawSezOblic(){
    for(int i = 0; i < sezOblic.size() ; i++){
    	cvRectangle( this->MyFrame, sezOblic.at(i).a, sezOblic.at(i).b, CV_RGB(255,125,0), 2, 8, 0 );
    	MYdisplay::ShowImage(this->MyFrame,'n');
    }

}

