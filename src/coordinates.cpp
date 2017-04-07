/* Coordinates functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/
Coordinates::Coordinates() { 
	this.x = 0;
	this.y = 0;
}

Coordinates::Coordinates(int x, int y) {
	this.x = x;
	this.y = y;
}

Coordinates& operator=(Coordinates& c){
	this.x = c.x;
	this.y = c.y;
}
