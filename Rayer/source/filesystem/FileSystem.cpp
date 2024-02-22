#include "filesystem/FileSystem.h"


namespace Rayer {

    RayerFileSystem::RayerFileSystem() {

        
    }

	std::string RayerFileSystem::GetSolutionDirectory(const std::string& path) {
        fs::path currentDir = fs::absolute(path);

        // Search upwards from the current directory to find the solution file (.sln)
        while (true) {
            for (const auto& entry : fs::directory_iterator(currentDir)) {
                if (entry.path().extension() == ".sln") {
                    return currentDir.string(); // Found the solution file
                }
            }

            // Move to the parent directory
            currentDir = currentDir.parent_path();
            if (currentDir.empty()) {
                // We have reached the root directory
                break;
            }
        }

        return ""; // Solution directory not found
	}

  
    std::string RayerFileSystem::ReadFileToString(const std::string& path) {

        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return "";
        }

        std::string content((std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>()));

        return content;
    }

    

    RayerFileSystem RayerFileSystem::instance;

}