#include "TrackingLevel.h"
#include "../../managers/AssetManager.h"
#include "../LevelElements/enemies/Bird2.h"
#include "../LevelElements/enemies/Bird3.h"
#include "../LevelElements/scenery/Billboard.h"
#include "../LevelElements/util/EndLevelTrigger.h"
#include "../LevelElements/util/SpawnTrigger.h"
#include "../LevelElements/util/SurfaceToggleTrigger.h"
#include "../menus/ResultsMenu.h"

void TrackingLevel::load() {
  surfaces.emplace_back(std::vector<Vector2f>({
      {   50,  250},
      { -210,  300},
      { -250,  250},
      { -325,  325},
      { -450,  350},
      { -543,  286},
      { -612,  230},
      { -641,  312},
      { -702,  358},
      { -748,  330},
      { -795,  349},
      { -863,  342},
      { -905,  309},
      { -954,  362},
      { -838,  623},
      { -934,  694},
      {-1075,  734},
      {-1111,  741},
      {-1208,  725},
      {-1263,  732}, // before hole
      {-1254,  795},
      {-1196,  846},
      {-1000,  772},
      {- 800,  802},
      {- 600,  813},
      {- 400,  853},
      {- 200,  837}, // above continuation
      {  000,  803},
      {  200,  796},
      {  400,  874},
      {  600,  941},
      {  800, 1089},
      { 1000, 1200}, // end point
      {  943, 1257},
      {  862, 1311},
      {  807, 1261},
      {  724, 1261},
      {  605, 1203},
      {  438, 1132},
      {  374, 1096},
      {  146, 1063},
      {  003,  999}, // below continuation
      {-  95, 1053},
      {- 158, 1113},
      {- 325, 1147},
      {- 473, 1163},
      {- 537, 1201},
      {- 699, 1047},
      {- 752, 1011},
      {- 883, 1007},
      {- 946,  978},
      {-1077, 1066},
      {-1102, 1103},
      {-1283, 1003},
      {-1307,  986},
      {-1375,  904},
      {-1532,  881},
      {-1683,  804},
      {-1713,  767}, // after hole
      {-1795,  793},
      {-2014,  764},
      {-2167,  712},
      {-2196,  635},
      {-2074,  513},
      {-2008,  452},
      {-1736,  257},
      {-1532,  417},
      {-1405,  362},
      {-1325,  463},
      {-1205,  472},
      {-1124,  175},
      {-1086,  056},
      { -964,  012},
      { -852,  100},
      { -810,  040},
      { -760, -010},
      { -700, -050},
      { -625, -025},
      { -575,  000},
      { -550, -075},
      { -400, -125},
      { -200, -150},
      {  000, -325},
      {  240, -291},
      {  309, -245},
      {  312, -117},
      {  272, -122},
      {  239, -112},
      {  264, -076},
      {  325, -073},
      {  475,  000},
      {  384,  136},
      {  250,  200},
      {  120,  260}
  }));
  surfaces.emplace_back(std::vector<Vector2f>({
      { 027,  50},
      { 135,  74},
      { 077,  00},
      { 057, -20},
      {-023,  00},
  }));
  surfaces.emplace_back(std::vector<Vector2f>({
      {-340,  072},
      {-300,  140},
      {-283,  101},
      {-139,  117},
      {-118,   95},
      {-159,   19},
  }));
  surfaces.emplace_back(std::vector<Vector2f>({
      {-1351,  702},
      {-1473,  694},
      {-1572,  729},
      {-1495,  735},
  }), false);
  surfaces.emplace_back(std::vector<Vector2f>({
      {-1253,  732},
      {-1413,  697},
      {-1723,  767},
      {-1549,  784}
  }), true);
  winds.emplace_back(new AbstractWind({- 60.0f, -10.0f}, 0.5f));
  winds.emplace_back(new AbstractWind({  00.0f, -50.0f}, { -500, -500, 1000, 1000}));
  winds.emplace_back(new AbstractWind({-100.0f,   0.0f}, {-2200,  250, 1500, 500}));
  winds.emplace_back(new AbstractWind({  60.0f,   0.0f}, {-2000,  750, 1000, 500}));

  AssetManager::RegisterTexture("Data/images/Arrow.png", 150);
  addElement(new Billboard({-80.0f, 150.0f}, 15.0f, AssetManager::getTexture(150)));
  addElement(new Billboard({250.0f, 0.0f}, -15.0f, AssetManager::getTexture(150)));
  addElement(new Billboard({-1500,  615}, 0.0f, AssetManager::getTexture(150)));
  addElement(new Billboard({-2100,  635}, 195.0f, AssetManager::getTexture(150)));

  addCheckpointAt({ - 250,  250}, { - 400, - 125});
  addCheckpointAt({ - 612,  230}, { - 575, -   0});
  addCheckpointAt({ - 954,  362}, { -1205,   472});
  addCheckpointAt({ -1549,  784}, { -1532,   417});
  addCheckpointAt({ -1713,  767}, { -1263,   732});
  addCheckpointAt({ - 752, 1011}, { - 800,   802});
  addCheckpointAt({     0,  803}, {     3,   999});
  addElement(new EndLevelTrigger({850, 1050, 150.0f, 300.0f}));
  addElement(new SurfaceToggleTrigger(surfaces[4], false, {-2200, 450, 250, 500}));
  addElement(new SurfaceToggleTrigger(surfaces[3], true,  {-2200, 450, 250, 500}));

  player = std::make_shared<AbstractPlayer>(Vector2f{150.0f, -30.0f}, chapter);

  AbstractLevel::load();
}

template<typename T> std::shared_ptr<T> launder(T* t) {return std::shared_ptr<T>{t};}

void TrackingLevel::open() {
  S::Window.setMouseCursorVisible(false);
  AbstractLevel::open();

  if (!S::bird3) {
    ResultsMenu::bird = std::make_shared<Bird3>(Vector2f{0.0f, 0.0f});
  }
  else if (!S::bird2) {
    ResultsMenu::bird = std::make_shared<Bird2>(Vector2f{0.0f, 0.0f});
  }

  addElement(ResultsMenu::bird->makeCopy({-150.0f, -30.0f}));
  elements.back()->destroy_on_load = true;
  addElement(new SpawnTrigger({-100.0f, -200.0f, 50.0f, 500.0f}, launder<AbstractLevelElement>(ResultsMenu::bird->makeCopy({-25.0f, -150.0f}))));
  elements.back()->destroy_on_load = true;
  addElement(new SpawnTrigger({-1450.0f, 350.0f, 100.0f, 500.0f}, launder<AbstractLevelElement>(ResultsMenu::bird->makeCopy({-1405.0f,  400.0f}))));
  elements.back()->destroy_on_load = true;
}

void TrackingLevel::Pause(bool down) {
  AbstractLevel::Pause(down);
  S::Window.setMouseCursorVisible(down);
}

void TrackingLevel::close() {
  S::Window.setMouseCursorVisible(true);

  if (!S::bird3) {
    S::bird3 = true;
    printf("Bird 3 is done \n");
  }
  else if (!S::bird2) {
    S::bird2 = true;
    printf("Bird 2 is done \n");
  }

  AbstractLevel::close();
}
