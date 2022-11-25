#include "Quizs.h"


void populateStorage(Storage& storage)
{
	std::vector<Quiz> qz = {
		Quiz{ -1, "Care este cel mai lung fluviu din Europa?", "Dunarea", "Volga","Ron","Nipru", 1},
		Quiz{ -1, "Din ce tara izvoraste Dunarea?", "Italia", "Bulgaria","Rusia","Germania", 4}
	};
	storage.insert_range(qz.begin(), qz.end());
}
