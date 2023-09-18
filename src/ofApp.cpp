#include "ofApp.h"

void ofApp::onBtn1Pressed()
{
	std::cout << "boton 1 \n";
	appstate = EAppState::pelotas;
	setupPelotas();
}

void ofApp::onBtn2Pressed()
{
	std::cout << "boton 2 \n";
	appstate = EAppState::lemmings;
	setupLemmings();
}

void ofApp::setup()
{
	//establecer el primer estado de la app
	appstate = EAppState::menu;

	titleFont.load("press.ttf", 24);
	uiFont.load("press.ttf", 12);

	mainmenu.setup();
	mainmenu.add(btnEjercicio1.setup("Pelotas rebotando"));
	mainmenu.add(btnEjercicio2.setup("Tipo Lemmings"));
	mainmenu.setPosition(ofGetWidth() / 2 - mainmenu.getWidth() / 2,
							ofGetHeight() / 2 - mainmenu.getHeight() / 2);
	btnEjercicio1.addListener(this, &ofApp::onBtn1Pressed );
	btnEjercicio2.addListener(this, &ofApp::onBtn2Pressed );
}

void ofApp::setupPelotas()
{
	Entity e = Entity();
	e.position->x = 100;
	e.position->y = 100;
	e.velocity->x = 10;
	gameObjects.push_back(e);
	Entity e2 = Entity();
	e2.position->x = 150;
	e2.position->y = 150;
	gameObjects.push_back(e2);

	e2.velocity->x = 10;

	std::cout << gameObjects.size() << "\n";

	imgHogar.load("casa.png");
}

void ofApp::setupLemmings()
{
	posx = 0;
	posy = 0;
	radioCirculo = 20;
	//cargar spritesheet
	playerSpriteImg.load("spritesheet.png");
	//tamaño del jugador
	playerSize = ofVec2f(28, 42);
	playerSpriteOffset = ofVec2f(2, 4);

	//items
	srand(time(NULL));
	item1x = rand() % 1140 + 100;
	item1y = rand() % 800 + 100;
	espada.load("espada.png");
	item1Size = ofVec2f(32, 48);
	item1Offset = ofVec2f(2, 4);

	item2x = rand() % 1140 + 100;
	item2y = rand() % 800 + 100;
	veneno.load("veneno.png");
	item2Size = ofVec2f(32, 40);
	item2Offset = ofVec2f(2, 4);

	item3x = rand() % 1140 + 100;
	item3y = rand() % 800 + 100;
	bomba.load("bomba.png");
	item3Size = ofVec2f(30, 28);
	item3Offset = ofVec2f(2, 4);

	item4x = rand() % 1140 + 100;
	item4y = rand() % 800 + 100;
	pistola.load("pistola.png");
	item4Size = ofVec2f(32, 25);
	item4Offset = ofVec2f(2, 4);

	//inventory
	Entity hands = Entity();
	hands.name = "MANOS";
	inventory.push_back(hands);

	inventoryIterator = inventory.begin(); //inicializar le iterador
	//currItem = &inventory.back();  //back obtiene el ultimo item
	std::cout << "begin: " << (*inventoryIterator).name << "\n";
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (appstate == EAppState::pelotas)
	{
		updatePelotas();
	}
	else if (appstate == EAppState::menu)
	{
		
	}
	else if (appstate == EAppState::lemmings)
	{
		updateLemmings();
	}
}

void ofApp::updatePelotas()
{
	//mover les entidades
	for (int i = 0; i < gameObjects.size(); i++)
	{

		//aplicar la aceleracion de la gravedad en el espacio
		gameObjects[i].velocity->y += gravity * ofGetLastFrameTime();


		//colision y rebote con el piso
		if (gameObjects[i].position->y >= ofGetHeight())
		{
			gameObjects[i].position->y = ofGetHeight();
			gameObjects[i].velocity->y *= -0.9;

		}

		//aplicar la velocidad como posicion
		gameObjects[i].position->x += gameObjects[i].velocity->x * ofGetLastFrameTime();
		gameObjects[i].position->y += gameObjects[i].velocity->y * ofGetLastFrameTime();
	}
}

