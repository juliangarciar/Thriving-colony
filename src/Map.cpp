#include "Map.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>
#include <OBDEngine/ResourceManager/ResourceJSON.h>
#include "Human.h"

#include "IA.h"
#include "IOEngine/IO.h"
#include "GraphicEngine/Window.h"

#include "Map.h"

Map* Map::pinstance = 0;

Map* Map::Instance() {
    if (pinstance == 0) {
        pinstance = new Map();
    }
    return pinstance;
}

Map::Map() {
    human = Human::Instance();
    ia = IA::Instance();
    hud = Hud::Instance();
}

Map::~Map() {
    delete skybox;
    delete terrain;
    delete camera;
}

void Map::Init() {
	hud->InitProgressBar();
	hud->showProgressBar(true);

    loadProgress(0);

    ResourceJSON *r = (ResourceJSON*)IO::Instance() -> getResourceManager() -> getResource(loadMap, true);
    json j = *r -> getJSON();

    loadProgress(5);

    //Skybox
    skybox = new Skybox(j["map"]["skybox_textures"].get< std::vector<std::string> >());

    loadProgress(10);

    //Luz
    for (auto& element : j["lights"]) {
        Vector3<f32> lp;
        lp.x = element["position"]["x"].get<i32>();
        lp.y = element["position"]["y"].get<i32>();
        lp.z = element["position"]["z"].get<i32>();
        Light *light = new Light(lp, Color(element["color"]["r"].get<f32>(), element["color"]["g"].get<f32>(), element["color"]["b"].get<f32>()), element["intensity"].get<i32>());
		lights.push_back(light);
	}

    loadProgress(15);

    //Create map
    terrain = new Terrain(j["map"]["heightmap"].get<std::string>().c_str());
    terrain -> setTexture(new Texture(j["map"]["texture"].get<std::string>().c_str()), new Texture(j["map"]["detail_texture"].get<std::string>().c_str()));
    terrain -> setSize(Vector3<f32>(j["map"]["scale"]["x"].get<int>(), j["map"]["scale"]["y"].get<int>(), j["map"]["scale"]["z"].get<int>()));
	mapMargins = new Margins();
	mapMargins->top = j["map"]["margins"]["top"].get<int>();
	mapMargins->right = j["map"]["margins"]["right"].get<int>();
	mapMargins->bottom = j["map"]["margins"]["bottom"].get<int>();
	mapMargins->left = j["map"]["margins"]["left"].get<int>();
    WorldGeometry::Instance() -> Init(cSize, i32(j["map"]["size"]["width"].get<int>()), i32(j["map"]["size"]["height"].get<int>()), cDepth);

    loadProgress(35);

    //Game productivity
    metalProductivity = j["game"]["metal_productivity"].get<i32>();
    crystalProductivity = j["game"]["crystal_productivity"].get<i32>();
	influenceRangeIncrement = j["game"]["expansion_increment"].get<i32>();
	influenceRangeIncrementLimit = j["game"]["expansion_increment_times"].get<i32>();
	citizenIncrement = j["game"]["citizen_increment"].get<i32>();

	winCondition = FinishCondition();
	winCondition.player = j["game"]["win_condition"]["player"].get<std::string>();
	winCondition.building = j["game"]["win_condition"]["building"].get<std::string>();
	winCondition.condition = j["game"]["win_condition"]["condition"].get<std::string>();
	winCondition.value = j["game"]["win_condition"]["value"].get<i32>();

    IO::Instance() -> getEventManager() -> addEvent("checkWinCondition", [=]() {
		int amount = 0;
		if (winCondition.player == "IA"){
			amount = IA::Instance() -> getBuildingManager() -> getAmount(winCondition.building);
		} else if (winCondition.player == "Human") {
			amount = Human::Instance() -> getBuildingManager() -> getAmount(winCondition.building);
		}

		bool youWin = false;

		if (winCondition.condition == "=="){
			youWin = (amount == winCondition.value);
		} else if (winCondition.condition == "<="){
			youWin = (amount <= winCondition.value);
		} else if (winCondition.condition == ">="){
			youWin = (amount >= winCondition.value);
		} else if (winCondition.condition == "<"){
			youWin = (amount < winCondition.value);
		} else if (winCondition.condition == ">"){
			youWin = (amount > winCondition.value);
		} else if (winCondition.condition == "!="){
			youWin = (amount != winCondition.value);
		}

		if (youWin){
			Game::Instance() -> changeState(Enumeration::State::WinState);
		}
	});

	loseCondition = FinishCondition();
	loseCondition.player = j["game"]["lose_condition"]["player"].get<std::string>();
	loseCondition.building = j["game"]["lose_condition"]["building"].get<std::string>();
	loseCondition.condition = j["game"]["lose_condition"]["condition"].get<std::string>();
	loseCondition.value = j["game"]["lose_condition"]["value"].get<i32>();

    IO::Instance() -> getEventManager() -> addEvent("checkLoseCondition", [=]() {
		int amount = 0;
		if (loseCondition.player == "IA"){
			amount = IA::Instance() -> getBuildingManager() -> getAmount(loseCondition.building);
		} else if (loseCondition.player == "Human") {
			amount = Human::Instance() -> getBuildingManager() -> getAmount(loseCondition.building);
		}

		bool youLose = false;

		if (loseCondition.condition == "=="){
			youLose = (amount == loseCondition.value);
		} else if (loseCondition.condition == "<="){
			youLose = (amount <= loseCondition.value);
		} else if (loseCondition.condition == ">="){
			youLose = (amount >= loseCondition.value);
		} else if (loseCondition.condition == "<"){
			youLose = (amount < loseCondition.value);
		} else if (loseCondition.condition == ">"){
			youLose = (amount > loseCondition.value);
		} else if (loseCondition.condition == "!="){
			youLose = (amount != loseCondition.value);
		}

		if (youLose){
			Game::Instance() -> changeState(Enumeration::State::DefeatState);
		}
	});
    
	loadProgress(45);

    //Human
    human -> Init(humanBreed); 
    human -> metalAmount = j["player"]["initial_metal"].get<i32>();
    human -> crystalAmount = j["player"]["initial_crystal"].get<i32>();
    human -> buildableRange = j["player"]["building_radius"].get<f32>();

    Vector2<f32> humanPosition(j["player"]["mainBuilding"]["position"]["x"], j["player"]["mainBuilding"]["position"]["z"]);
    human -> getBuildingManager() -> createBuilding(humanPosition, "MainBuilding", 0);
    human -> hallPosition = Vector3<f32>(humanPosition.x, terrain->getY(humanPosition.x, humanPosition.y), humanPosition.y);
    humanStartPos = humanPosition;

    for (auto& element : j["player"]["buildings"]) {
        Vector2<f32> v(element["position"]["x"], element["position"]["z"]);
        human -> getBuildingManager() -> createBuilding(v, element["type"].get<std::string>(), 0);
    }

    //Human events
    IO::Instance() -> getEventManager() -> addEvent("RetractTroopsHuman", [&]() {
        Human::Instance() -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent("DeployTroopsHuman", [&]() {
        Vector3<f32> p = Human::Instance() -> hallPosition;
        Human::Instance() -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    loadProgress(60);

    //IA
    ia -> Init(iaBreed);
    ia -> metalAmount = j["IA"]["initial_metal"].get<i32>();
    ia -> crystalAmount = j["IA"]["initial_crystal"].get<i32>();
    ia -> buildableRange = j["IA"]["building_radius"].get<f32>();

    Vector2<f32> iaPosition(j["IA"]["mainBuilding"]["position"]["x"], j["IA"]["mainBuilding"]["position"]["z"]);
    ia -> getBuildingManager() -> createBuilding(iaPosition, "MainBuilding", 0);
    ia -> hallPosition = Vector3<f32>(iaPosition.x, terrain->getY(iaPosition.x, iaPosition.y), iaPosition.y);
    iaStartPos = iaPosition;
    
    for (auto& element : j["IA"]["buildings"]) {
        Vector2<f32> iaPosition(element["position"]["x"], element["position"]["z"]);
        ia -> getBuildingManager() -> createBuilding(iaPosition, element["type"].get<std::string>(), 0);
    }

    //IA Events
    IO::Instance() -> getEventManager() -> addEvent("RetractTroopsIA", [&]() {
        IA::Instance() -> getUnitManager() -> retractAllTroops();
    });
    IO::Instance() -> getEventManager() -> addEvent("DeployTroopsIA", [&]() {
        Vector3<f32> p = IA::Instance() -> hallPosition;
        IA::Instance() -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
    });

    loadProgress(80);

    //Hud buttons
    hud -> Init();
    for (auto& element : j["buildables"]) {
        Hud::Instance()->setButtonStatus(element["type"].get<std::string>(), element["isBuildable"].get<bool>());
    }
    Hud::Instance()->setButtonStatus("expandableTerrain", j["expandableTerrain"].get<bool>());

    //Hud events
    IO::Instance() -> getEventManager() -> addEvent("showBuiltText", [&]() {
        Hud::Instance() -> addToastToQueue("Se ha construido un edificio");
    });
    IO::Instance() -> getEventManager() -> addEvent("showRecruitedText", [&]() {
        Hud::Instance() -> addToastToQueue("Se ha reclutado una tropa");
    });
	hud->InitDebug();

	loadProgress(95);

    //Init camera controller
    camera = new CameraController();
	camera -> minZoom = j["camera"]["zoom"]["min"].get<int>();
	camera -> maxZoom = j["camera"]["zoom"]["max"].get<int>();
	camera -> zoomDistanceFromTarget = j["camera"]["zoom"]["initialDistanceFromTarget"].get<int>();
	camera -> minInclination = j["camera"]["rotation"]["min_inclination"].get<int>();
	camera -> maxInclination = j["camera"]["rotation"]["max_inclination"].get<int>();
	camera -> rotateDegrees = Vector2<f32>(j["camera"]["rotation"]["initialRotation"]["x"].get<int>(), j["camera"]["rotation"]["initialRotation"]["y"].get<int>());
    camera -> Init(Vector3<f32>(humanStartPos.x, terrain->getY(humanStartPos.x,humanStartPos.y), humanStartPos.y));

    loadProgress(100);
	hud->showProgressBar(false);
}

void Map::Input() {
    camera -> Move();
    camera -> RotateAndInclinate();
    camera -> Zoom();
    camera -> CenterCamera();

    collisionPoint = terrain->getPointCollision(IO::Instance()->getMouse()->getPosition());
	
	human -> getBuildingManager() -> testRaycastCollisions();
	human -> getUnitManager() -> testRaycastCollisions();

	ia -> getBuildingManager() -> testRaycastCollisions();
	ia -> getUnitManager() -> testRaycastCollisions();

	i32 onMap = true;
	//Interactions with our buildings
	i32 idBuilding = human -> getBuildingManager() -> getCollisionID();
	if (idBuilding != -1) {
		if (!human -> getUnitManager() -> isTroopSelected())
			IO::Instance() -> getMouse() -> changeCustomIcon(1);
		
		if (IO::Instance() -> getMouse() -> leftMousePressed()) {
			Building *b = human -> getBuildingManager()->getBuilding(idBuilding);
			if (b != nullptr) {
				if (human -> getBuildingManager() -> checkFinished(idBuilding)) {
					//ShowPopup
					hud -> showPopup(b->getType());
				}
			}
		}
		// Right clicked
		if (IO::Instance() -> getMouse() -> rightMousePressed()) {
			// Have a troop
			if (human -> getUnitManager() -> isTroopSelected()) {
				// Main hall
				if (idBuilding == 0) {
					//Retract
					human -> getUnitManager() -> getSelectedTroop() -> switchState(Enumeration::UnitState::Retract);
				}
			}
		}

		onMap = false;
	}

	//Interactions with IA's buildings
	i32 idBuildingIA =  ia -> getBuildingManager() -> getCollisionID();
	if (idBuildingIA != -1) {
		IO::Instance() -> getMouse() -> changeCustomIcon(2);
		
		if (human -> getUnitManager() -> isTroopSelected()) {
			if (IO::Instance() -> getMouse() -> rightMousePressed()) {
				human -> getUnitManager()->getSelectedTroop()->setTarget(ia -> getBuildingManager()->getBuilding(idBuildingIA));
			}
		}

		onMap = false;
	}

	//Interactions with Human Units
	i32 idTroop = human -> getUnitManager() -> getCollisionID();
	if (idTroop != -1) {
		IO::Instance() -> getMouse() -> changeCustomIcon(1);

		if (IO::Instance() -> getMouse() -> leftMousePressed()) {
			human -> getUnitManager() -> selectTroop(idTroop);
		}
		
		onMap = false;
	}

	//Interactions with IA Units
	i32 idTroopIA = ia -> getUnitManager() -> getCollisionID();
	if (idTroopIA != -1) {
		IO::Instance() -> getMouse() -> changeCustomIcon(2);

		if (human -> getUnitManager() -> isTroopSelected()) {
			if (IO::Instance() -> getMouse() -> rightMousePressed()) {
				human -> getUnitManager()->getSelectedTroop()->setTarget(ia -> getUnitManager()->getUnit(idTroopIA));
			}
		}

		onMap = false;
	}

	if(onMap){
		if(human -> getUnitManager() -> isTroopSelected()){
			if (IO::Instance()-> getMouse() -> rightMousePressed()) {
				human -> getUnitManager() -> moveOrder();
			}
		}
	}

	//If nothing happens
	if (onMap) {
		if (human -> getUnitManager() -> isTroopSelected()) {
			IO::Instance() -> getMouse() -> changeCustomIcon(0);
		} 
		else if (human -> getUnitManager() -> isDeployingTroop()) {
			IO::Instance() -> getMouse() -> changeCustomIcon(0);
			i32 idTroop = human -> getUnitManager() -> getDeployingTroopID();
			if (idTroop > 0) {
				if (IO::Instance() -> getMouse() -> rightMousePressed()) {
					Vector3<f32> p = getMouseCollitionPoint();
					human -> getUnitManager() -> deploySelectedTroop(Vector2<f32>(p.x, p.z));
					human -> getUnitManager() -> selectTroop(idTroop);
				}
			} else if (idTroop == 0) {
				if (IO::Instance() -> getMouse() -> rightMousePressed()) {
					Vector3<f32> p = getMouseCollitionPoint();
					human -> getUnitManager() -> deployAllTroops(Vector2<f32>(p.x, p.z));
				}
			} else {
				//Ninguna tropa seleccionada
			}
		} else {
			IO::Instance() -> getMouse() -> changeCustomIcon(0);
		}

		if (IO::Instance() -> getMouse() -> leftMousePressed())
			human -> getUnitManager() -> unSelectTroop();
	}
}

void Map::Update() {
	//Update HUD
	hud -> Update();

	//Update human and IA status
	human -> Update();
	ia -> Update();

	//Win/Lose
	IO::Instance() -> getEventManager() -> triggerEvent("checkWinCondition");
	IO::Instance() -> getEventManager() -> triggerEvent("checkLoseCondition");
}

void Map::Render() {

}

void Map::CleanUp() {
    for (i32 i=0; i<lights.size(); i++) {
        delete lights[i];
    }
    lights.clear();
    delete terrain;
    delete camera;
	delete skybox;
	delete mapMargins;
}

void Map::setMap(std::string l){
	loadMap = l;
}

void Map::setBreeds(std::string b1, std::string b2){
	humanBreed = b1;
	iaBreed = b2;
}

Vector2<f32> Map::getHumanStartPosition() {
    return humanStartPos;
}

Vector2<f32> Map::getIAStartPosition() {
    return iaStartPos;
}

Vector3<f32> Map::getMouseCollitionPoint() {
    return collisionPoint;
}

Terrain* Map::getTerrain() {
    return terrain;
}

CameraController* Map::getCamera() {
    return camera;
}

Margins *Map::getMapMargins() {
	return mapMargins;
}

i32 Map::getMetalProductivity() {
	return metalProductivity;
}

i32 Map::getCrystalProductivity() {
	return crystalProductivity;
}

i32 Map::getCitizenIncrement() {
	return citizenIncrement;
}

i32 Map::getInfluenceRangeIncrement() {
	return influenceRangeIncrement;
}

i32 Map::getInfluenceRangeIncrementLimit() {
	return influenceRangeIncrementLimit;
}

void Map::loadProgress(i32 p) {
	hud->setProgressBar(p/100.f);
	Window::Instance()->endScene();
}