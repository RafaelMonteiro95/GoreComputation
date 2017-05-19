/* Transform source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

Transform::Transform(Vector3& position, Vector3& rotation, Vector3& scale){
	this.position = position;
	this.rotation = rotation;
	this.scale = scale;
}

Transform::~Transform(){

	delete this.position;
	delete this.rotation;
	delete this.scale;
}
