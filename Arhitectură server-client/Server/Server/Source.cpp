#include "UserRoutes.h"
#include "Game.h"

int main()
{
	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	storage.sync_schema();
	crow::SimpleApp app;
	
	routeForSignIn(app, storage);
	routeForLogin(app, storage);
	routeForStatistics(app, storage);

	Game game(storage, app);
	game.gameManager();
	app.port(14040).multithreaded().run();
	
}