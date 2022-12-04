#include "Storage.h"


void populateStorage(Storage& storage)
{
	std::vector<User> users = {
		User{"Iosif", "19"},
		User{"Diana", "20"},
		User{"Viviana", "21"},
		User{"Ionel", "22"},
		User{"Cristi", "23"}
	};
	storage.insert_range(users.begin(), users.end());
}
