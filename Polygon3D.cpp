#include "Polygon3D.h"

Polygon3D::Polygon3D(){
}

Polygon3D::Polygon3D(string filename){
	ifstream inputStream;
	inputStream.open(fileName.c_str());
	int numberOfComponent;
	inputStream >> numberOfComponent;
	while(numberOfComponent) {
		char typeOfComponent;
		inputStream >> typeOfComponent;
		if (typeOfComponent == '/') {
			string dummy;
			getline(inputStream,dummy);
			continue;
		}
		else if (typeOfComponent == 'L') {
			int x1,y1,x2,y2,red,green,blue;
			inputStream>>x1>>y1>>x2>>y2>>red>>green>>blue;
			Point beginPoint(x1,y1),endPoint(x2,y2);
			Color color(red,green,blue,0);
			this->add(new Line(beginPoint,endPoint,color));
		} else {
			printf("Unknown type of component in file %s: %c\n",fileName.c_str(),typeOfComponent);
		}
		numberOfComponent--;
	}
	inputStream.close();
}

void Polygon3D::add(Line3D* line){
	lines.push_back(*line);	
}

void Polygon3D::clear(){
	(lines).clear();
}

vector<Pixel> Polygon3D::getPixels() const{
	
}

//TBD
void rotate(int angle,int x0,int y0){
	printf("Polygon3D doesn't support rotate");
}

#endif
