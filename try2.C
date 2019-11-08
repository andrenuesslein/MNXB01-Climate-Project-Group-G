#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TImage.h>


using namespace std;
using namespace cimg_library;

void canvasimage() {
//create a canvas with a picture (.png,.jpg,.gif, etc) in the background

CImg<unsigned char> image("se.svg");
  int width = image.width;
  int height = image.height;
  
TImage *img = TImage::Open("se.svg"); //put your own picture here
TCanvas *c1 = new TCanvas("c1", "c1", width, height);
img->Draw("x");

//Create a transparent pad filling the full canvas
TPad *p = new TPad("p","p",0,0,1,1);
p->SetFillStyle(4000);
p->SetFrameFillStyle(4000);
p->Draw();
p->cd();
TH1F *h = new TH1F("h","test",100,-3,3);
h->SetFillColor(kCyan);
h->FillRandom("gaus",5000);
h->Draw();
}
