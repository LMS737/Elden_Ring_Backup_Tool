#include "stdafx.h"
#include <iostream>
#include <shlobj.h>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Pause, so we can see some output from the program.
void pause() {
	std::cout << "Press [Enter] to exit" << std::endl;
	std::cin.get();
}

int main()
{	
	// Try to get user's AppData\Roaming path
	PWSTR path_tmp = NULL;
	HRESULT result = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path_tmp);
	
	if (result != S_OK) {
		CoTaskMemFree(path_tmp);
		std::cout << "Could not find AppData Roaming folder..." << std::endl;
		pause();
		return 1;
	}

	// Convert from PWSTR to std::filesystem::path
	fs::path path;
	path = path_tmp;
	path += "\\EldenRing";
	
	// Free memory
	CoTaskMemFree(path_tmp);

	// Could not find Elden Ring folder
	if (!fs::exists(path)) {
		std::cout << "Could not find Elden Ring folder..." << std::endl;
		pause();
		return 1;
	}

	// Create Backup_Saves folder
	fs::path backup_path = ".\\Backup_Saves";
	if (!fs::exists(backup_path)) {
		fs::create_directory(".\\Backup_Saves");
		std::cout << "Created Backup_Saves folder" << std::endl;
	}

	// Number of saves to keep
	int nr_saves = 5;

	// Set copy options
	const auto copyOptions = fs::copy_options::overwrite_existing 
		| fs::copy_options::recursive;

	// Create Save_1 up to Save_5
	for (int i = 1; i < nr_saves + 1; ++i) {
		std::string save_directory = "Save_" + std::to_string(i);
		fs::path tmp_path = backup_path / save_directory;
		
		if (!fs::exists(tmp_path)) {
			fs::copy(path, tmp_path, copyOptions);
			std::cout << "Stored most recent save in folder: Save_" + std::to_string(i) << std::endl;
			std::cout << "Done" << std::endl;
			pause();
			return 0;
		}
	}

	/*
	All Save folders already exists so remove oldest save, Save_1 first.
	Save_5 will always be the most recent save backup if nr_saves = 5.
	After that we are left with Save_2, Save_3, Save_4 and Save_5.
	Simply rename Save_i to Save_i-1 so in the end we have Save_1, Save_2, Save_3 and Save_4.
	*/

	fs::remove_all(backup_path / "Save_1");
	std::cout << "Removed Save_1" << std::endl;

	for (int i = 2; i < nr_saves + 1; ++i) {
		std::string old_save_directory = "Save_" + std::to_string(i);
		fs::path old_save_path = backup_path / old_save_directory;

		std::string new_save_directory = "Save_" + std::to_string(i - 1);
		fs::path new_save_path = backup_path / new_save_directory;
		fs::rename(old_save_path, new_save_path);

		std::cout << "Renamed " + old_save_directory + " To: " + new_save_directory << std::endl;
	}

	// Create Save_X, the most recent save. By default this will be Save_5.
	std::string save_X_string = "Save_" + std::to_string(nr_saves);
	fs::path save_X_path = backup_path / save_X_string;
	fs::copy(path, save_X_path, copyOptions);
	std::cout << "Stored most recent save in folder: Save_" + std::to_string(nr_saves) << std::endl;
	std::cout << "Done" << std::endl;
	pause();
    return 0;
}