void ofApp::updateLemmings()
{
	//mover el sprite dependiendo de los inputs
	if (w)
	{
		posy -= 100 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(2, 52);
		
	}
	if (s)
	{
		posy += 100 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(2, 4);
	}
	if (a)
	{
		posx -= 100 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(2, 100);
	}
	if (d)
	{
		posx += 100 * ofGetLastFrameTime();
		playerSpriteOffset = ofVec2f(34, 148);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (appstate == EAppState::pelotas)
	{
		ofBackground(ofColor::cornflowerBlue);
		//dibujar los objetos del fondo como la casa
		imgHogar.draw(200, ofGetHeight() - imgHogar.getHeight());

		ofSetColor(240, 12, 12);

		if (gameObjects.size() > 0)
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].draw();
				color.push_back(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
				gameObjects[i].setColor(color[i]);
			}
		}
	}
	else if (appstate == EAppState::menu)
	{
		ofBackground(ofColor::darkGray);
		mainmenu.draw();
	}
	else if (appstate == EAppState::lemmings)
	{
		Entity spada = Entity();
		spada.name = "ESPADA";
		Entity veneno1 = Entity();
		veneno1.name = "VENENO";
		Entity bomba1 = Entity();
		bomba1.name = "BOMBA";
		Entity pistola1 = Entity();
		pistola1.name = "PISTOLA";

		ofBackground(ofColor::lightGray);
		ofSetColor(2, 2, 1);
		titleFont.drawString("std::list inventory example", 100, 100);

		ofSetColor(255, 255, 255);
		playerSpriteImg.drawSubsection(posx, posy, 
			playerSize.x, playerSize.y,
			playerSpriteOffset.x, playerSpriteOffset.y);

		espada.drawSubsection(item1x, item1y, item1Size.x, item1Size.y, item1Offset.x, item1Offset.y);
		veneno.drawSubsection(item2x, item2y, item2Size.x, item2Size.y, item2Offset.x, item2Offset.y);
		bomba.drawSubsection(item3x, item3y, item3Size.x, item3Size.y, item3Offset.x, item3Offset.y);
		pistola.drawSubsection(item4x, item4y, item4Size.x, item4Size.y, item4Offset.x, item4Offset.y);
		//poner el nombre del item actual
		ofSetColor(255, 255, 0);

		//uiFont.drawString( currItem==nullptr?"NULL":currItem->name.c_str(), posx, posy);
		uiFont.drawString( (*inventoryIterator).name.c_str(), posx, posy);

		//Colisiones
		if (!onHand)
		{
			if (posx + limit > item1x && posx + limit < item1x && posy + limit > item1y && posy - limit < item1y + limit) {
				onHand = true;
				inventory.push_back(spada);
				item1x = 10000;
				item1y = 10000;
			}
			if (posx - limit < item1x + limit && posx - limit > item1x + limit && posy + limit > item1y && posy - limit < item1y + limit) {
				onHand = true;
				inventory.push_back(spada);
				item1x = 10000;
				item1y = 10000;
			}
			if (posy + limit > item1y && posy + limit < item1y + limit && posx + limit > item1x && posx - limit < item1x++ + limit) {
				onHand = true;
				inventory.push_back(spada);
				item1x = 10000;
				item1y = 10000;
			}
			if (posy - limit < item1y + limit && posy - limit > item1y + limit && posx + limit > item1x && posx - limit < item1x + limit) {
				onHand = true;
				inventory.push_back(spada);
				item1x = 10000;
				item1y = 10000;
			}
		}

		if (!onHand2)
		{
			if (posx + limit > item2x && posx + limit < item2x && posy + limit > item2y && posy - limit < item2y + limit) {
				onHand2 = true;
				inventory.push_back(veneno1);
				item2x = 10000;
				item2y = 10000;
			}
			if (posx - limit < item2x + limit && posx - limit > item2x + limit && posy + limit > item2y && posy - limit < item2y + limit) {
				onHand2 = true;
				inventory.push_back(veneno1);
				item2x = 10000;
				item2y = 10000;
			}
			if (posy + limit > item2y && posy + limit < item2y + limit && posx + limit > item2x && posx - limit < item2x++ + limit) {
				onHand2 = true;
				inventory.push_back(veneno1);
				item2x = 10000;
				item2y = 10000;
			}
			if (posy - limit < item2y + limit && posy - limit > item2y + limit && posx + limit > item2x && posx - limit < item2x + limit) {
				onHand2 = true;
				inventory.push_back(veneno1);
				item2x = 10000;
				item2y = 10000;
			}
		}

		if (!onHand3)
		{
			if (posx + limit > item3x && posx + limit < item3x && posy + limit > item3y && posy - limit < item3y + limit) {
				onHand3 = true;
				inventory.push_back(bomba1);
				item3x = 10000;
				item3y = 10000;
			}
			if (posx - limit < item3x + limit && posx - limit > item3x + limit && posy + limit > item3y && posy - limit < item3y + limit) {
				onHand3 = true;
				inventory.push_back(bomba1);
				item3x = 10000;
				item3y = 10000;
			}
			if (posy + limit > item3y && posy + limit < item3y + limit && posx + limit > item3x && posx - limit < item3x++ + limit) {
				onHand3 = true;
				inventory.push_back(bomba1);
				item3x = 10000;
				item3y = 10000;
			}
			if (posy - limit < item3y + limit && posy - limit > item3y + limit && posx + limit > item3x && posx - limit < item3x + limit) {
				onHand3 = true;
				inventory.push_back(bomba1);
				item3x = 10000;
				item3y = 10000;
			}
		}

		if (!onHand4)
		{

			if (posx + limit > item4x && posx + limit < item4x && posy + limit > item4y && posy - limit < item4y + limit) {
				onHand4 = true;
				inventory.push_back(pistola1);
				item4x = 10000;
				item4y = 10000;
			}
			if (posx - limit < item4x + limit && posx - limit > item4x + limit && posy + limit > item4y && posy - limit < item4y + limit) {
				onHand4 = true;
				inventory.push_back(pistola1);
				item4x = 10000;
				item4y = 10000;
			}
			if (posy + limit > item4y && posy + limit < item4y + limit && posx + limit > item4x && posx - limit < item4x++ + limit) {
				onHand4 = true;
				inventory.push_back(pistola1);
				item4x = 10000;
				item4y = 10000;
			}
			if (posy - limit < item4y + limit && posy - limit > item4y + limit && posx + limit > item4x && posx - limit < item4x + limit) {
				onHand4 = true;
				inventory.push_back(pistola1);
				item4x = 10000;
				item4y = 10000;
			}
		}
	}

		if (onHand && inventoryIterator == ++inventory.begin())
		{
			item1x = posx;
			item1y = posy;
		}
		if (onHand2 && inventoryIterator == ++++inventory.begin())
		{
			item2x = posx;
			item2y = posy;
		}
		if (onHand3 && inventoryIterator == ----inventory.end())
		{
			item3x = posx;
			item3y = posy;
		}
		if (onHand4 && inventoryIterator == --inventory.end())
		{
			item4x = posx;
			item4y = posy;
		}

}

