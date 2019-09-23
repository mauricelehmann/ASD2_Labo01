#include "GraphFromImage.h"
using namespace std;

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {

}

// throws std::out_of_range
GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {

	Iterable listAdj;
	//Coordonee x,y de v (idx)
	int _x,_y,_adjx,_adjy;
	//check si les coordonnées x,y sont valides
	try{
		_x = x(v);
		_y = y(v);
	}catch(out_of_range& e){
		throw e;
	}
	//check pixel du haut
	_adjx = _x;
	_adjy = _y - 1;
	//Controle si on ne dépasse pas le bord du haut
	if(_adjy >= 0){
		//On controle les couleurs
		if(compareColor(_x,_y,_adjx,_adjy)){
			listAdj.push_front(idx(_adjx,_adjy));
		}
	}
	//check pixel du bas
	_adjy = _y + 1;
	//Controle si on ne dépasse pas le bord du bas
	if(_adjy < image.height()){
		//On controle les couleurs
		if(compareColor(_x,_y,_adjx,_adjy)){
			listAdj.push_front(idx(_adjx,_adjy));
		}
	}
	//check pixel de gauche
	_adjx = _x - 1;
	_adjy = _y;
	//Controle si on ne dépasse pas le bord de gauche
	if(_adjx >= 0){
		//On controle les couleurs
		if(compareColor(_x,_y,_adjx,_adjy)){
			listAdj.push_front(idx(_adjx,_adjy));
		}
	}
	//check pixel de droite
	_adjx = _x + 1;
	//Controle si on ne dépasse pas le bord de droite
	if(_adjx < image.width()){
		//On controle les couleurs
		if(compareColor(_x,_y,_adjx,_adjy)){
			listAdj.push_front(idx(_adjx,_adjy));
		}
	}

	return listAdj;
}

// throws std::out_of_range
int GraphFromImage::idx(int x, int y) const {

	if(x > image.width() ||
	   y > image.height()||
	   x < 0 ||
	   y < 0
    ){
		throw out_of_range("Coordonee x,y invalide!");
	}
	return (y * image.width()) + x ;

}

// throws std::out_of_range
int GraphFromImage::x(int idx) const {
	if(!checkRange(idx)){
		throw out_of_range("Coordonee idx invalide!");
	}
	return idx % image.width();
}

// throws std::out_of_range
int GraphFromImage::y(int idx) const {
	if(!checkRange(idx)){
		throw out_of_range("Coordonee idx invalide!");
	}
    return idx / image.width();
}

int GraphFromImage::V() const {
	return image.pixel_count();
}

bool GraphFromImage::checkRange(int idx) const {
	if(idx > V() || idx < 0){
		return false;
	}
	return true;
}
bool GraphFromImage::compareColor(int x,int y,int adjx,int adjy) const{

	unsigned char red,green,blue, adjRed,adjGreen,adjBlue;
 	//On récupère la couleur du pixel (x,y)
	image.get_pixel(x,y,red,green,blue);
	//On récupère la couleur du pixel adjacent
	image.get_pixel(adjx,adjy,adjRed,adjGreen,adjBlue);
	if(adjRed == red && adjGreen == green && adjBlue == blue){
		return true;
	}
	return false;
}
