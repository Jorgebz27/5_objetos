#pragma once

#include "ofMain.h"
#include <vector>
#include "Entity.h"
#include "ofxGui.h"
#include <list> //std::list, lista ligada
#include <time.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupPelotas();
		void setupLemmings();
		void update();
		void updatePelotas();
		void updateLemmings();

		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	//mis variables
		

		float gravity = 9.81f * 100; //escala a 100 px por metro

		float radioCirculo;

		std::vector<Entity> gameObjects;
		std::vector<ofColor> color;

		//imagenes
		ofImage imgHogar;

		//estados de la aplicacion
		enum EAppState {
			menu, pelotas, lemmings, max
		} appstate ;

		//cosas del UI
		ofTrueTypeFont titleFont;
		ofTrueTypeFont uiFont;
		ofxPanel mainmenu;
		ofxButton btnEjercicio1, btnEjercicio2;

		void onBtn1Pressed();
		void onBtn2Pressed();

		//juego con inventario (lemmings)
		ofImage playerSpriteImg;
		ofImage espada;
		ofImage veneno;
		ofImage bomba;
		ofImage pistola;

		float limit = 30;
		float posx;
		float posy;
		float item1x, item1y;
		float item2x, item2y;
		float item3x, item3y;
		float item4x, item4y;

		ofVec2f playerSize;
		ofVec2f playerSpriteOffset;
		ofVec2f item1Size;
		ofVec2f item1Offset;
		ofVec2f item2Size;
		ofVec2f item2Offset;
		ofVec2f item3Size;
		ofVec2f item3Offset;
		ofVec2f item4Size;
		ofVec2f item4Offset;
		//inputs del jugador
		bool w, s, a, d;
		//inventario, es una lista ligada
		std::list<Entity> inventory;
		void NextItem();
		void PrevItem();
		std::list<Entity>::iterator inventoryIterator;
};
