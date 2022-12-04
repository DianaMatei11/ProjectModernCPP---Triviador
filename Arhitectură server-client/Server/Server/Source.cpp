#include "Storage.h"

int main()
{
	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	storage.sync_schema();
	auto initUsersCount = storage.count<User>();
	if (initUsersCount == 0)
	{
		populateStorage(storage);
	}


	std::vector<crow::json::wvalue> numericalQuest_json;
	for (const auto& quest : storage.iterate<IntrebareNumerica>())
	{
		numericalQuest_json.push_back(crow::json::wvalue{
			{"Id", quest.GetId()},
			{"Question", quest.GetEnunt()}
			});
	}


	crow::SimpleApp app;
	CROW_ROUTE(app, "/numericalQuestion")([&numericalQuest_json]() {
		int index = Intrebare::GetRandomNumber(0, numericalQuest_json.size());
		return numericalQuest_json[index];
		});

	app.port(14040).multithreaded().run();
}