#include "Users.h"


void populateStorage(Storage& storage)
{
	std::vector<User> users = {
		User{ -1, "Iosif", "19", 0, 0},
		User{ -1, "Diana", "20", 0, 0},
		User{ -1, "Viviana", "21", 0, 0},
		User{ -1, "Ionel", "22", 0, 0},
		User{ -1, "Cristi", "23", 0, 0}
		
	};
	storage.insert_range(users.begin(), users.end());
}