void ofApp::PrevItem()
{	
	//si estamos en el inicio de la lista, ir al final
	
	if (inventoryIterator == inventory.begin())
	{
		puts("inicio, moviendo al final");
		inventoryIterator = inventory.end();
		--inventoryIterator;
	}
	else
	{
		--inventoryIterator;
		if (inventoryIterator == inventory.begin())
		{
			puts("llegando al inicio");
		}
	}
	
	//inventoryIterator = inventory.begin();
	std::cout << "item: " << (*inventoryIterator).name << "\n";
}
void ofApp::NextItem()
{
	++inventoryIterator;
	if (inventoryIterator == inventory.end())
	{
		inventoryIterator = inventory.begin();
	}

	std::cout << "item: " << (*inventoryIterator).name << "\n";
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'w') w = true;
	if (key == 'a') a = true;
	if (key == 's') s = true;
	if (key == 'd') d = true;

	//inputs para navegar el inventario
	if (appstate == EAppState::lemmings)
	{
		//inventory
		if (key == 57357)
		{
			PrevItem();
		}
		if (key == 57359)
		{
			NextItem();
		}
	}

	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w') w = false;
	if (key == 'a') a = false;
	if (key == 's') s = false;
	if (key == 'd') d = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (x >= 0 && y >= 0 && x <= ofGetWidth() && y <= ofGetHeight())
	{
		//spawnear (engendrar) un objeto nuevo y agregarlo a la losta
		Entity newEntity = Entity();
		newEntity.position->x = x;
		newEntity.position->y = y;
		gameObjects.push_back(newEntity);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}



//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
